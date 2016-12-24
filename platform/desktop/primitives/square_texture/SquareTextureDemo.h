#ifndef _SQUARE_TEXTURE_DEMO_H_
#define _SQUARE_TEXTURE_DEMO_H_

#include "SquareTextureSettings.h"
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
class SquareTextureEffect;
class SquareTextureUi;
class SquareTextureDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(SquareTextureDemo, DrawableGameComponent)

public:
	SquareTextureDemo(Library::Game& aGame);
	~SquareTextureDemo();

public:
	SquareTextureDemo() = delete;
	SquareTextureDemo(const SquareTextureDemo& aRhs) = delete;
	SquareTextureDemo& operator = (const SquareTextureDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mSquareTextureProgram;
	eps::utils::unique<SquareTextureEffect> mSquareTextureEffect;
	eps::utils::unique<eps::rendering::texture> u_source;
	eps::utils::optional<SquareTextureSettings> mSquareTextureSettings;
	SquareTextureUi* mSquareTextureUi;
};
}

#endif
