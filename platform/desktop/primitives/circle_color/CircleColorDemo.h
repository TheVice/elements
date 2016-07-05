#ifndef _CIRCLE_DEMO_H_
#define _CIRCLE_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/primitives/square.h"
#include <GL/glew.h>

namespace Rendering
{
class CircleColorDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(CircleColorDemo, DrawableGameComponent)

public:
	CircleColorDemo(Library::Game& aGame);
	~CircleColorDemo();

public:
	CircleColorDemo() = delete;
	CircleColorDemo(const CircleColorDemo& aRhs) = delete;
	CircleColorDemo& operator = (const CircleColorDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgramCircleColor;
	eps::rendering::primitive::square mSquare;
	glm::vec4 mColor;
	glm::mat4 mTransform;
};
}

#endif
