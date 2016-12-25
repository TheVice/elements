#ifndef _LPP_LIGHTING_STENCIL_DEMO_H_
#define _LPP_LIGHTING_STENCIL_DEMO_H_

#include "LppLightingStencilSettings.h"
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
class LppLightingStencilEffect;
class LppLightingStencilUi;
class LppLightingStencilDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LppLightingStencilDemo, DrawableGameComponent)

public:
	LppLightingStencilDemo(Library::Game& aGame);
	~LppLightingStencilDemo();

public:
	LppLightingStencilDemo() = delete;
	LppLightingStencilDemo(const LppLightingStencilDemo& aRhs) = delete;
	LppLightingStencilDemo& operator = (const LppLightingStencilDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mLppLightingStencilProgram;
	eps::utils::unique<LppLightingStencilEffect> mLppLightingStencilEffect;
	eps::utils::optional<LppLightingStencilSettings> mLppLightingStencilSettings;
	LppLightingStencilUi* mLppLightingStencilUi;
};
}

#endif
