#ifndef _VELOCITIES_PROCESS_SETTINGS_H_
#define _VELOCITIES_PROCESS_SETTINGS_H_

#include "VelocitiesProcessVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct VelocitiesProcessSettings : public eps::asset_xml
{
public:
	std::vector<VelocitiesProcessVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_product;
	float u_dt;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
