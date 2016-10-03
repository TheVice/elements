
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

asset_fs::asset_fs(const std::string& mount_point) :
	mount_point_(mount_point.empty() ? "" : mount_point + "/")
{
}

eps::io::file* asset_fs::open(const std::string& file)
{
	const auto full_path = mount_point_ + file;
	return new asset_stream(full_path);
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
