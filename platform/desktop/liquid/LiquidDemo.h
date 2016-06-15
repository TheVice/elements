#ifndef _LIQUID_DEMO_H_
#define _LIQUID_DEMO_H_

#include "DrawableGameComponent.h"
#ifndef _MSC_VER
#include "renderer.h"
#include "elements/simulation/liquid/system.h"
#endif
#include <GL/glew.h>

namespace eps
{
namespace experiment
{
namespace liquid
{
class renderer;
}
}
}

namespace eps
{
namespace simulation
{
namespace liquid
{
class system;
}
}
}

namespace Rendering
{
class LiquidDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LiquidDemo, DrawableGameComponent)

public:
	LiquidDemo(Library::Game& aGame, Library::Camera& aCamera);
	~LiquidDemo();

public:
	LiquidDemo() = delete;
	LiquidDemo(const LiquidDemo& aRhs) = delete;
	LiquidDemo& operator = (const LiquidDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	std::unique_ptr<eps::simulation::liquid::system> mSystem;
	std::unique_ptr<eps::experiment::liquid::renderer> mRenderer;
	GLuint mParticlesCount;
};
}

#endif
