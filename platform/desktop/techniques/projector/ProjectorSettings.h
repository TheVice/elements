#ifndef _PROJECTOR_SETTINGS_H_
#define _PROJECTOR_SETTINGS_H_

#include "ProjectorVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct ProjectorSettings : public eps::asset_xml
{
public:
	std::vector<ProjectorVertex> mVertices;
	std::vector<unsigned char> mIndices;

	eps::math::mat4 u_matrix_mvp;
	eps::math::mat4 u_matrix_model;
	eps::math::mat4 u_matrix_pvp;
	std::string u_map_projective;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
