#ifndef _VERTEX_STRUCTURE_H_
#define _VERTEX_STRUCTURE_H_

#include <glm/glm.hpp>

namespace Rendering
{
struct VertexStructure
{
	glm::vec3 a_vertex_pos;

	VertexStructure() :
		a_vertex_pos()
	{
	}

	VertexStructure(
		const glm::vec3& argument_a_vertex_pos) :
		a_vertex_pos(argument_a_vertex_pos)
	{
	}
};
}

#endif
