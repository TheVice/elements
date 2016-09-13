
#include "asset_fs.h"
#include "io/file.h"
#include <fstream>

namespace Desktop
{

struct asset_stream : public eps::io::file
{
	explicit asset_stream(const std::string& file) :
		mAssetFile(file, std::fstream::binary)
	{
	}

	~asset_stream()
	{
	}

	size_t read(void* output, size_t size, size_t count)
	{
		mAssetFile.read(static_cast<char*>(output), count);
		return count;
	}

	size_t tell() const
	{
		return mAssetFile.tellg();
	}

	size_t size() const
	{
		mAssetFile.seekg(0, std::ios::end);
		return mAssetFile.tellg();
	}

	int seek(size_t offset, int origin)
	{
		mAssetFile.seekg(offset, static_cast<std::fstream::seekdir>(origin));
		return mAssetFile.tellg();
	}

	void flush()
	{
	}

	static bool exists(const std::string& file)
	{
		std::ifstream assetFile(file, std::fstream::binary);

		if (assetFile)
		{
			return true;
		}

		return false;
	}

private:
	mutable std::ifstream mAssetFile;
};

asset_fs::asset_fs()
{
}

eps::io::file* asset_fs::open(const std::string& file)
{
	return new asset_stream(file);
}

bool asset_fs::exists(const std::string& file)
{
	return asset_stream::exists(file);
}

void asset_fs::close(eps::io::file* file)
{
	if (file)
	{
		delete file;
	}
}

}
