
#include "DeferredEffect.h"
#include "VertexStructure.h"

namespace Library
{
RTTI_DEFINITIONS(DeferredEffect)

SHADER_VARIABLE_DEFINITION(DeferredEffect, u_matrix_mvp)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_matrix_model_view)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_matrix_normal)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_matrix_view)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_camera_pos)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_map_diffuse)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_map_specular)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_map_normal)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_light_pos)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_light_diffuse)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_light_specular)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_light_ambient)
SHADER_VARIABLE_DEFINITION(DeferredEffect, u_light_range)

DeferredEffect::DeferredEffect() :
	ShaderProgram(),
	SHADER_VARIABLE_INITIALIZATION(u_matrix_mvp),
	SHADER_VARIABLE_INITIALIZATION(u_matrix_model_view),
	SHADER_VARIABLE_INITIALIZATION(u_matrix_normal),
	SHADER_VARIABLE_INITIALIZATION(u_matrix_view),
	SHADER_VARIABLE_INITIALIZATION(u_camera_pos),
	SHADER_VARIABLE_INITIALIZATION(u_map_diffuse),
	SHADER_VARIABLE_INITIALIZATION(u_map_specular),
	SHADER_VARIABLE_INITIALIZATION(u_map_normal),
	SHADER_VARIABLE_INITIALIZATION(u_light_pos),
	SHADER_VARIABLE_INITIALIZATION(u_light_diffuse),
	SHADER_VARIABLE_INITIALIZATION(u_light_specular),
	SHADER_VARIABLE_INITIALIZATION(u_light_ambient),
	SHADER_VARIABLE_INITIALIZATION(u_light_range)
{
}

GLvoid DeferredEffect::Initialize(GLuint aVertexArrayObject)
{
	ShaderProgram::Initialize(aVertexArrayObject);
	//
	SHADER_VARIABLE_INSTANTIATE(u_matrix_mvp)
	SHADER_VARIABLE_INSTANTIATE(u_matrix_model_view)
	SHADER_VARIABLE_INSTANTIATE(u_matrix_normal)
	SHADER_VARIABLE_INSTANTIATE(u_matrix_view)
	SHADER_VARIABLE_INSTANTIATE(u_camera_pos)
	SHADER_VARIABLE_INSTANTIATE(u_map_diffuse)
	SHADER_VARIABLE_INSTANTIATE(u_map_specular)
	SHADER_VARIABLE_INSTANTIATE(u_map_normal)
	SHADER_VARIABLE_INSTANTIATE(u_light_pos)
	SHADER_VARIABLE_INSTANTIATE(u_light_diffuse)
	SHADER_VARIABLE_INSTANTIATE(u_light_specular)
	SHADER_VARIABLE_INSTANTIATE(u_light_ambient)
	SHADER_VARIABLE_INSTANTIATE(u_light_range)
	//
	const GLint vertexAttribute_a_vertex_pos = GetAttrib("a_vertex_pos");
	const GLint vertexAttribute_a_vertex_normal = GetAttrib("a_vertex_normal");
	const GLint vertexAttribute_a_vertex_tangent = GetAttrib("a_vertex_tangent");
	const GLint vertexAttribute_a_vertex_uv = GetAttrib("a_vertex_uv");
	//
	glVertexAttribPointer(vertexAttribute_a_vertex_pos, glm::vec3().length(), GL_FLOAT, GL_FALSE,
						  GetVertexSize(),
						  reinterpret_cast<GLvoid*>(offsetof(VertexStructure, a_vertex_pos)));
	glEnableVertexAttribArray(vertexAttribute_a_vertex_pos);
	//
	glVertexAttribPointer(vertexAttribute_a_vertex_normal, glm::vec3().length(), GL_FLOAT, GL_FALSE,
						  GetVertexSize(),
						  reinterpret_cast<GLvoid*>(offsetof(VertexStructure, a_vertex_normal)));
	glEnableVertexAttribArray(vertexAttribute_a_vertex_normal);
	//
	glVertexAttribPointer(vertexAttribute_a_vertex_tangent, glm::vec3().length(), GL_FLOAT, GL_FALSE,
						  GetVertexSize(),
						  reinterpret_cast<GLvoid*>(offsetof(VertexStructure, a_vertex_tangent)));
	glEnableVertexAttribArray(vertexAttribute_a_vertex_tangent);
	//
	glVertexAttribPointer(vertexAttribute_a_vertex_uv, glm::vec2().length(), GL_FLOAT, GL_FALSE,
						  GetVertexSize(),
						  reinterpret_cast<GLvoid*>(offsetof(VertexStructure, a_vertex_uv)));
	glEnableVertexAttribArray(vertexAttribute_a_vertex_uv);
}

GLuint DeferredEffect::GetVertexSize() const
{
	return sizeof(VertexStructure);
}

}
