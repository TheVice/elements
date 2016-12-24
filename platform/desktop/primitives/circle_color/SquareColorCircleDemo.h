#ifndef _SQUARE_COLOR_CIRCLE_DEMO_H_
#define _SQUARE_COLOR_CIRCLE_DEMO_H_

#include "SquareColorCircleSettings.h"
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
class SquareColorCircleEffect;
class SquareColorCircleUi;
class SquareColorCircleDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(SquareColorCircleDemo, DrawableGameComponent)

public:
	SquareColorCircleDemo(Library::Game& aGame);
	~SquareColorCircleDemo();

public:
	SquareColorCircleDemo() = delete;
	SquareColorCircleDemo(const SquareColorCircleDemo& aRhs) = delete;
	SquareColorCircleDemo& operator = (const SquareColorCircleDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mSquareColorCircleProgram;
	eps::utils::unique<SquareColorCircleEffect> mSquareColorCircleEffect;
	eps::utils::optional<SquareColorCircleSettings> mSquareColorCircleSettings;
	SquareColorCircleUi* mSquareColorCircleUi;
};
}

#endif
