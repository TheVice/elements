#ifndef _POSITIONS_RESET_SETTINGS_H_
#define _POSITIONS_RESET_SETTINGS_H_

#include "PositionsResetVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct PositionsResetSettings : public eps::asset_xml
{
public:
	std::vector<PositionsResetVertex> mVertices;
	std::vector<unsigned char> mIndices;



	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
