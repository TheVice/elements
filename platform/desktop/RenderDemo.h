#ifndef _RENDER_DEMO_H_
#define _RENDER_DEMO_H_

#include "DrawableGameComponent.h"
#ifndef _MSC_VER
#include "renderer.h"
#include "elements/simulation/air/system.h"
#endif
#include <GL/glew.h>

namespace eps
{
namespace experiment
{
namespace air
{
class renderer;
}
}
}

//eps::simulation::air::system

namespace Rendering
{
class RenderDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(RenderDemo, DrawableGameComponent)

public:
	RenderDemo(Library::Game& aGame, Library::Camera& aCamera);
	~RenderDemo();

public:
	RenderDemo() = delete;
	RenderDemo(const RenderDemo& aRhs) = delete;
	RenderDemo& operator = (const RenderDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	std::unique_ptr<eps::simulation::air::system> mSystem;
	std::unique_ptr<eps::experiment::air::renderer> mRenderer;
	GLuint mParticlesCount;
};
}

#endif
