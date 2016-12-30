#ifndef _PARTICLES_PRODUCT_PROCESS_SETTINGS_H_
#define _PARTICLES_PRODUCT_PROCESS_SETTINGS_H_

#include "ParticlesProductProcessVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct ParticlesProductProcessSettings : public eps::asset_xml
{
public:
	std::vector<ParticlesProductProcessVertex> mVertices;
	std::vector<unsigned char> mIndices;

	float u_attractor_a;
	float u_attractor_b;
	float u_attractor_c;
	float u_attractor_d;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
