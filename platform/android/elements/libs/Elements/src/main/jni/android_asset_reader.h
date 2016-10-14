#ifndef _ANDROID_ASSET_READER_H_
#define _ANDROID_ASSET_READER_H_

#include "elements/assets/assets_storage.h"
#include <map>

namespace eps
{
struct asset_blob;
struct asset_texture;
struct asset_xml;
}

struct android_asset_reader : public eps::asset_reader
{
	explicit android_asset_reader();

	bool visit(eps::asset_blob& asset) final;
	bool visit(eps::asset_texture& asset) final;
	bool visit(eps::asset_xml& asset) final;

	static std::map<std::string, std::string> assets_;
};

#endif
