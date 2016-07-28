#ifndef _AIR_DEMO_H_
#define _AIR_DEMO_H_

#include "DrawableGameComponent.h"
#include "air_renderer.h"
#include "../renderer_factory.h"

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
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	bool mTouchDown;
	int mRenderId;
	typedef renderer_factory<air_renderer> air_renderer_factory;
	std::unique_ptr<air_renderer_factory> mAirRendererFactory;

private:
	static const glm::vec3 sColorSpeedDown;
	static const glm::vec3 sColorSpeedUp;
	static const int sQuantity;
};
}

#endif
