
#include "RenderDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#endif
#include "Game.h"
#include "Camera.h"
#include "Utility.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(RenderDemo)

RenderDemo::RenderDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mRenderer(nullptr)
{
}

RenderDemo::~RenderDemo()
{
}

void RenderDemo::Initialize()
{
	mRenderer = std::make_unique<eps::experiment::air::renderer>();

	if (!mRenderer->initialize())
	{
		throw std::runtime_error("mRenderer->initialize() failed");
	}

	//mRenderer->construct(glm::vec2(mGame->GetScreenWidth(), mGame->GetScreenHeight()), 10);
}

void RenderDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
}

}
