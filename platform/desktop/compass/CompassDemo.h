#ifndef _COMPASS_DEMO_H_
#define _COMPASS_DEMO_H_

#include "DrawableGameComponent.h"
#include "compass_renderer.h"
#include "../renderer_factory.h"

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
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	int mRenderId;
	using CompassRendererFactory = renderer_factory<compass_renderer>;
	std::unique_ptr<CompassRendererFactory> mRendererFactory;
};
}

#endif
