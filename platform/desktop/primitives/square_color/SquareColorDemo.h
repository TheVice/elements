#ifndef _SQUARE_DEMO_H_
#define _SQUARE_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/primitives/square.h"
#include <GL/glew.h>

namespace Rendering
{
class SquareColorDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(SquareColorDemo, DrawableGameComponent)

public:
	SquareColorDemo(Library::Game& aGame);
	~SquareColorDemo();

public:
	SquareColorDemo() = delete;
	SquareColorDemo(const SquareColorDemo& aRhs) = delete;
	SquareColorDemo& operator = (const SquareColorDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::primitive::square mSquare;
	glm::vec4 mColor;
	glm::mat4 mTransform;
};
}

#endif
