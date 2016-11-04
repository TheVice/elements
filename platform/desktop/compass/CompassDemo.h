#ifndef _COMPASS_DEMO_H_
#define _COMPASS_DEMO_H_

#include "DrawableGameComponent.h"
#include "compass_renderer.h"
#include "../renderer_factory.h"
#include "Game.h"

namespace Rendering
{
class CompassDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(CompassDemo, DrawableGameComponent)

public:
	CompassDemo(Library::Game& aGame);
	~CompassDemo();

public:
	CompassDemo() = delete;
	CompassDemo(const CompassDemo& aRhs) = delete;
	CompassDemo& operator = (const CompassDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void OnKey(int aKey, int aScancode, int aAction, int aMods);

private:
	int mRenderId;
	using RendererFactory = renderer_factory<compass_renderer>;
	eps::utils::unique<RendererFactory> mRendererFactory;
	eps::timing::framerate rate_;
};
}

#endif
