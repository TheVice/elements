#ifndef _POSITIONS_PRODUCT_RESET_VERTEX_H_
#define _POSITIONS_PRODUCT_RESET_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct PositionsProductResetVertex
{
	eps::math::vec2 a_vertex_xy;

	PositionsProductResetVertex() :
		a_vertex_xy()
	{
	}

	PositionsProductResetVertex(
		const eps::math::vec2& argument_a_vertex_xy) :
		a_vertex_xy(argument_a_vertex_xy)
	{
	}
};
}

#endif

