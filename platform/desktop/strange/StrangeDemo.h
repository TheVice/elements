#ifndef _STRANGE_DEMO_H_
#define _STRANGE_DEMO_H_

#include "DrawableGameComponent.h"
#ifndef _MSC_VER
#include "renderer.h"
#endif
#include <GL/glew.h>

namespace Rendering
{
class StrangeDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(StrangeDemo, DrawableGameComponent)

public:
	StrangeDemo(Library::Game& aGame, Library::Camera& aCamera);
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
