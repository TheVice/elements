
#include "SettingsReader.h"
#include "assets/assets_storage.h"
#include <cstdlib>

bool read_glm_vec2(const pugi::xml_node& aNode, glm::vec2& aValue)
{
	if (aNode.empty())
	{
		return false;
	}

	if (aNode.child("x").first_child().empty())
	{
		return false;
	}

	if (aNode.child("y").first_child().empty())
	{
		return false;
	}

	aValue.x = std::atof(aNode.child("x").first_child().value());
	aValue.y = std::atof(aNode.child("y").first_child().value());
	//
	return true;
}

bool SettingsReader::read(const pugi::xml_document& doc)
{
	mIsEmpty = true;
	pugi::xml_node root_node = doc.child("program");

	if (root_node.empty())
	{
		return false;
	}

	pugi::xml_node exposure_node = root_node.child("exposure");

	if (exposure_node.empty())
	{
		return false;
	}

	mExposure = std::atof(exposure_node.child_value());
	pugi::xml_node decay_node = root_node.child("decay");

	if (decay_node.empty())
	{
		return false;
	}

	mDecay = std::atof(decay_node.child_value());
	pugi::xml_node density_node = root_node.child("density");

	if (density_node.empty())
	{
		return false;
	}

	mDensity = std::atof(density_node.child_value());
	pugi::xml_node weigh_node = root_node.child("weight");

	if (weigh_node.empty())
	{
		return false;
	}

	mWeight = std::atof(weigh_node.child_value());

	if (!read_glm_vec2(root_node.child("light_position"), mLightPosition))
	{
		return false;
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

	demo_data.mExposure = data.mExposure;
	demo_data.mDecay = data.mDecay;
	demo_data.mDensity = data.mDensity;
	demo_data.mWeight = data.mWeight;
	demo_data.mLightPosition = data.mLightPosition;
	return true;
}
