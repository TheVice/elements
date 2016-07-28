#ifndef _BLUR_DEMO_H_
#define _BLUR_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "rendering/primitives/square.h"

namespace Rendering
{
class VertexPositionTexture;
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
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::texture mTexture;
	eps::rendering::primitive::square mSquare;
	glm::vec2 mOffset;
};
}

#endif
