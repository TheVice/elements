#ifndef _SQUARE_TEXTURE_ALPHA_DEMO_H_
#define _SQUARE_TEXTURE_ALPHA_DEMO_H_

#include "SquareTextureAlphaSettings.h"
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
class SquareTextureAlphaEffect;
class SquareTextureAlphaUi;
class SquareTextureAlphaDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(SquareTextureAlphaDemo, DrawableGameComponent)

public:
	SquareTextureAlphaDemo(Library::Game& aGame);
	~SquareTextureAlphaDemo();

public:
	SquareTextureAlphaDemo() = delete;
	SquareTextureAlphaDemo(const SquareTextureAlphaDemo& aRhs) = delete;
	SquareTextureAlphaDemo& operator = (const SquareTextureAlphaDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mSquareTextureAlphaProgram;
	eps::utils::unique<SquareTextureAlphaEffect> mSquareTextureAlphaEffect;
	eps::utils::unique<eps::rendering::texture> u_source;
	eps::utils::optional<SquareTextureAlphaSettings> mSquareTextureAlphaSettings;
	SquareTextureAlphaUi* mSquareTextureAlphaUi;
};
}

#endif
