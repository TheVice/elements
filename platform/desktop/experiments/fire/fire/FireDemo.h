#ifndef _FIRE_DEMO_H_
#define _FIRE_DEMO_H_

#include "FireSettings.h"
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
class FireEffect;
class FireUi;
class FireDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(FireDemo, DrawableGameComponent)

public:
	FireDemo(Library::Game& aGame);
	~FireDemo();

public:
	FireDemo() = delete;
	FireDemo(const FireDemo& aRhs) = delete;
	FireDemo& operator = (const FireDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mFireProgram;
	eps::utils::unique<FireEffect> mFireEffect;
	eps::utils::unique<eps::rendering::texture> u_fire;
	eps::utils::unique<eps::rendering::texture> u_background;
	eps::utils::optional<FireSettings> mFireSettings;
	FireUi* mFireUi;
};
}

#endif
