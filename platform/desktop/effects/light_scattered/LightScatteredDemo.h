#ifndef _LIGHT_SCATTERED_DEMO_H_
#define _LIGHT_SCATTERED_DEMO_H_

#include "LightScatteredSettings.h"
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
class LightScatteredEffect;
class LightScatteredUi;
class LightScatteredDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LightScatteredDemo, DrawableGameComponent)

public:
	LightScatteredDemo(Library::Game& aGame);
	~LightScatteredDemo();

public:
	LightScatteredDemo() = delete;
	LightScatteredDemo(const LightScatteredDemo& aRhs) = delete;
	LightScatteredDemo& operator = (const LightScatteredDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mLightScatteredProgram;
	eps::utils::unique<LightScatteredEffect> mLightScatteredEffect;
	eps::utils::unique<eps::rendering::texture> u_occluding;
	eps::utils::optional<LightScatteredSettings> mLightScatteredSettings;
	LightScatteredUi* mLightScatteredUi;
};
}

#endif
