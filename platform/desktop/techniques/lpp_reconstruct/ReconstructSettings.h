#ifndef _RECONSTRUCT_SETTINGS_H_
#define _RECONSTRUCT_SETTINGS_H_

#include "ReconstructVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct ReconstructSettings : public eps::asset_xml
{
public:
	std::vector<ReconstructVertex> mVertices;
	std::vector<unsigned char> mIndices;

	eps::math::mat4 u_matrix_mvp;
	std::string u_map_light;
	std::string u_map_diffuse;
	std::string u_map_specular;
	bool u_has_map_diffuse;
	bool u_has_map_specular;
	eps::math::vec3 u_color_diffuse;
	eps::math::vec3 u_color_specular;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
