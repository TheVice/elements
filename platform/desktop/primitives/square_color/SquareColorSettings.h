#ifndef _SQUARE_COLOR_SETTINGS_H_
#define _SQUARE_COLOR_SETTINGS_H_

#include "SquareColorVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>

namespace Rendering
{
struct SquareColorSettings : public eps::asset_xml
{
public:
	std::vector<SquareColorVertex> mVertices;
	std::vector<unsigned char> mIndices;

	eps::math::mat4 u_transform;
	eps::math::vec4 u_color;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
