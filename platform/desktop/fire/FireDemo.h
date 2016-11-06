#ifndef _FIRE_DEMO_H_
#define _FIRE_DEMO_H_

#include "DrawableGameComponent.h"
#include "fire_renderer.h"
#include "../renderer_factory.h"
#include "Game.h"

namespace Rendering
{
class FireDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(FireDemo, DrawableGameComponent)

public:
	FireDemo(Library::Game& aGame);
	~FireDemo();

public:
	FireDemo() = delete;
	FireDemo(const FireDemo& aRhs) = delete;
	FireDemo& operator = (const FireDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	int mRenderId;
	using RendererFactory = renderer_factory<fire_renderer>;
	eps::utils::unique<RendererFactory> mRendererFactory;

private:
	static const char* sBackground;
	static const glm::vec3 sColorHot;
	static const glm::vec3 sColorCold;
	static const int sQuality;
};
}

#endif
