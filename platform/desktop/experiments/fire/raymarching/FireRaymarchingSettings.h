#ifndef _FIRE_RAYMARCHING_SETTINGS_H_
#define _FIRE_RAYMARCHING_SETTINGS_H_

#include "FireRaymarchingVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct FireRaymarchingSettings : public eps::asset_xml
{
public:
	std::vector<FireRaymarchingVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_noise;
	float u_dt;
	float u_intensity;
	float u_covering;
	eps::math::vec2 u_texel;
	eps::math::vec3 u_color_hot;
	eps::math::vec3 u_color_cold;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
