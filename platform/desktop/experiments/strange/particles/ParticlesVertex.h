#ifndef _PARTICLES_VERTEX_H_
#define _PARTICLES_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct ParticlesVertex
{
	eps::math::vec2 a_positions_uv;

	ParticlesVertex() :
		a_positions_uv()
	{
	}

	ParticlesVertex(
		const eps::math::vec2& argument_a_positions_uv) :
		a_positions_uv(argument_a_positions_uv)
	{
	}
};
}

#endif

