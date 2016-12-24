#ifndef _SQUARE_TEXTURE_SETTINGS_H_
#define _SQUARE_TEXTURE_SETTINGS_H_

#include "SquareTextureVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct SquareTextureSettings : public eps::asset_xml
{
public:
	std::vector<SquareTextureVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_source;
	eps::math::mat4 u_transform;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
