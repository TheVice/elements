#ifndef _AIR_DEMO_H_
#define _AIR_DEMO_H_

#include "DrawableGameComponent.h"
#include "air_renderer.h"
#include "../renderer_factory.h"
#include "Game.h"

namespace Rendering
{
class AirDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(AirDemo, DrawableGameComponent)

public:
	AirDemo(Library::Game& aGame);
	~AirDemo();

public:
	AirDemo() = delete;
	AirDemo(const AirDemo& aRhs) = delete;
	AirDemo& operator = (const AirDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	int mRenderId;
	using RendererFactory = renderer_factory<air_renderer>;
	eps::utils::unique<RendererFactory> mRendererFactory;

private:
	static const glm::vec3 sColorSpeedDown;
	static const glm::vec3 sColorSpeedUp;
	static const int sQuantity;
};
}

#endif
