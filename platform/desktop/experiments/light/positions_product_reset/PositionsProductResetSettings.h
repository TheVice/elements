#ifndef _POSITIONS_PRODUCT_RESET_SETTINGS_H_
#define _POSITIONS_PRODUCT_RESET_SETTINGS_H_

#include "PositionsProductResetVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct PositionsProductResetSettings : public eps::asset_xml
{
public:
	std::vector<PositionsProductResetVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_displacement;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
