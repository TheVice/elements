
#include "CompassDemo.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(CompassDemo)

CompassDemo::CompassDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr)
{
}

CompassDemo::~CompassDemo()
{
	mRendererFactory->close(mRenderId);
}

void CompassDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mRendererFactory = std::make_unique<CompassRendererFactory>();
	//
	mRenderId = mRendererFactory->open();
	//
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size))
	{
		throw std::runtime_error("renderer->startup() failed");
	}
}

void CompassDemo::Update(const Library::GameTime&)
{
}

void CompassDemo::Draw(const Library::GameTime&)
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

}
