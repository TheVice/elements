#ifndef _LIGHT_DEMO_H_
#define _LIGHT_DEMO_H_

#include "DrawableGameComponent.h"
#if !defined(_MSC_VER) || defined(__clang__)
#include "light_renderer.h"
#endif
#include "renderer_factory.h"
#include <GLES2/gl2.h>

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
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	bool mTouchDown;
	int mRenderId;
	typedef renderer_factory<light_renderer> light_renderer_factory;
	std::unique_ptr<light_renderer_factory> mLightRendererFactory;

private:
	static const char* sBackground;
	static const glm::vec3 sColor;
	static const int sQuantity;
};
}

#endif
