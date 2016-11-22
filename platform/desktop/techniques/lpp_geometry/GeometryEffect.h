#ifndef _GEOMETRY_EFFECT_H_
#define _GEOMETRY_EFFECT_H_

#include <ShaderProgram.h>

namespace Library
{
class GeometryEffect : public ShaderProgram
{
	RTTI_DECLARATIONS(GeometryEffect, ShaderProgram)

	SHADER_VARIABLE_DECLARATION(u_matrix_mvp)
	SHADER_VARIABLE_DECLARATION(u_matrix_normal)
	//SHADER_VARIABLE_DECLARATION(u_map_normal)

public:
	GeometryEffect();

public:
	GeometryEffect(const GeometryEffect& aRhs) = delete;
	GeometryEffect& operator = (const GeometryEffect& aRhs) = delete;

public:
	virtual GLvoid Initialize(GLuint aVertexArrayObject) override;
	virtual GLuint GetVertexSize() const override;
};
}

#endif
