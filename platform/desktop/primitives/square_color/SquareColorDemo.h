#ifndef _SQUARE_COLOR_DEMO_H_
#define _SQUARE_COLOR_DEMO_H_

#include "SquareColorSettings.h"
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
class SquareColorEffect;
class SquareColorUi;
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
	eps::utils::unique<eps::rendering::program> mSquareColorProgram;
	eps::utils::unique<SquareColorEffect> mSquareColorEffect;
	eps::utils::optional<SquareColorSettings> mSquareColorSettings;
	SquareColorUi* mSquareColorUi;
};
}

#endif
