#ifndef _VELOCITIES_PROCESS_DEMO_H_
#define _VELOCITIES_PROCESS_DEMO_H_

#include "VelocitiesProcessSettings.h"
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
class VelocitiesProcessEffect;
class VelocitiesProcessUi;
class VelocitiesProcessDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(VelocitiesProcessDemo, DrawableGameComponent)

public:
	VelocitiesProcessDemo(Library::Game& aGame);
	~VelocitiesProcessDemo();

public:
	VelocitiesProcessDemo() = delete;
	VelocitiesProcessDemo(const VelocitiesProcessDemo& aRhs) = delete;
	VelocitiesProcessDemo& operator = (const VelocitiesProcessDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mVelocitiesProcessProgram;
	eps::utils::unique<VelocitiesProcessEffect> mVelocitiesProcessEffect;
	eps::utils::unique<eps::rendering::texture> u_product;
	eps::utils::optional<VelocitiesProcessSettings> mVelocitiesProcessSettings;
	VelocitiesProcessUi* mVelocitiesProcessUi;
};
}

#endif
