#ifndef _SQUARE_COLOR_CIRCLE_SETTINGS_H_
#define _SQUARE_COLOR_CIRCLE_SETTINGS_H_

#include "SquareColorCircleVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>

namespace Rendering
{
struct SquareColorCircleSettings : public eps::asset_xml
{
public:
	std::vector<SquareColorCircleVertex> mVertices;
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
