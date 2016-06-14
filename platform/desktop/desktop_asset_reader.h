
#include "elements/assets/assets_storage.h"
#include "elements/assets/asset_texture.h"
#include "elements/assets/asset_blob.h"
#include "elements/assets/asset_xml.h"
#include "elements/assets/asset_operations_stream.h"
#include "Utility.h"

struct desktop_asset_reader : public eps::asset_reader
{
	// root path to asset folder. For example, C:\elements\assets
	explicit desktop_asset_reader(std::string& root);
	virtual ~desktop_asset_reader();

	bool visit(eps::asset_texture& asset) final
	{
		// path to asset, for example "shaders/experiments/air/particles.prog"
		const std::string& asset_path = asset.resource();

		// normalize and concatenate asset_path with root.
		// result is platform specific ('/' or '\\')
		const std::string result = P(asset_path);

		// create the file abstraction.
		// derived class from asset_read_operation (elements/assets/asset_operations.h)
		// for example, elements/assets/asset_operations_stream.h
		eps::asset_read_operation_stream opt(result.c_str());

		// load
		if (asset.load(&opt))
		{
			return true;
		}

		return false;
	}

	bool visit(eps::asset_blob& asset) final
	{
		const std::string& asset_path = asset.resource();
		const std::string result = P(asset_path);
		eps::asset_read_operation_stream opt(result.c_str());

		if (asset.load(&opt))
		{
			return true;
		}

		return false;
	}

	bool visit(eps::asset_xml& asset) final
	{
		const std::string& asset_path = asset.resource();
		const std::string result = P(asset_path);
		eps::asset_read_operation_stream opt(result.c_str());

		if (asset.load(&opt))
		{
			return true;
		}

		return false;
	}

private:
	std::string root_;
};
