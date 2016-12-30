#ifndef _POSITIONS_RESET_VERTEX_H_
#define _POSITIONS_RESET_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct PositionsResetVertex
{
	eps::math::vec2 a_vertex_xy;

	PositionsResetVertex() :
		a_vertex_xy()
	{
	}

	PositionsResetVertex(
		const eps::math::vec2& argument_a_vertex_xy) :
		a_vertex_xy(argument_a_vertex_xy)
	{
	}
};
}

#endif

