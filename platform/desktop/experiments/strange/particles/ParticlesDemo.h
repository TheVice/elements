#ifndef _PARTICLES_DEMO_H_
#define _PARTICLES_DEMO_H_

#include "ParticlesSettings.h"
#include <DrawableGameComponent.h>
#include <elements/utils/std/pointer.h>
#include <elements/utils/std/optional.h>

namespace eps
{
namespace rendering
{
class program;
class texture;
}
}

namespace Rendering
{
class ParticlesEffect;
class ParticlesUi;
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
	eps::utils::unique<eps::rendering::program> mParticlesProgram;
	eps::utils::unique<ParticlesEffect> mParticlesEffect;
	eps::utils::unique<eps::rendering::texture> u_positions;
	eps::utils::optional<ParticlesSettings> mParticlesSettings;
	ParticlesUi* mParticlesUi;
};
}

#endif
