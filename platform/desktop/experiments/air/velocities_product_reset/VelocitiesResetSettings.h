#ifndef _VELOCITIES_RESET_SETTINGS_H_
#define _VELOCITIES_RESET_SETTINGS_H_

#include "VelocitiesResetVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct VelocitiesResetSettings : public eps::asset_xml
{
public:
	std::vector<VelocitiesResetVertex> mVertices;
	std::vector<unsigned char> mIndices;



	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
