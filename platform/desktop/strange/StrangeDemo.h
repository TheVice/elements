#ifndef _STRANGE_DEMO_H_
#define _STRANGE_DEMO_H_

#include "DrawableGameComponent.h"
#if !defined(_MSC_VER) || defined(__clang__)
#include "renderer.h"
#endif
#include <GLES2/gl2.h>

namespace Rendering
{
class StrangeDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(StrangeDemo, DrawableGameComponent)

public:
	StrangeDemo(Library::Game& aGame);
	~StrangeDemo();

public:
	StrangeDemo() = delete;
	StrangeDemo(const StrangeDemo& aRhs) = delete;
	StrangeDemo& operator = (const StrangeDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	std::unique_ptr<eps::experiment::strange::renderer> mRenderer;
	GLuint mParticlesCount;
};
}

#endif
