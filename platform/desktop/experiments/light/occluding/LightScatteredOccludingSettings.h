#ifndef _LIGHT_SCATTERED_OCCLUDING_SETTINGS_H_
#define _LIGHT_SCATTERED_OCCLUDING_SETTINGS_H_

#include "LightScatteredOccludingVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct LightScatteredOccludingSettings : public eps::asset_xml
{
public:
	std::vector<LightScatteredOccludingVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_positions;
	float u_size;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
