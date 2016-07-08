#ifndef _SQUARE_TEXTURE_ALPHA_DEMO_H_
#define _SQUARE_TEXTURE_ALPHA_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "rendering/primitives/square.h"
#include "rendering/core/texture_policy.h"
#include <GL/glew.h>

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
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::primitive::square mSquare;
	eps::rendering::texture<eps::rendering::default_texture_policy> mTexture;
	glm::mat4 mTransform;
	glm::vec4 mColor;
};
}

#endif
