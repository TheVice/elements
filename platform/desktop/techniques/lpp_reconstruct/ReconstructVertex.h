#ifndef _RECONSTRUCT_VERTEX_H_
#define _RECONSTRUCT_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct ReconstructVertex
{
	eps::math::vec3 a_vertex_pos;
	eps::math::vec2 a_vertex_uv;

	ReconstructVertex() :
		a_vertex_pos(),
		a_vertex_uv()
	{
	}

	ReconstructVertex(
		const eps::math::vec3& argument_a_vertex_pos,
		const eps::math::vec2& argument_a_vertex_uv) :
		a_vertex_pos(argument_a_vertex_pos),
		a_vertex_uv(argument_a_vertex_uv)
	{
	}
};
}

#endif

