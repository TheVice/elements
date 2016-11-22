#ifndef _BLUR_DEMO_H_
#define _BLUR_DEMO_H_

#include <DrawableGameComponent.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/rendering/primitives/square.h>
#include <elements/utils/std/pointer.h>
#include <elements/timing/framerate.h>

namespace Rendering
{
class BlurDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(BlurDemo, DrawableGameComponent)

public:
	BlurDemo(Library::Game& aGame);
	~BlurDemo();

public:
	BlurDemo() = delete;
	BlurDemo(const BlurDemo& aRhs) = delete;
	BlurDemo& operator = (const BlurDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<eps::rendering::texture> mTexture;
	eps::utils::unique<eps::rendering::primitive::square> mSquare;
	eps::math::vec2 mOffset;

	GLuint mColorTexture;
	eps::timing::framerate rate_;
};
}

#endif
