#ifndef _LIGHT_DEMO_H_
#define _LIGHT_DEMO_H_

#include "DrawableGameComponent.h"
#include "light_renderer.h"
#include "../renderer_factory.h"
#include "Game.h"

namespace Rendering
{
class LightDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(LightDemo, DrawableGameComponent)

public:
	LightDemo(Library::Game& aGame);
	~LightDemo();

public:
	LightDemo() = delete;
	LightDemo(const LightDemo& aRhs) = delete;
	LightDemo& operator = (const LightDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	int mRenderId;
	using RendererFactory = renderer_factory<light_renderer>;
	eps::utils::unique<RendererFactory> mRendererFactory;

private:
	static const char* sBackground;
	static const glm::vec3 sColor;
	static const int sQuantity;
};
}

#endif
