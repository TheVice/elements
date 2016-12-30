#ifndef _GRADIENT_MAPPING_SETTINGS_H_
#define _GRADIENT_MAPPING_SETTINGS_H_

#include "GradientMappingVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct GradientMappingSettings : public eps::asset_xml
{
public:
	std::vector<GradientMappingVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_source;
	eps::math::vec3 u_color_1;
	eps::math::vec3 u_color_2;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
