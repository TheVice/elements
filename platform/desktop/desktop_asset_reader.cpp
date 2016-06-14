
#include "desktop_asset_reader.h"

desktop_asset_reader::desktop_asset_reader(std::string& root)
	: asset_reader(*this),
	  root_(root)
{
}

desktop_asset_reader::~desktop_asset_reader()
{
}
