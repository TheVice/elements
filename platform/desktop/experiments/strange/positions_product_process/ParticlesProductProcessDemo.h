#ifndef _PARTICLES_PRODUCT_PROCESS_DEMO_H_
#define _PARTICLES_PRODUCT_PROCESS_DEMO_H_

#include "ParticlesProductProcessSettings.h"
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
class ParticlesProductProcessEffect;
class ParticlesProductProcessUi;
class ParticlesProductProcessDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(ParticlesProductProcessDemo, DrawableGameComponent)

public:
	ParticlesProductProcessDemo(Library::Game& aGame);
	~ParticlesProductProcessDemo();

public:
	ParticlesProductProcessDemo() = delete;
	ParticlesProductProcessDemo(const ParticlesProductProcessDemo& aRhs) = delete;
	ParticlesProductProcessDemo& operator = (const ParticlesProductProcessDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mParticlesProductProcessProgram;
	eps::utils::unique<ParticlesProductProcessEffect> mParticlesProductProcessEffect;
	eps::utils::optional<ParticlesProductProcessSettings> mParticlesProductProcessSettings;
	ParticlesProductProcessUi* mParticlesProductProcessUi;
};
}

#endif
