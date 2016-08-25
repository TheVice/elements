#ifndef _VERTEX_STRUCTURE_H_
#define _VERTEX_STRUCTURE_H_

#include <glm/glm.hpp>

struct VertexStructure
{
	glm::vec2 a_vertex_xy;

	VertexStructure() :
		a_vertex_xy()
	{
	}

	VertexStructure(
		const glm::vec2& argument_a_vertex_xy) :
		a_vertex_xy(argument_a_vertex_xy)
	{
	}
};

#endif
