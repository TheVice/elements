#ifndef _PARTICLES_DEMO_H_
#define _PARTICLES_DEMO_H_

#include "DrawableGameComponent.h"
#include "ParticlesEffect.h"
#include "SettingsReader.h"
#include "rendering/core/buffer.h"
#include "rendering/core/program.h"
#include "utils/std/optional.h"
#include <memory>

namespace Rendering
{
class ParticlesDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(ParticlesDemo, DrawableGameComponent)

public:
	ParticlesDemo(Library::Game& aGame);
	~ParticlesDemo();

public:
	ParticlesDemo() = delete;
	ParticlesDemo(const ParticlesDemo& aRhs) = delete;
	ParticlesDemo& operator = (const ParticlesDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	Library::ParticlesEffect mParticlesEffect;
	GLuint mVertexArrayObject;
	eps::rendering::vertices mVertexBuffer;
	GLuint mVertexCount;

	eps::utils::optional<SettingsReader> mSettings;
};
}

#endif
