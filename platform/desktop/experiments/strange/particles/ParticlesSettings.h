#ifndef _PARTICLES_SETTINGS_H_
#define _PARTICLES_SETTINGS_H_

#include "ParticlesVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct ParticlesSettings : public eps::asset_xml
{
public:
	std::vector<ParticlesVertex> mVertices;
	std::vector<unsigned char> mIndices;

	std::string u_positions;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif