
#include "desktop_asset_reader.h"

my_asset_reader::my_asset_reader(std::string& root)
	: asset_reader(*this),
	  root_(root)
{
}

my_asset_reader::~my_asset_reader()
{
}
