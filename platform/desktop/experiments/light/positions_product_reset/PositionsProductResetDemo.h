#ifndef _POSITIONS_PRODUCT_RESET_DEMO_H_
#define _POSITIONS_PRODUCT_RESET_DEMO_H_

#include "PositionsProductResetSettings.h"
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
class PositionsProductResetEffect;
class PositionsProductResetUi;
class PositionsProductResetDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(PositionsProductResetDemo, DrawableGameComponent)

public:
	PositionsProductResetDemo(Library::Game& aGame);
	~PositionsProductResetDemo();

public:
	PositionsProductResetDemo() = delete;
	PositionsProductResetDemo(const PositionsProductResetDemo& aRhs) = delete;
	PositionsProductResetDemo& operator = (const PositionsProductResetDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mPositionsProductResetProgram;
	eps::utils::unique<PositionsProductResetEffect> mPositionsProductResetEffect;
	eps::utils::unique<eps::rendering::texture> u_displacement;
	eps::utils::optional<PositionsProductResetSettings> mPositionsProductResetSettings;
	PositionsProductResetUi* mPositionsProductResetUi;
};
}

#endif
