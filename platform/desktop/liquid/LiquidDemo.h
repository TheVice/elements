#ifndef _LIQUID_DEMO_H_
#define _LIQUID_DEMO_H_

#include "DrawableGameComponent.h"
#if !defined(_MSC_VER) || defined(__clang__)
#include "liquid_renderer.h"
#endif
#include "renderer_factory.h"
#include <GL/glew.h>

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

private:
	int mRenderId;
	typedef renderer_factory<liquid_renderer> liquid_renderer_factory;
	std::unique_ptr<liquid_renderer_factory> mLiquidRendererFactory;

private:
	static const char* sBackground;
	static const glm::vec4 sColor;
	static const int sQuantity;
	static const glm::vec3 sGravity;
};
}

#endif
