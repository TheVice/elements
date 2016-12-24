#ifndef _LIQUID_SETTINGS_H_
#define _LIQUID_SETTINGS_H_

#include "LiquidVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct LiquidSettings : public eps::asset_xml
{
public:
	std::vector<LiquidVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_surface;
	std::string u_surface_background;
	eps::math::vec4 u_surface_color;
	eps::math::vec2 u_surface_texel;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
