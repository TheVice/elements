#ifndef _LIGHT_SCATTERED_SETTINGS_H_
#define _LIGHT_SCATTERED_SETTINGS_H_

#include "LightScatteredVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct LightScatteredSettings : public eps::asset_xml
{
public:
	std::vector<LightScatteredVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_occluding;
	float u_exposure;
	float u_decay;
	float u_density;
	float u_weight;
	eps::math::vec2 u_light_position;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
