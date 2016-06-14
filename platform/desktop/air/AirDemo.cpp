
#include "AirDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#include "elements/simulation/air/system.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(AirDemo)

AirDemo::AirDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mSystem(nullptr),
	  mRenderer(nullptr),
	  mParticlesCount(10)
{
}

AirDemo::~AirDemo()
{
}

void AirDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	// create simulation subsystem
	mSystem = std::make_unique<eps::simulation::air::system>();
	// construct with window size
	mSystem->construct(size);
	//
	mRenderer = std::make_unique<eps::experiment::air::renderer>();

	if (!mRenderer->initialize())
	{
		throw std::runtime_error("mRenderer->initialize() failed");
	}

	// spawn simulation
	mRenderer->set_field(mSystem->spawn(1.0f / 60.0f));
	//
	mRenderer->set_colors(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	// construct renderer
	mRenderer->construct(size, mParticlesCount);
}

void AirDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
	// mSystem->spawn(1.0f / 60.0f);
	// mRenderer->render(static_cast<float>(1000000.0f * aGameTime.GetElapsedGameTime()));
}

}
