
#include "android_asset_fs.h"
#include "io/file.h"
#include <ios>
#include <cassert>
#include "logging.h"

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

asset_fs::asset_fs()
{
}

eps::io::file* asset_fs::open(const std::string& file)
{
	if (!assets_.count(file))
	{
		LOGE("Asset %s NOT found", file.c_str());
		return new asset_content("");
	}

	LOGI("Asset %s found", file.c_str());
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
