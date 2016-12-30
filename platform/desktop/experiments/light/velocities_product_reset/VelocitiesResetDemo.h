#ifndef _VELOCITIES_RESET_DEMO_H_
#define _VELOCITIES_RESET_DEMO_H_

#include "VelocitiesResetSettings.h"
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
class VelocitiesResetEffect;
class VelocitiesResetUi;
class VelocitiesResetDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(VelocitiesResetDemo, DrawableGameComponent)

public:
	VelocitiesResetDemo(Library::Game& aGame);
	~VelocitiesResetDemo();

public:
	VelocitiesResetDemo() = delete;
	VelocitiesResetDemo(const VelocitiesResetDemo& aRhs) = delete;
	VelocitiesResetDemo& operator = (const VelocitiesResetDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mVelocitiesResetProgram;
	eps::utils::unique<VelocitiesResetEffect> mVelocitiesResetEffect;
	eps::utils::optional<VelocitiesResetSettings> mVelocitiesResetSettings;
	VelocitiesResetUi* mVelocitiesResetUi;
};
}

#endif
