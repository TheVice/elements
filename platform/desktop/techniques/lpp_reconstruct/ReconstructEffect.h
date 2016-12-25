#ifndef _RECONSTRUCT_EFFECT_H_
#define _RECONSTRUCT_EFFECT_H_

#include "ReconstructVertex.h"
#include <elements/rendering/core/buffer.h>
#include <vector>
#include <array>

namespace eps
{
namespace rendering
{
class program;
}
}

namespace Rendering
{
class ReconstructEffect
{
public:
	explicit ReconstructEffect(const std::vector<ReconstructVertex>& vertices,
							   const std::vector<GLubyte>& indices,
							   eps::rendering::buffer_usage usage = eps::rendering::buffer_usage::STATIC_DRAW);

	void construct(const std::vector<ReconstructVertex>& vertices);
	void render(eps::rendering::program& program, const std::array<short, 2>& a_position, short index_count);

private:
	eps::rendering::vertices texture_vertices_;
	eps::rendering::indices texture_indices_;
};
}

#endif

