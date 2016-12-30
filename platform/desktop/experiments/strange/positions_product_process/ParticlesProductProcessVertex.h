#ifndef _PARTICLES_PRODUCT_PROCESS_VERTEX_H_
#define _PARTICLES_PRODUCT_PROCESS_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct ParticlesProductProcessVertex
{
	eps::math::vec2 a_vertex_xy;

	ParticlesProductProcessVertex() :
		a_vertex_xy()
	{
	}

	ParticlesProductProcessVertex(
		const eps::math::vec2& argument_a_vertex_xy) :
		a_vertex_xy(argument_a_vertex_xy)
	{
	}
};
}

#endif

