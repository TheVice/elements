#ifndef _LIQUID_DEMO_H_
#define _LIQUID_DEMO_H_

#include "DrawableGameComponent.h"
#include "liquid_renderer.h"
#include "../renderer_factory.h"
#include "Game.h"

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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	int mRenderId;
	using RendererFactory = renderer_factory<liquid_renderer>;
	std::unique_ptr<RendererFactory> mRendererFactory;

private:
	static const char* sBackground;
	static const glm::vec4 sColor;
	static const int sQuantity;
	static const glm::vec3 sGravity;
};
}

#endif
