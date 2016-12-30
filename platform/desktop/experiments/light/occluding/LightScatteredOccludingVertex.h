#ifndef _LIGHT_SCATTERED_OCCLUDING_VERTEX_H_
#define _LIGHT_SCATTERED_OCCLUDING_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct LightScatteredOccludingVertex
{
	eps::math::vec2 a_product_uv;

	LightScatteredOccludingVertex() :
		a_product_uv()
	{
	}

	LightScatteredOccludingVertex(
		const eps::math::vec2& argument_a_product_uv) :
		a_product_uv(argument_a_product_uv)
	{
	}
};
}

#endif

