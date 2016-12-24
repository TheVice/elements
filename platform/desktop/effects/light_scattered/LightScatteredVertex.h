#ifndef _LIGHT_SCATTERED_VERTEX_H_
#define _LIGHT_SCATTERED_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct LightScatteredVertex
{
	eps::math::vec2 a_vertex_xy;
	eps::math::vec2 a_vertex_uv;

	LightScatteredVertex() :
		a_vertex_xy(),
		a_vertex_uv()
	{
	}

	LightScatteredVertex(
		const eps::math::vec2& argument_a_vertex_xy,
		const eps::math::vec2& argument_a_vertex_uv) :
		a_vertex_xy(argument_a_vertex_xy),
		a_vertex_uv(argument_a_vertex_uv)
	{
	}
};
}

#endif
