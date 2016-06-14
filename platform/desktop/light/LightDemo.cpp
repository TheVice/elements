
#include "LightDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#include "elements/simulation/air/system.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(LightDemo)

LightDemo::LightDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mSystem(nullptr),
	  mRenderer(nullptr),
	  mParticlesCount(10000)
{
}

LightDemo::~LightDemo()
{
}

void LightDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	// create simulation subsystem
	mSystem = std::make_unique<eps::simulation::air::system>();
	// construct with window size
	mSystem->construct(size);
	//
	mRenderer = std::make_unique<eps::experiment::light::renderer>();

	if (!mRenderer->initialize())
	{
		throw std::runtime_error("mRenderer->initialize() failed");
	}

	// spawn simulation
	mRenderer->set_field(mSystem->spawn(1.0f / 60.0f));
	//
	const std::string pathToTexture = "textures/noise.png";
	mRenderer->set_background(pathToTexture);
	//
	mRenderer->set_color(glm::vec3(0.14f, 0.25f, 0.15f));
	// construct renderer
	mRenderer->construct(size, mParticlesCount);
}

void LightDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(aGameTime.GetElapsedGameTime());
}

}
