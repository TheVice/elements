#ifndef _VELOCITIES_RESET_VERTEX_H_
#define _VELOCITIES_RESET_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct VelocitiesResetVertex
{
	eps::math::vec2 a_vertex_xy;

	VelocitiesResetVertex() :
		a_vertex_xy()
	{
	}

	VelocitiesResetVertex(
		const eps::math::vec2& argument_a_vertex_xy) :
		a_vertex_xy(argument_a_vertex_xy)
	{
	}
};
}

#endif

