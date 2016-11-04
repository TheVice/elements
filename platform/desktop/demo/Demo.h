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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void OnKey(int aKey, int aScancode, int aAction, int aMods);

private:
	int mRenderId;
	using RendererFactory = renderer_factory<demo_renderer>;
	eps::utils::unique<RendererFactory> mRendererFactory;
	eps::timing::framerate rate_;
	Library::Game::KeyboardHandler mKeyboardHandler;
};
}

#endif
