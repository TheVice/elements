#ifndef _SETTINGS_READER_H_
#define _SETTINGS_READER_H_

#include "VertexStructure.h"
#include <elements/assets/asset_xml.h>
#include <vector>

namespace Rendering
{
struct SettingsReader : public eps::asset_xml
{
public:

	std::vector<VertexStructure> mVertices;
	std::vector<unsigned char> mIndices;
	glm::mat4 mMatrixMvp;
	glm::mat3 mMatrixNormal;
	std::string mTexturePath;
	bool mIsEmpty;

public:

	using eps::asset_xml::asset_xml;

private:

	bool read(const pugi::xml_document& doc) final;
};
}

#endif
