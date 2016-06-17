
#include "LiquidDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#include "elements/simulation/liquid/system.h"
#endif
#include "Game.h"
#include "elements/math/transform.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

LiquidDemo::LiquidDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mSystem(nullptr),
	  mRenderer(nullptr),
	  mTransform(),
	  mTransformTouch(),
	  mPrevScreenPos(),
	  mParticlesCount(700)
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
	mSystem->set_density(30.0f);
	//
	mSystem->set_viscosity(1.0f, 0.1f);
	//
	mSystem->set_pressure(0.3f, 6.0f);
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
	mRenderer->set_surface_color(glm::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	// construct renderer
	const glm::uvec2 sim_size(10.0f, 10.0f * mGame->GetAspectRatio());
	mRenderer->construct(size, sim_size, 512);
	// setup transformation matrix
	mTransform = eps::math::translate(0.0f, sim_size.y, 0.0f) *
			eps::math::scale(sim_size.x, -sim_size.y, 1.0f) *
			eps::math::scale(1.0f / size.x, 1.0f / size.y, 1.0f);
	//
	mTransformTouch = eps::math::translate(0.0f, size.y, 0.0f) *
			eps::math::scale(1.0f, -1.0f, 1.0f);
}

void LiquidDemo::Update(const Library::GameTime&)
{
	//if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		glm::dvec2 screen_pos;
		glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);
		screen_pos.y = mGame->GetScreenHeight() - screen_pos.y;
		// touch
		const eps::math::vec4 pos = mTransform * eps::math::vec4(screen_pos.x, screen_pos.y, 1.0f, 1.0f);
//		const eps::math::vec4 pos_touch = mTransformTouch * eps::math::vec4(screen_pos.x, screen_pos.y, 1.0f, 1.0f);
//		const eps::math::vec4 pos = mTransform * eps::math::vec4(pos_touch.x, pos_touch.y, 1.0f, 1.0f);

		if (IsMove(screen_pos, mPrevScreenPos))
		{
			mSystem->touch(eps::math::vec2(pos.x, pos.y), 1.0f);
		}
		else
		{
			mSystem->touch(eps::math::vec2(pos.x, pos.y), 0.0f);
		}

		mPrevScreenPos = screen_pos;
	}
}

void LiquidDemo::Draw(const Library::GameTime&)
{
	mRenderer->render();
}

GLboolean LiquidDemo::IsMove(glm::dvec2 aScreenPos, glm::dvec2 aPrevScreenPos)
{
	return (std::abs(aScreenPos.x - aPrevScreenPos.x) > 1.0f || std::abs(aScreenPos.y - aPrevScreenPos.y) > 1.0f);
}

}
