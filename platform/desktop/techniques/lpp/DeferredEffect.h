#ifndef _DEFERRED_EFFECT_H_
#define _DEFERRED_EFFECT_H_

#include "ShaderProgram.h"

namespace Library
{
class DeferredEffect : public ShaderProgram
{
	RTTI_DECLARATIONS(DeferredEffect, ShaderProgram)

	SHADER_VARIABLE_DECLARATION(u_matrix_mvp)
	SHADER_VARIABLE_DECLARATION(u_matrix_model_view)
	SHADER_VARIABLE_DECLARATION(u_matrix_normal)
	SHADER_VARIABLE_DECLARATION(u_matrix_view)
	SHADER_VARIABLE_DECLARATION(u_camera_pos)
	SHADER_VARIABLE_DECLARATION(u_map_diffuse)
	SHADER_VARIABLE_DECLARATION(u_map_specular)
	SHADER_VARIABLE_DECLARATION(u_map_normal)
	SHADER_VARIABLE_DECLARATION(u_light_pos)
	SHADER_VARIABLE_DECLARATION(u_light_diffuse)
	SHADER_VARIABLE_DECLARATION(u_light_specular)
	SHADER_VARIABLE_DECLARATION(u_light_ambient)
	SHADER_VARIABLE_DECLARATION(u_light_range)

public:
	DeferredEffect();

public:
	DeferredEffect(const DeferredEffect& aRhs) = delete;
	DeferredEffect& operator = (const DeferredEffect& aRhs) = delete;

public:
	virtual GLvoid Initialize(GLuint aVertexArrayObject) override;
	virtual GLuint GetVertexSize() const override;
};
}

#endif
