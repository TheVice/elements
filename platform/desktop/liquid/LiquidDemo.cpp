
#include "LiquidDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#include "elements/simulation/liquid/system.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

LiquidDemo::LiquidDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mSystem(nullptr),
	  mRenderer(nullptr),
	  mParticlesCount(1000)
{
}

LiquidDemo::~LiquidDemo()
{
}

void LiquidDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	// create simulation subsystem
	mSystem = std::make_unique<eps::simulation::liquid::system>();
	// construct with window size
	mSystem->construct(size, mParticlesCount);
	//
	mSystem->set_gravity(glm::vec2(1.0f, 1.0f));
	//
	mSystem->set_density(100.0f);
	//
	mSystem->set_viscosity(10.0f, 10.0f);
	//
	mSystem->set_pressure(10.0f, 10.0f);
	//
	mSystem->set_elasticity(10.0f);
	//
	mRenderer = std::make_unique<eps::experiment::liquid::renderer>();

	if (!mRenderer->initialize())
	{
		throw std::runtime_error("mRenderer->initialize() failed");
	}

	// spawn simulation
	mRenderer->set_particles(mSystem->spawn(1.0f / 60.0f));
	//
	const std::string pathToTexture = "textures/noise.png";
	mRenderer->set_surface_background(pathToTexture);
	//
	mRenderer->set_surface_color(glm::vec4(1.0f, 0.5f, 0.25f, 1.0f));
	// construct renderer
	const glm::uvec2 sim_size(size.x, size.y);
	mRenderer->construct(size, sim_size, 512);
}

void LiquidDemo::Update(const Library::GameTime&)
{
	glm::dvec2 pos;
	glfwGetCursorPos(mGame->GetWindow(), &pos.x, &pos.y);
	pos.y = mGame->GetScreenHeight() - pos.y;

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		GLfloat radius = 5.0f;
		mSystem->touch(glm::vec2(pos.x, pos.y), radius);
	}
}

void LiquidDemo::Draw(const Library::GameTime&)
{
	mRenderer->render();
}

}
