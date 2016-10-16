#ifndef _DEMO_H_
#define _DEMO_H_

#include "DrawableGameComponent.h"
#include "demo_renderer.h"
#include "../renderer_factory.h"
#include "Game.h"

namespace Rendering
{
class Demo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(Demo, DrawableGameComponent)

public:
	Demo(Library::Game& aGame);
	~Demo();

public:
	Demo() = delete;
	Demo(const Demo& aRhs) = delete;
	Demo& operator = (const Demo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	void OnKey(int aKey, int aScancode, int aAction, int aMods);

private:
	int mRenderId;
	using demo_renderer_factory = renderer_factory<demo_renderer>;
	std::unique_ptr<demo_renderer_factory> mDemoRendererFactory;
	eps::timing::framerate rate_;
	Library::Game::KeyboardHandler mKeyboardHandler;
};
}

#endif
