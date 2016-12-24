#ifndef _BLUR_DEMO_H_
#define _BLUR_DEMO_H_

#include "BlurSettings.h"
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
class BlurEffect;
class BlurUi;
class BlurDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(BlurDemo, DrawableGameComponent)

public:
	BlurDemo(Library::Game& aGame);
	~BlurDemo();

public:
	BlurDemo() = delete;
	BlurDemo(const BlurDemo& aRhs) = delete;
	BlurDemo& operator = (const BlurDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mBlurProgram;
	eps::utils::unique<BlurEffect> mBlurEffect;
	eps::utils::unique<eps::rendering::texture> u_source;
	eps::utils::optional<BlurSettings> mBlurSettings;
	BlurUi* mBlurUi;
};
}

#endif
