
#include "asset_fs.h"
#include "io/file.h"
#include <fstream>
#include <cassert>

namespace Desktop
{

struct asset_stream : public eps::io::file
{
	explicit asset_stream(const std::string& file) :
		mAssetFile(file, std::fstream::binary)
	{
	}

	size_t read(void* output, size_t size, size_t count)
	{
		assert(size == 1 || count == 1);

		if (mAssetFile.is_open())
		{
			const auto position = mAssetFile.tellg();
			mAssetFile.read(static_cast<char*>(output), size * count);
			const auto new_position = mAssetFile.tellg();
			return new_position - position;
		}

		return std::ios::pos_type(-1);
	}

	size_t tell() const
	{
		if (mAssetFile.is_open())
		{
			return mAssetFile.tellg();
		}

		return std::ios::pos_type(-1);
	}

	size_t size() const
	{
		if (mAssetFile.is_open())
		{
			const auto currentFilePosition = mAssetFile.tellg();
			mAssetFile.seekg(0, std::ios::end);
			const auto fileSize = mAssetFile.tellg();
			mAssetFile.seekg(currentFilePosition, std::ios::beg);
			return fileSize;
		}

		return std::ios::pos_type(-1);
	}

	int seek(size_t offset, int origin)
	{
		if (mAssetFile.is_open())
		{
			mAssetFile.seekg(offset, static_cast<std::ios::seekdir>(origin));
			return mAssetFile.tellg();
		}

		return std::ios::pos_type(-1);
	}

	void flush()
	{
	}

	virtual ~asset_stream()
	{
	}

	static bool exists(const std::string& file)
	{
		std::ifstream assetFile(file, std::fstream::binary);
		return assetFile.is_open();
	}

private:
	mutable std::ifstream mAssetFile;
};

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
		asset_stream asset(full_path);
		std::string file_content(asset.size(), '\0');
		asset.read(&file_content.front(), 1, file_content.size());
		assets_[full_path] = file_content;
	}

	return new asset_content(assets_[full_path]);
}

bool asset_fs::exists(const std::string& file)
{
	const auto full_path = mount_point_ + file;
	return asset_stream::exists(full_path);
}

void asset_fs::close(eps::io::file* file)
{
	if (file)
	{
		delete file;
	}
}

}
