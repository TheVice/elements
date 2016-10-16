#ifndef _STRANGE_DEMO_H_
#define _STRANGE_DEMO_H_

#include "DrawableGameComponent.h"
#include "strange_renderer.h"
#include "../renderer_factory.h"

namespace Rendering
{
class StrangeDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(StrangeDemo, DrawableGameComponent)

public:
	StrangeDemo(Library::Game& aGame);
	~StrangeDemo();

public:
	StrangeDemo() = delete;
	StrangeDemo(const StrangeDemo& aRhs) = delete;
	StrangeDemo& operator = (const StrangeDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	int mRenderId;
	using strange_renderer_factory = renderer_factory<strange_renderer>;
	std::unique_ptr<strange_renderer_factory> mStrangeRendererFactory;

private:
	static const glm::vec3 sColorBackground;
	static const glm::vec3 sColorGradient1;
	static const glm::vec3 sColorGradient2;
	static const int sQuantity;
};
}

#endif
