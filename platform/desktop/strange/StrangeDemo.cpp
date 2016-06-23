
#include "StrangeDemo.h"
#if defined (_MSC_VER) && !defined(__clang__)
#include "renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(StrangeDemo)

StrangeDemo::StrangeDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mRenderer(nullptr),
	  mParticlesCount(100000)
{
}

StrangeDemo::~StrangeDemo()
{
}

void StrangeDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mRenderer = std::make_unique<eps::experiment::strange::renderer>();

	if (!mRenderer->initialize())
	{
		throw std::runtime_error("mRenderer->initialize() failed");
	}

	mRenderer->color_background(glm::vec3(0.0f, 0.0f, 0.25f));
	//
	mRenderer->color_gradient(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// construct renderer
	mRenderer->construct(size, mParticlesCount);
}

void StrangeDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
}

}
