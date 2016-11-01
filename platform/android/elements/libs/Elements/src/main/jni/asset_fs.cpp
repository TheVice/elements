/*
The MIT License (MIT)
Copyright (c) 2016 Alexey Yegorov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#include "asset_fs.h"
#include "logging.h"
#include <elements/io/file.h>
#ifdef ANDROID
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

struct asset_stream : public eps::io::file
{
public:

    explicit asset_stream(AAsset * jasset)
        : jasset_(jasset) {}

    ~asset_stream()
    {
        AAsset_close(jasset_);
    }

    size_t read(void * output, size_t size, size_t count) final
    {
        return AAsset_read(jasset_, output, size * count);
    }

    size_t tell() const final
    {
        return AAsset_getLength(jasset_) - AAsset_getRemainingLength(jasset_);
    }

    size_t size() const final
    {
        return AAsset_getLength(jasset_);
    }

    int seek(size_t offset, int origin) final
    {
        return AAsset_seek(jasset_, offset, origin) == (off_t)-1 ? -1 : 0;
    }

    void flush() final
    {

    }

private:

    AAsset * jasset_;
};

asset_fs::asset_fs(AAssetManager * mgr)
    : mgr_(mgr)
{}

eps::io::file * asset_fs::open(const std::string & file)
{
    if(AAsset * jasset = AAssetManager_open(mgr_, file.c_str(), AASSET_MODE_STREAMING))
        return new asset_stream(jasset);
    return nullptr;
}

bool asset_fs::exists(const std::string & file)
{
    if(AAsset * jasset = AAssetManager_open(mgr_, file.c_str(), AASSET_MODE_STREAMING))
    {
        AAsset_close(jasset);
        return true;
    }
    return false;
}

void asset_fs::close(eps::io::file * file)
{
    delete file;
}

#else

#include <ios>
#include <cassert>
#include <climits>

struct asset_content : public eps::io::file
{
	explicit asset_content(const std::string& content) :
		content_(content),
		pos_(0)
	{
	}

	size_t read(void* output, size_t size, size_t count)
	{
		assert(size == 1 || count == 1);

		if (pos_ < content_.size())
		{
			if (pos_ + size * count >= content_.size())
			{
				size = content_.size() - pos_;
				count = 1;
			}

			content_.copy(static_cast<char*>(output), size * count, pos_);
			pos_ += size * count;
			return size * count;
		}

		return 0;
	}

	size_t tell() const
	{
		return pos_;
	}

	size_t size() const
	{
		return content_.size();
	}

	int seek(size_t offset, int origin)
	{
		switch (static_cast<std::ios::seekdir>(origin))
		{
			case std::ios::beg:
				if (offset < size())
				{
					pos_ = offset;
				}
				else
				{
					return std::ios::pos_type(-1);
				}

				break;

			case std::ios::cur:
				if (pos_ + offset < size())
				{
					pos_ += offset;
				}
				else
				{
					return std::ios::pos_type(-1);
				}

			case std::ios::end:
				if (offset < size())
				{
					pos_ = size() - offset;
				}
				else
				{
					return std::ios::pos_type(-1);
				}

				break;

			default:
				return std::ios::pos_type(-1);
		}

		return pos_;
	}

	void flush()
	{
	}

	virtual ~asset_content()
	{
	}

private:
	const std::string content_;
	std::string::size_type pos_;
};

struct asset_file : public eps::io::file
{
	asset_file(const char* file_name)
		: _file(fopen(file_name, "rb"))
	{
	}

	size_t read(void * output, size_t size, size_t count)
	{
		if (!_file)
		{
			return -1;
		}

		return fread(output, size, count, _file);
	}

	size_t tell() const
	{
		if (!_file)
		{
			return -1;
		}

		return ftell(_file);
	}

	size_t size() const
	{
		if (!_file)
		{
			return -1;
		}

		const long offset = ftell(_file);
		fseek(_file, 0, SEEK_END);
		const long file_size = ftell(_file);
		fseek(_file, offset, SEEK_SET);
		return file_size;
	}

	int seek(size_t offset, int origin)
	{
		if (!_file)
		{
			return INT_MAX;
		}

		return fseek(_file, offset, origin);
	}

	void flush()
	{
		fflush(_file);
	}

	virtual ~asset_file()
	{
		if (!_file)
		{
			return;
		}

		fclose(_file);
	}

	static bool exists(const char* file_name)
	{
		FILE * _file = fopen(file_name, "rb");
		const bool is_open = (_file != nullptr);

		if (is_open)
		{
			fclose(_file);
		}

		return is_open;
	}

private:
	FILE * _file;
};

asset_fs::asset_fs(const std::string& mount_point) :
	mount_point_(mount_point.empty() ? "" : mount_point + "/"),
	assets_()
{
}

eps::io::file* asset_fs::open(const std::string& file)
{
	const auto full_path = mount_point_ + file;

	if (!assets_.count(full_path))
	{
		asset_file asset(full_path.c_str());
		std::string file_content(asset.size(), '\0');
		asset.read(&file_content.front(), 1, file_content.size());
		assets_[full_path] = file_content;
	}

	return new asset_content(assets_[full_path]);
}

bool asset_fs::exists(const std::string& file)
{
	const auto full_path = mount_point_ + file;
	return asset_file::exists(full_path.c_str());
}

void asset_fs::close(eps::io::file* file)
{
	if (file)
	{
		delete file;
	}
}

#endif
