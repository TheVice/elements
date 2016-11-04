#ifndef _PARTICLES_DEMO_H_
#define _PARTICLES_DEMO_H_

#include "DrawableGameComponent.h"
#include "ParticlesEffect.h"
#include "SettingsReader.h"
#include <elements/rendering/core/buffer.h>
#include <elements/rendering/core/program.h>
#include <elements/utils/std/optional.h>
#include "Game.h"

namespace Rendering
{
class CustomUi;
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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<Library::ParticlesEffect> mParticlesEffect;
	GLuint mVertexArrayObject;
	eps::utils::unique<eps::rendering::vertices> mVertexBuffer;
	eps::utils::unique<eps::rendering::indices> mIndexBuffer;

	eps::utils::optional<SettingsReader> mSettings;

	CustomUi* mUi;
};
}

#endif
