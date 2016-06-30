
#include "LiquidDemo.h"
#if defined (_MSC_VER) && !defined(__clang__)
#include "renderer.h"
#include "elements/simulation/liquid/system.h"
#include "liquid_renderer.h"
#endif
#include "Game.h"
#include "elements/math/transform.h"
#include <memory>
#define A
namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

LiquidDemo::LiquidDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mSystem(nullptr),
	  mRenderer(nullptr),
	  mTransform(),
	  mTransformTouch(),
	  mPrevScreenPos(),
	  mParticlesCount(700),
	  mLiquidRenderer(nullptr),
	  mRenderId(-1),
	  mLiquidRendererFactory(nullptr),
	  mGravity(sDefaultGravity)
{
}

LiquidDemo::~LiquidDemo()
{
#ifdef C
	mLiquidRendererFactory->close(mRenderId);
#endif
}

void LiquidDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
#ifdef A
	const glm::uvec2 sim_size(10.0f, 10.0f * mGame->GetAspectRatio());
	// create simulation subsystem
	mSystem = std::make_unique<eps::simulation::liquid::system>();
	// construct with window size
	mSystem->construct(sim_size, mParticlesCount);
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
	mRenderer->construct(size, sim_size, 512);
	// setup transformation matrix
	mTransform = eps::math::translate(0.0f, sim_size.y, 0.0f) *
				 eps::math::scale(sim_size.x, -sim_size.y, 1.0f) *
				 eps::math::scale(1.0f / size.x, 1.0f / size.y, 1.0f);
	//
	mTransformTouch = eps::math::translate(0.0f, size.y, 0.0f) *
					  eps::math::scale(1.0f, -1.0f, 1.0f);
#endif
#ifdef B
	bool preview = false;
	mLiquidRenderer = std::make_unique<liquid_renderer>(preview);
	//
	size_t quality = 1;

	if (!mLiquidRenderer->startup(size, quality))
	{
		throw std::runtime_error("mLiquidRenderer->startup() failed");
	}

	mLiquidRenderer->set_color(0.0f, 0.65f, 0.95f, 1.0f);
#endif
#ifdef C
	mLiquidRendererFactory = std::make_unique<liquid_renderer_factory>();
	//
	bool preview = false;
	mRenderId = mLiquidRendererFactory->open(preview);
	//
	auto renderer = mLiquidRendererFactory->get(mRenderId);
	enum QUALITY { LOW = 0, MEDIUM = 1, HIGH = 2};
	size_t quality = MEDIUM;

	if (!renderer->startup(size, quality))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	const std::string pathToTexture = "textures/noise.png";
	renderer->set_background(pathToTexture.c_str());
	//
	renderer->set_color(1.0f, 0.65f, 0.95f, 1.0f);
#endif
}

void LiquidDemo::Update(const Library::GameTime&)
{
#ifdef A
	//if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	/*{
		glm::dvec2 screen_pos;
		glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);
		screen_pos.y = mGame->GetScreenHeight() - screen_pos.y;
		// touch
		const eps::math::vec4 pos = mTransform * eps::math::vec4(screen_pos.x, screen_pos.y, 1.0f, 1.0f);
		// const eps::math::vec4 pos_touch = mTransformTouch * eps::math::vec4(screen_pos.x, screen_pos.y, 1.0f, 1.0f);
		// const eps::math::vec4 pos = mTransform * eps::math::vec4(pos_touch.x, pos_touch.y, 1.0f, 1.0f);

		if (IsMove(screen_pos, mPrevScreenPos))
		{
			mSystem->touch(eps::math::vec2(pos.x, pos.y), 1.0f);
		}
		else
		{
			mSystem->touch(eps::math::vec2(pos.x, pos.y), 0.0f);
		}

		mPrevScreenPos = screen_pos;
	}*/
	mSystem->set_gravity(mGravity);
#endif
#ifdef B
//	glm::dvec2 screen_pos;
//	glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);
//	screen_pos.y = mGame->GetScreenHeight() - screen_pos.y;
	//
	mLiquidRenderer->acceleration(mGravity.x, mGravity.y, 0.0f);
//	mLiquidRenderer->touch(screen_pos.x, screen_pos.y, 0);
#endif
#ifdef C
//	glm::dvec2 screen_pos;
//	glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);
	//
	auto renderer = mLiquidRendererFactory->get(mRenderId);
	renderer->acceleration(mGravity.x, mGravity.y, 0.0f);
//	renderer->touch(screen_pos.x, screen_pos.y, 0);
#endif
}

void LiquidDemo::Draw(const Library::GameTime&)
{
#ifdef A
	mRenderer->render();
#endif
#ifdef B
	mLiquidRenderer->render();
#endif
#ifdef C
	auto renderer = mLiquidRendererFactory->get(mRenderId);
	renderer->render();
#endif
}

GLboolean LiquidDemo::IsMove(glm::dvec2 aScreenPos, glm::dvec2 aPrevScreenPos)
{
	return (std::abs(aScreenPos.x - aPrevScreenPos.x) > 1.0f || std::abs(aScreenPos.y - aPrevScreenPos.y) > 1.0f);
}

const glm::vec2 LiquidDemo::sDefaultGravity(0.0f, -9.8f);

}
