#ifndef _MODEL_VERTEX_H_
#define _MODEL_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct ModelVertex
{
	eps::math::vec3 a_vertex_pos;
	eps::math::vec3 a_vertex_normal;
	eps::math::vec3 a_vertex_tangent;
	eps::math::vec2 a_vertex_uv;

	ModelVertex() :
		a_vertex_pos(),
		a_vertex_normal(),
		a_vertex_tangent(),
		a_vertex_uv()
	{
	}

	ModelVertex(
		const eps::math::vec3& argument_a_vertex_pos,
		const eps::math::vec3& argument_a_vertex_normal,
		const eps::math::vec3& argument_a_vertex_tangent,
		const eps::math::vec2& argument_a_vertex_uv) :
		a_vertex_pos(argument_a_vertex_pos),
		a_vertex_normal(argument_a_vertex_normal),
		a_vertex_tangent(argument_a_vertex_tangent),
		a_vertex_uv(argument_a_vertex_uv)
	{
	}
};
}

#endif
