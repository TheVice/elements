
#include "desktop_asset_reader.h"

desktop_asset_reader::desktop_asset_reader()
{
}

desktop_asset_reader::~desktop_asset_reader()
{
}

bool desktop_asset_reader::visit(eps::asset_texture& asset)
{
	// path to asset, for example "shaders/experiments/air/particles.prog"
	const std::string& asset_path = asset.resource();
	// normalize in platform specific ('/' or '\\')
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

bool desktop_asset_reader::visit(eps::asset_blob& asset)
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

bool desktop_asset_reader::visit(eps::asset_xml& asset)
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
