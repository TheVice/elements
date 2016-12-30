#ifndef _FIRE_RAYMARCHING_DEMO_H_
#define _FIRE_RAYMARCHING_DEMO_H_

#include "FireRaymarchingSettings.h"
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
class FireRaymarchingEffect;
class FireRaymarchingUi;
class FireRaymarchingDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(FireRaymarchingDemo, DrawableGameComponent)

public:
	FireRaymarchingDemo(Library::Game& aGame);
	~FireRaymarchingDemo();

public:
	FireRaymarchingDemo() = delete;
	FireRaymarchingDemo(const FireRaymarchingDemo& aRhs) = delete;
	FireRaymarchingDemo& operator = (const FireRaymarchingDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mFireRaymarchingProgram;
	eps::utils::unique<FireRaymarchingEffect> mFireRaymarchingEffect;
	eps::utils::unique<eps::rendering::texture> u_noise;
	eps::utils::optional<FireRaymarchingSettings> mFireRaymarchingSettings;
	FireRaymarchingUi* mFireRaymarchingUi;
};
}

#endif
