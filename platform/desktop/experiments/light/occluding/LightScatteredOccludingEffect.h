#ifndef _LIGHT_SCATTERED_OCCLUDING_EFFECT_H_
#define _LIGHT_SCATTERED_OCCLUDING_EFFECT_H_

#include "LightScatteredOccludingVertex.h"
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
class LightScatteredOccludingEffect
{
public:
	explicit LightScatteredOccludingEffect(const std::vector<LightScatteredOccludingVertex>& vertices,
										   const std::vector<GLubyte>& indices,
										   eps::rendering::buffer_usage usage = eps::rendering::buffer_usage::STATIC_DRAW);

	void construct(const std::vector<LightScatteredOccludingVertex>& vertices);
	void render(eps::rendering::program& program, short a_position, short index_count);

private:
	eps::rendering::vertices texture_vertices_;
	eps::rendering::indices texture_indices_;
};
}

#endif

