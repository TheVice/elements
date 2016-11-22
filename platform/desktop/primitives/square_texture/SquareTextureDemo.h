#ifndef _SQUARE_TEXTURE_DEMO_H_
#define _SQUARE_TEXTURE_DEMO_H_

#include <DrawableGameComponent.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/rendering/primitives/square.h>
#include <elements/utils/std/pointer.h>

namespace Rendering
{
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
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<eps::rendering::texture> mTexture;
	eps::utils::unique<eps::rendering::primitive::square> mSquare;
	eps::math::mat4 mTransform;

	GLuint mColorTexture;
};
}

#endif
