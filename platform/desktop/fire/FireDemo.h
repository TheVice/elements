#ifndef _FIRE_DEMO_H_
#define _FIRE_DEMO_H_

#include "DrawableGameComponent.h"
#if !defined(_MSC_VER) || defined(__clang__)
#include "fire_renderer.h"
#endif
#include "renderer_factory.h"
#include <GL/glew.h>

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
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	bool mTouchDown;
	int mRenderId;
	typedef renderer_factory<fire_renderer> fire_renderer_factory;
	std::unique_ptr<fire_renderer_factory> mFireRendererFactory;

private:
	static const char* sBackground;
	static const glm::vec3 sColorHot;
	static const glm::vec3 sColorCold;
	static const int sQuality;
};
}

#endif
