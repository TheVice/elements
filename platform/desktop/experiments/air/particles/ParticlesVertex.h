#ifndef _PARTICLES_VERTEX_H_
#define _PARTICLES_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct ParticlesVertex
{
	eps::math::vec2 a_product_uv;

	ParticlesVertex() :
		a_product_uv()
	{
	}

	ParticlesVertex(
		const eps::math::vec2& argument_a_product_uv) :
		a_product_uv(argument_a_product_uv)
	{
	}
};
}

#endif

