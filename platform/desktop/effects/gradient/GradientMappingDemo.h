#ifndef _GRADIENT_MAPPING_DEMO_H_
#define _GRADIENT_MAPPING_DEMO_H_

#include "GradientMappingSettings.h"
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
class GradientMappingEffect;
class GradientMappingUi;
class GradientMappingDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(GradientMappingDemo, DrawableGameComponent)

public:
	GradientMappingDemo(Library::Game& aGame);
	~GradientMappingDemo();

public:
	GradientMappingDemo() = delete;
	GradientMappingDemo(const GradientMappingDemo& aRhs) = delete;
	GradientMappingDemo& operator = (const GradientMappingDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mGradientMappingProgram;
	eps::utils::unique<GradientMappingEffect> mGradientMappingEffect;
	eps::utils::unique<eps::rendering::texture> u_source;
	eps::utils::optional<GradientMappingSettings> mGradientMappingSettings;
	GradientMappingUi* mGradientMappingUi;
};
}

#endif
