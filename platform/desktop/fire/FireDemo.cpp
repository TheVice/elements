
#include "FireDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(FireDemo)

FireDemo::FireDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mRenderer(nullptr),
	  mParticlesCount(10)
{
}

FireDemo::~FireDemo()
{
}

void FireDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mRenderer = std::make_unique<eps::experiment::fire::renderer>();

	if (!mRenderer->initialize())
	{
		throw std::runtime_error("mRenderer->initialize() failed");
	}

	mRenderer->set_background("textures/noise.png");
	//
	mRenderer->set_intensity(5.0f);
	//
	mRenderer->set_covering(5.0f);
	//
	mRenderer->set_color_hot(glm::vec3(1.0f, 0.0f, 0.0f));
	//
	mRenderer->set_color_cold(glm::vec3(0.0f, 1.0f, 1.0f));
	// construct renderer
	mRenderer->construct(size, mParticlesCount);
}

void FireDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
}

}
