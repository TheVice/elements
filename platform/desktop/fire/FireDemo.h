#ifndef _FIRE_DEMO_H_
#define _FIRE_DEMO_H_

#include "DrawableGameComponent.h"
#ifndef _MSC_VER
#include "renderer.h"
#endif
#include <GL/glew.h>

namespace eps
{
namespace experiment
{
namespace fire
{
class renderer;
}
}
}

namespace Rendering
{
class FireDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(FireDemo, DrawableGameComponent)

public:
	FireDemo(Library::Game& aGame, Library::Camera& aCamera);
	~FireDemo();

public:
	FireDemo() = delete;
	FireDemo(const FireDemo& aRhs) = delete;
	FireDemo& operator = (const FireDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	std::unique_ptr<eps::experiment::fire::renderer> mRenderer;
};
}

#endif
