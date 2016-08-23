#ifndef _VERTEX_STRUCTURE_H_
#define _VERTEX_STRUCTURE_H_

#include <glm/glm.hpp>

struct VertexStructure
{
	glm::vec3 a_vertex_pos;
	glm::vec3 a_vertex_normal;
	glm::vec3 a_vertex_tangent;
	glm::vec2 a_vertex_uv;

	VertexStructure() :
		a_vertex_pos(),
		a_vertex_normal(),
		a_vertex_tangent(),
		a_vertex_uv()
	{
	}

	VertexStructure(
		const glm::vec3& argument_a_vertex_pos,
		const glm::vec3& argument_a_vertex_normal,
		const glm::vec3& argument_a_vertex_tangent,
		const glm::vec2& argument_a_vertex_uv) :
		a_vertex_pos(argument_a_vertex_pos),
		a_vertex_normal(argument_a_vertex_normal),
		a_vertex_tangent(argument_a_vertex_tangent),
		a_vertex_uv(argument_a_vertex_uv)
	{
	}
};

#endif
