#ifndef _LIQUID_DEMO_H_
#define _LIQUID_DEMO_H_

#include "DrawableGameComponent.h"
#if !defined(_MSC_VER) || defined(__clang__)
#include "renderer.h"
#include "elements/simulation/liquid/system.h"
#include "liquid_renderer.h"
#endif
#include "renderer_factory.h"
#include <GLES2/gl2.h>
#include <glm/glm.hpp>

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

class liquid_renderer;

namespace Rendering
{
class LiquidDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LiquidDemo, DrawableGameComponent)

public:
	LiquidDemo(Library::Game& aGame);
	~LiquidDemo();

public:
	LiquidDemo() = delete;
	LiquidDemo(const LiquidDemo& aRhs) = delete;
	LiquidDemo& operator = (const LiquidDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;
	static GLboolean IsMove(glm::dvec2 aScreenPos, glm::dvec2 aPrevScreenPos);

private:
	std::unique_ptr<eps::simulation::liquid::system> mSystem;
	std::unique_ptr<eps::experiment::liquid::renderer> mRenderer;
	glm::mat4 mTransform;
	glm::mat4 mTransformTouch;
	glm::dvec2 mPrevScreenPos;
	GLuint mParticlesCount;
	std::unique_ptr<liquid_renderer> mLiquidRenderer;

	int mRenderId;
	typedef renderer_factory<liquid_renderer> liquid_renderer_factory;
	std::unique_ptr<liquid_renderer_factory> mLiquidRendererFactory;

	glm::vec2 mGravity;

	static const glm::vec2 sDefaultGravity;
};
}

#endif
