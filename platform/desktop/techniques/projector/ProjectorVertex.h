#ifndef _VERTEX_STRUCTURE_H_
#define _VERTEX_STRUCTURE_H_

#include <elements/math/types.h>

namespace Rendering
{
struct ProjectorVertex
{
	eps::math::vec3 a_vertex_pos;

	ProjectorVertex() :
		a_vertex_pos()
	{
	}

	ProjectorVertex(
		const eps::math::vec3& argument_a_vertex_pos) :
		a_vertex_pos(argument_a_vertex_pos)
	{
	}
};
}

#endif
