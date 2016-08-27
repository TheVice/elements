#ifndef _PARTICLES_EFFECT_H_
#define _PARTICLES_EFFECT_H_

#include "ShaderProgram.h"

namespace Library
{
class ParticlesEffect : public ShaderProgram
{
	RTTI_DECLARATIONS(ParticlesEffect, ShaderProgram)

	SHADER_VARIABLE_DECLARATION(u_transform)
	SHADER_VARIABLE_DECLARATION(u_size)

public:
	ParticlesEffect();

public:
	ParticlesEffect(const ParticlesEffect& aRhs) = delete;
	ParticlesEffect& operator = (const ParticlesEffect& aRhs) = delete;

public:
	virtual GLvoid Initialize(GLuint aVertexArrayObject) override;
	virtual GLuint GetVertexSize() const override;
};
}

#endif
