#ifndef _LIQUID_DEMO_H_
#define _LIQUID_DEMO_H_

#include "LiquidSettings.h"
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
class LiquidEffect;
class LiquidUi;
class LiquidDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LiquidDemo, DrawableGameComponent)

public:
	LiquidDemo(Library::Game& aGame);
	~LiquidDemo();

public:
	LiquidDemo() = delete;
	LiquidDemo(const LiquidDemo& aRhs) = delete;
	LiquidDemo& operator = (const LiquidDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mLiquidProgram;
	eps::utils::unique<LiquidEffect> mLiquidEffect;
	eps::utils::unique<eps::rendering::texture> u_surface;
	eps::utils::unique<eps::rendering::texture> u_surface_background;
	eps::utils::optional<LiquidSettings> mLiquidSettings;
	LiquidUi* mLiquidUi;
};
}

#endif
