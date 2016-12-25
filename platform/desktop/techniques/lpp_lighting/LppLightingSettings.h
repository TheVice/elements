#ifndef _LPP_LIGHTING_SETTINGS_H_
#define _LPP_LIGHTING_SETTINGS_H_

#include "LppLightingVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct LppLightingSettings : public eps::asset_xml
{
public:
	std::vector<LppLightingVertex> mVertices;
	std::vector<unsigned char> mIndices;

	eps::math::mat4 u_matrix_mvp;
	eps::math::vec2 u_camera_view_param;
	float u_camera_near;
	float u_camera_far;
	std::string u_map_geometry;
	std::string u_map_depth;
	eps::math::vec3 u_light_pos;
	eps::math::vec3 u_light_intensity;
	float u_light_inv_range_square;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
