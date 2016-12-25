#ifndef _LPP_LIGHTING_DEMO_H_
#define _LPP_LIGHTING_DEMO_H_

#include "LppLightingSettings.h"
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
class LppLightingEffect;
class LppLightingUi;
class LppLightingDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LppLightingDemo, DrawableGameComponent)

public:
	LppLightingDemo(Library::Game& aGame);
	~LppLightingDemo();

public:
	LppLightingDemo() = delete;
	LppLightingDemo(const LppLightingDemo& aRhs) = delete;
	LppLightingDemo& operator = (const LppLightingDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mLppLightingProgram;
	eps::utils::unique<LppLightingEffect> mLppLightingEffect;
	eps::utils::unique<eps::rendering::texture> u_map_geometry;
	eps::utils::unique<eps::rendering::texture> u_map_depth;
	eps::utils::optional<LppLightingSettings> mLppLightingSettings;
	LppLightingUi* mLppLightingUi;
};
}

#endif
