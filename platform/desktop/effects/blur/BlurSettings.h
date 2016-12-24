#ifndef _BLUR_SETTINGS_H_
#define _BLUR_SETTINGS_H_

#include "BlurVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct BlurSettings : public eps::asset_xml
{
public:
	std::vector<BlurVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_source;
	eps::math::vec2 u_offset;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
