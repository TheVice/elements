#ifndef _FIRE_SETTINGS_H_
#define _FIRE_SETTINGS_H_

#include "FireVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct FireSettings : public eps::asset_xml
{
public:
	std::vector<FireVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_fire;
	std::string u_background;
	eps::math::vec2 u_texel;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
