
#include "SettingsReader.h"
#include "assets/assets_storage.h"
#include <cstdlib>

bool SettingsReader::read(const pugi::xml_document& doc)
{
	mIsEmpty = true;
	pugi::xml_node root_node = doc.child("program");

	if (root_node.empty())
	{
		return false;
	}

	pugi::xml_node position_node = root_node.child("position");

	if (position_node.empty())
	{
		return false;
	}

	if (position_node.child("x").first_child().empty())
	{
		return false;
	}

	if (position_node.child("y").first_child().empty())
	{
		return false;
	}

	pugi::xml_node size_node = root_node.child("size");

	if (size_node.empty())
	{
		return false;
	}

	{
		float x = std::atof(position_node.child("x").first_child().value());
		float y = std::atof(position_node.child("y").first_child().value());
		//
		mPosition = { x, y };
	}

	mSize = std::atof(size_node.child_value());
	mIsEmpty = false;
	return true;
}

bool load_data(const char* demo_data_asset, SettingsReader& demo_data)
{
	auto data = eps::assets_storage::instance().read<SettingsReader>(demo_data_asset);

	if (data.mIsEmpty)
	{
		return false;
	}

	demo_data.mPosition = data.mPosition;
	demo_data.mSize = data.mSize;
	return true;
}
