#ifndef _SQUARE_TEXTURE_DEMO_H_
#define _SQUARE_TEXTURE_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "rendering/primitives/square.h"

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
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::primitive::square mSquare;
	eps::rendering::texture mTexture;
	glm::mat4 mTransform;
};
}

#endif
