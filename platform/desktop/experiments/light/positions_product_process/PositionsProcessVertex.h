#ifndef _POSITIONS_PROCESS_VERTEX_H_
#define _POSITIONS_PROCESS_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct PositionsProcessVertex
{
	eps::math::vec2 a_vertex_xy;

	PositionsProcessVertex() :
		a_vertex_xy()
	{
	}

	PositionsProcessVertex(
		const eps::math::vec2& argument_a_vertex_xy) :
		a_vertex_xy(argument_a_vertex_xy)
	{
	}
};
}

#endif

