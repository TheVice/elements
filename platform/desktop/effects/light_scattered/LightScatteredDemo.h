#ifndef _LIGHT_SCATTERED_DEMO_H_
#define _LIGHT_SCATTERED_DEMO_H_

#include <DrawableGameComponent.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/rendering/primitives/square.h>
#include <elements/utils/std/pointer.h>
#include <elements/timing/framerate.h>

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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<eps::rendering::texture> mTexture;
	eps::utils::unique<eps::rendering::primitive::square> mSquare;
	float mExposure;
	float mDecay;
	float mDensity;
	float mWeight;
	eps::math::vec2 mLightPosition;

	GLuint mColorTexture;
	eps::timing::framerate rate_;
};
}

#endif
