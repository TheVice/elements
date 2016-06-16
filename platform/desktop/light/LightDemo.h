#ifndef _LIGHT_DEMO_H_
#define _LIGHT_DEMO_H_

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
namespace light
{
class renderer;
}
}
}

namespace eps
{
namespace simulation
{
namespace air
{
class system;
}
}
}

namespace Rendering
{
class LightDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LightDemo, DrawableGameComponent)

public:
	LightDemo(Library::Game& aGame, Library::Camera& aCamera);
	~LightDemo();

public:
	LightDemo() = delete;
	LightDemo(const LightDemo& aRhs) = delete;
	LightDemo& operator = (const LightDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	std::unique_ptr<eps::simulation::air::system> mSystem;
	std::unique_ptr<eps::experiment::light::renderer> mRenderer;
	GLuint mParticlesCount;
	GLboolean mTouchDown;
};
}

#endif