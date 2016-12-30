#ifndef _LIGHT_SCATTERED_OCCLUDING_DEMO_H_
#define _LIGHT_SCATTERED_OCCLUDING_DEMO_H_

#include "LightScatteredOccludingSettings.h"
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
class LightScatteredOccludingEffect;
class LightScatteredOccludingUi;
class LightScatteredOccludingDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LightScatteredOccludingDemo, DrawableGameComponent)

public:
	LightScatteredOccludingDemo(Library::Game& aGame);
	~LightScatteredOccludingDemo();

public:
	LightScatteredOccludingDemo() = delete;
	LightScatteredOccludingDemo(const LightScatteredOccludingDemo& aRhs) = delete;
	LightScatteredOccludingDemo& operator = (const LightScatteredOccludingDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mLightScatteredOccludingProgram;
	eps::utils::unique<LightScatteredOccludingEffect> mLightScatteredOccludingEffect;
	eps::utils::unique<eps::rendering::texture> u_positions;
	eps::utils::optional<LightScatteredOccludingSettings> mLightScatteredOccludingSettings;
	LightScatteredOccludingUi* mLightScatteredOccludingUi;
};
}

#endif
