#ifndef _MODEL_EFFECT_H_
#define _MODEL_EFFECT_H_

#include "ShaderProgram.h"

namespace Library
{
class ModelEffect : public ShaderProgram
{
	RTTI_DECLARATIONS(ModelEffect, ShaderProgram)

	SHADER_VARIABLE_DECLARATION(u_matrix_mvp)
	SHADER_VARIABLE_DECLARATION(u_matrix_model_view)
	SHADER_VARIABLE_DECLARATION(u_matrix_normal)
	SHADER_VARIABLE_DECLARATION(u_matrix_view)
	SHADER_VARIABLE_DECLARATION(u_camera_pos)
	SHADER_VARIABLE_DECLARATION(u_map_diffuse)
	SHADER_VARIABLE_DECLARATION(u_map_specular)
	SHADER_VARIABLE_DECLARATION(u_map_normal)
	SHADER_VARIABLE_DECLARATION(u_light_pos)
	SHADER_VARIABLE_DECLARATION(u_light_intensity)
	SHADER_VARIABLE_DECLARATION(u_light_range)

public:
	ModelEffect();

public:
	ModelEffect(const ModelEffect& aRhs) = delete;
	ModelEffect& operator = (const ModelEffect& aRhs) = delete;

public:
	virtual GLvoid Initialize(GLuint aVertexArrayObject) override;
	virtual GLuint GetVertexSize() const override;
};
}

#endif
