#ifndef _SQUARE_TEXTURE_ALPHA_DEMO_H_
#define _SQUARE_TEXTURE_ALPHA_DEMO_H_

#include "DrawableGameComponent.h"
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/rendering/primitives/square.h>
#include <elements/utils/std/pointer.h>
#include <elements/timing/framerate.h>
#include "Game.h"

namespace Rendering
{
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
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<eps::rendering::texture> mTexture;
	eps::utils::unique<eps::rendering::primitive::square> mSquare;
	eps::math::mat4 mTransform;
	eps::math::vec4 mColor;

	GLuint mColorTexture;
	eps::timing::framerate rate_;
};
}

#endif
