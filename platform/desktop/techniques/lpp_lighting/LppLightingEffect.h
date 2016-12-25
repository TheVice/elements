#ifndef _LPP_LIGHTING_EFFECT_H_
#define _LPP_LIGHTING_EFFECT_H_

#include "LppLightingVertex.h"
#include <elements/rendering/core/buffer.h>
#include <vector>


namespace eps
{
namespace rendering
{
class program;
}
}

namespace Rendering
{
class LppLightingEffect
{
public:
	explicit LppLightingEffect(const std::vector<LppLightingVertex>& vertices,
							   const std::vector<GLubyte>& indices,
							   eps::rendering::buffer_usage usage = eps::rendering::buffer_usage::STATIC_DRAW);

	void construct(const std::vector<LppLightingVertex>& vertices);
	void render(eps::rendering::program& program, short a_position, short index_count);

private:
	eps::rendering::vertices texture_vertices_;
	eps::rendering::indices texture_indices_;
};
}

#endif

