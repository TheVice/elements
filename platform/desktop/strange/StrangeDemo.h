#ifndef _STRANGE_DEMO_H_
#define _STRANGE_DEMO_H_

#include "DrawableGameComponent.h"
#if !defined(_MSC_VER) || defined(__clang__)
#include "strange_renderer.h"
#endif
#include "renderer_factory.h"
#include <GLES2/gl2.h>

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
	typedef renderer_factory<strange_renderer> strange_renderer_factory;
	std::unique_ptr<strange_renderer_factory> mStrangeRendererFactory;

private:
	static const glm::vec3 sColorBackground;
	static const glm::vec3 sColorGradient1;
	static const glm::vec3 sColorGradient2;
	static const int sQuantity;
};
}

#endif
