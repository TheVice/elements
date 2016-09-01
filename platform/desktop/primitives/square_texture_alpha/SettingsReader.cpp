#ifdef A
#include "SettingsReader.h"
#include "ReaderHelpers.h"
#include "assets/assets_storage.h"

bool SettingsReader::read(const pugi::xml_document& doc)
{
	mIsEmpty = true;
	pugi::xml_node root_node = doc.child("program");

	if (root_node.empty())
	{
		return false;
	}

	if (!read_glm_mat4(root_node.child("transform"), mTransform))
	{
		return false;
	}

	if (!read_glm_vec4(root_node.child("color"), mColor))
	{
		return false;
	}

	mIsEmpty = false;
	return true;
}

bool load_data(const char* demo_data_asset, SettingsReader& demo_data)
{
	auto data = eps::assets_storage::instance().read<SettingsReader>(demo_data_asset);

	if (!data || data.value().mIsEmpty)
	{
		return false;
	}

	demo_data.mTransform = data.value().mTransform;
	demo_data.mColor = data.value().mColor;
	return true;
}
#endif
