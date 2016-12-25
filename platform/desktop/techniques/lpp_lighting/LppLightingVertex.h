#ifndef _LPP_LIGHTING_VERTEX_H_
#define _LPP_LIGHTING_VERTEX_H_

#include <elements/math/types.h>

namespace Rendering
{
struct LppLightingVertex
{
	eps::math::vec3 a_vertex_pos;

	LppLightingVertex() :
		a_vertex_pos()
	{
	}

	LppLightingVertex(
		const eps::math::vec3& argument_a_vertex_pos) :
		a_vertex_pos(argument_a_vertex_pos)
	{
	}
};
}

#endif

