#ifndef _LPP_LIGHTING_STENCIL_SETTINGS_H_
#define _LPP_LIGHTING_STENCIL_SETTINGS_H_

#include "LppLightingStencilVertex.h"
#include <elements/math/types.h>
#include <elements/assets/asset_xml.h>
#include <vector>
#include <string>

namespace Rendering
{
struct LppLightingStencilSettings : public eps::asset_xml
{
public:
	std::vector<LppLightingStencilVertex> mVertices;
	std::vector<unsigned char> mIndices;

	eps::math::mat4 u_matrix_mvp;

	bool mIsEmpty;

public:
	using eps::asset_xml::asset_xml;

private:
	bool read(const pugi::xml_document& doc) final;
};
}

#endif
