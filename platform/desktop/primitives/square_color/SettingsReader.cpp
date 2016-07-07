
#include "SettingsReader.h"
#include "assets/assets_storage.h"
#include <cstdlib>
#include <iostream>

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

	pugi::xml_node color_node = root_node.child("color");

	if (color_node.empty())
	{
		return false;
	}

	if (color_node.child("x").first_child().empty())
	{
		return false;
	}

	if (color_node.child("y").first_child().empty())
	{
		return false;
	}

	if (color_node.child("z").first_child().empty())
	{
		return false;
	}

	if (color_node.child("w").first_child().empty())
	{
		return false;
	}

	{
		float x = std::atof(position_node.child("x").first_child().value());
		float y = std::atof(position_node.child("y").first_child().value());
		//
		mPosition = { x, y };
	}

	{
		float x = std::atof(color_node.child("x").first_child().value());
		float y = std::atof(color_node.child("y").first_child().value());
		float z = std::atof(color_node.child("z").first_child().value());
		float w = std::atof(color_node.child("w").first_child().value());
		//
		mColor = { x, y, z, w };
	}

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
	demo_data.mColor = data.mColor;
	return true;
}
