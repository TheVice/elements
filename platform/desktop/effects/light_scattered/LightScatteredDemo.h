#ifndef _LIGHT_SCATTERED_DEMO_H_
#define _LIGHT_SCATTERED_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "rendering/primitives/square.h"
#include "rendering/core/texture_policy.h"
#include <GL/glew.h>

namespace Rendering
{
class LightScatteredDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LightScatteredDemo, DrawableGameComponent)

public:
	LightScatteredDemo(Library::Game& aGame);
	~LightScatteredDemo();

public:
	LightScatteredDemo() = delete;
	LightScatteredDemo(const LightScatteredDemo& aRhs) = delete;
	LightScatteredDemo& operator = (const LightScatteredDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::primitive::square mSquare;
	eps::rendering::texture<eps::rendering::default_texture_policy> mTexture;
	float mExposure;
	float mDecay;
	float mDensity;
	float mWeight;
	glm::vec2 mLightPosition;
};
}

#endif
