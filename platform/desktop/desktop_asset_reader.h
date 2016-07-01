#ifndef _DESKTOP_ASSET_READER_H_
#define _DESKTOP_ASSET_READER_H_

#include "elements/assets/assets_storage.h"
#include "elements/assets/asset_texture.h"
#include "elements/assets/asset_blob.h"
#include "elements/assets/asset_xml.h"
#include "elements/assets/asset_operations_stream.h"
#include "Utility.h"

struct desktop_asset_reader : public eps::asset_reader
{
	explicit desktop_asset_reader();

	bool visit(eps::asset_texture& asset) final;
	bool visit(eps::asset_blob& asset) final;
	bool visit(eps::asset_xml& asset) final;
};

#endif