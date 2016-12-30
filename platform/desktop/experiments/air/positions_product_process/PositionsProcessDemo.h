#ifndef _POSITIONS_PROCESS_DEMO_H_
#define _POSITIONS_PROCESS_DEMO_H_

#include "PositionsProcessSettings.h"
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
class PositionsProcessEffect;
class PositionsProcessUi;
class PositionsProcessDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(PositionsProcessDemo, DrawableGameComponent)

public:
	PositionsProcessDemo(Library::Game& aGame);
	~PositionsProcessDemo();

public:
	PositionsProcessDemo() = delete;
	PositionsProcessDemo(const PositionsProcessDemo& aRhs) = delete;
	PositionsProcessDemo& operator = (const PositionsProcessDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mPositionsProcessProgram;
	eps::utils::unique<PositionsProcessEffect> mPositionsProcessEffect;
	eps::utils::unique<eps::rendering::texture> u_positions;
	eps::utils::unique<eps::rendering::texture> u_velocities;
	eps::utils::optional<PositionsProcessSettings> mPositionsProcessSettings;
	PositionsProcessUi* mPositionsProcessUi;
};
}

#endif
