#ifndef _SETTINGS_READER_H_
#define _SETTINGS_READER_H_

#include "VertexStructure.h"
#include <elements/assets/asset_xml.h>
#include <vector>

struct SettingsReader : public eps::asset_xml
{
public:

	std::vector<VertexStructure> mVertices;
	std::vector<unsigned int> mIndices;
	glm::mat4 mTransform;
	float mSize;
	bool mIsEmpty;

public:

	using eps::asset_xml::asset_xml;

private:

	bool read(const pugi::xml_document& doc) final;
};

#endif
