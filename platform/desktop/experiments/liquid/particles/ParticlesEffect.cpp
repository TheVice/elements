
#include "ParticlesEffect.h"
#include "VertexStructure.h"

namespace Library
{
RTTI_DEFINITIONS(ParticlesEffect)

SHADER_VARIABLE_DEFINITION(ParticlesEffect, u_transform)
SHADER_VARIABLE_DEFINITION(ParticlesEffect, u_size)

ParticlesEffect::ParticlesEffect() :
	ShaderProgram(),
	SHADER_VARIABLE_INITIALIZATION(u_transform),
	SHADER_VARIABLE_INITIALIZATION(u_size)
{
}

GLvoid ParticlesEffect::Initialize(GLuint aVertexArrayObject)
{
	ShaderProgram::Initialize(aVertexArrayObject);
	//
	SHADER_VARIABLE_INSTANTIATE(u_transform)
	SHADER_VARIABLE_INSTANTIATE(u_size)
	//
	const GLint vertexAttribute_a_vertex_xy = GetAttrib("a_vertex_xy");
	//
	glVertexAttribPointer(vertexAttribute_a_vertex_xy, glm::vec2().length(), GL_FLOAT, GL_FALSE,
						  GetVertexSize(),
						  reinterpret_cast<GLvoid*>(offsetof(VertexStructure, a_vertex_xy)));
	glEnableVertexAttribArray(vertexAttribute_a_vertex_xy);
}

GLuint ParticlesEffect::GetVertexSize() const
{
	return sizeof(VertexStructure);
}

}
