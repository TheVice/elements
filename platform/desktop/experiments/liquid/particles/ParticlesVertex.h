#ifndef _PARTICLES_VERTEX_H_
#define _PARTICLES_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct ParticlesVertex
{
	eps::math::vec2 a_vertex_xy;

	ParticlesVertex() :
		a_vertex_xy()
	{
	}

	ParticlesVertex(
		const eps::math::vec2& argument_a_vertex_xy) :
		a_vertex_xy(argument_a_vertex_xy)
	{
	}
};
}

#endif
