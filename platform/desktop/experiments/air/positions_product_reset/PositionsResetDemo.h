#ifndef _POSITIONS_RESET_DEMO_H_
#define _POSITIONS_RESET_DEMO_H_

#include "PositionsResetSettings.h"
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
class PositionsResetEffect;
class PositionsResetUi;
class PositionsResetDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(PositionsResetDemo, DrawableGameComponent)

public:
	PositionsResetDemo(Library::Game& aGame);
	~PositionsResetDemo();

public:
	PositionsResetDemo() = delete;
	PositionsResetDemo(const PositionsResetDemo& aRhs) = delete;
	PositionsResetDemo& operator = (const PositionsResetDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mPositionsResetProgram;
	eps::utils::unique<PositionsResetEffect> mPositionsResetEffect;
	eps::utils::optional<PositionsResetSettings> mPositionsResetSettings;
	PositionsResetUi* mPositionsResetUi;
};
}

#endif
