
#include "android_asset_fs.h"
#include "io/file.h"
#include "logging.h"
#include <ios>
#include <cassert>

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

asset_fs::asset_fs()
{
}

eps::io::file* asset_fs::open(const std::string& file)
{
	if (!assets_.count(file))
	{
		LOGE("Asset %s NOT exists", file.c_str());
		return new asset_content("");
	}

	LOGI("Asset %s exists", file.c_str());
	return new asset_content(assets_[file]);
}

bool asset_fs::exists(const std::string& file)
{
	return assets_.count(file);
}

void asset_fs::close(eps::io::file* file)
{
	if (file)
	{
		delete file;
	}
}

std::map<std::string, std::string> asset_fs::assets_;

asset_fs2::asset_fs2(const std::string& path_to_cache)
	: _path_to_cache(path_to_cache.empty() ? "" : path_to_cache + "/")
{
}

eps::io::file* asset_fs2::open(const std::string& file)
{
	LOGI("Asset %s %s", file.c_str(), exists(file) ? "exists" : "NOT exists");
	const std::string abs_path = _path_to_cache + file;
	return new asset_file(abs_path.c_str());
}

bool asset_fs2::exists(const std::string& file)
{
	const std::string abs_path = _path_to_cache + file;
	return asset_file::exists(abs_path.c_str());
}

void asset_fs2::close(eps::io::file* file)
{
	if (file)
	{
		delete file;
	}
}

#ifndef ANDROID

asset_fs3::asset_fs3(const std::string& mount_point) :
	mount_point_(mount_point.empty() ? "" : mount_point + "/"),
	assets_()
{
}

eps::io::file* asset_fs3::open(const std::string& file)
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

bool asset_fs3::exists(const std::string& file)
{
	const auto full_path = mount_point_ + file;
	return asset_file::exists(full_path.c_str());
}

void asset_fs3::close(eps::io::file* file)
{
	if (file)
	{
		delete file;
	}
}

#endif
