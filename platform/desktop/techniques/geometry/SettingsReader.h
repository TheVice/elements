#ifndef _SETTINGS_READER_H_
#define _SETTINGS_READER_H_

#include "assets/asset_xml.h"
#include "VertexStructure.h"
#include <vector>

struct SettingsReader : public eps::asset_xml
{
public:

	std::vector<VertexStructure> mVertices;
	glm::mat4 mMatrixMvp;
	glm::mat3 mMatrixNormal;
	std::string mTexturePath;
	bool mIsEmpty;

public:

	using eps::asset_xml::asset_xml;

private:

	bool read(const pugi::xml_document& doc) final;
};

bool load_data(const char* demo_data_asset, SettingsReader& demo_data);

#endif
