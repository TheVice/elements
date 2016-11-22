#ifndef _CIRCLE_DEMO_H_
#define _CIRCLE_DEMO_H_

#include <DrawableGameComponent.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/primitives/square.h>
#include <elements/utils/std/pointer.h>
#include <elements/timing/framerate.h>

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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<eps::rendering::primitive::square> mSquare;
	eps::math::vec4 mColor;
	eps::math::mat4 mTransform;
	eps::timing::framerate rate_;
};
}

#endif
