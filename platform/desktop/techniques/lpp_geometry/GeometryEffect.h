#ifndef _GEOMETRY_EFFECT_H_
#define _GEOMETRY_EFFECT_H_

#include "GeometryVertex.h"
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
class GeometryEffect
{
public:
	explicit GeometryEffect(const std::vector<GeometryVertex>& vertices,
							const std::vector<GLubyte>& indices,
							eps::rendering::buffer_usage usage = eps::rendering::buffer_usage::STATIC_DRAW);

	void construct(const std::vector<GeometryVertex>& vertices);
	void render(eps::rendering::program& program, const std::array<short, 4>& a_position, short index_count);

private:
	eps::rendering::vertices texture_vertices_;
	eps::rendering::indices texture_indices_;
};
}

#endif
