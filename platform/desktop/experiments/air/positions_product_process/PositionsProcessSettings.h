#ifndef _POSITIONS_PROCESS_SETTINGS_H_
#define _POSITIONS_PROCESS_SETTINGS_H_

#include "PositionsProcessVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct PositionsProcessSettings : public eps::asset_xml
{
public:
	std::vector<PositionsProcessVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_positions;
	std::string u_velocities;
	float u_dt;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
