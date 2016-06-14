#ifndef _AIR_DEMO_H_
#define _AIR_DEMO_H_

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
class AirDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(AirDemo, DrawableGameComponent)

public:
	AirDemo(Library::Game& aGame, Library::Camera& aCamera);
	~AirDemo();

public:
	AirDemo() = delete;
	AirDemo(const AirDemo& aRhs) = delete;
	AirDemo& operator = (const AirDemo& aRhs) = delete;

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
