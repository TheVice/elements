#ifndef _PROJECTOR_SETTINGS_H_
#define _PROJECTOR_SETTINGS_H_

#include "VertexStructure.h"
#include <elements/assets/asset_xml.h>
#include <vector>

namespace Rendering
{
struct ProjectorSettings : public eps::asset_xml
{
public:
	std::vector<VertexStructure> mVertices;
	std::vector<unsigned char> mIndices;

	glm::mat4 u_matrix_mvp;
	glm::mat4 u_matrix_model;
	glm::mat4 u_matrix_pvp;
	std::string u_map_projective;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
