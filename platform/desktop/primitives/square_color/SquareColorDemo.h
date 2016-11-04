#ifndef _SQUARE_DEMO_H_
#define _SQUARE_DEMO_H_

#include "DrawableGameComponent.h"
#include <elements/rendering/core/program.h>
#include <elements/rendering/primitives/square.h>
#include <elements/utils/std/pointer.h>
#include <elements/timing/framerate.h>
#include "Game.h"

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
