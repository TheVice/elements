
#include "AirDemo.h"
#if defined (_MSC_VER) && !defined(__clang__)
#include "renderer.h"
#include "elements/simulation/air/system.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(AirDemo)

AirDemo::AirDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mSystem(nullptr),
	  mRenderer(nullptr),
	  mParticlesCount(100000),
	  mTouchDown(false)
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

void AirDemo::Update(const Library::GameTime&)
{
	/*glm::dvec2 pos;
	glfwGetCursorPos(mGame->GetWindow(), &pos.x, &pos.y);
	pos.y = mGame->GetScreenHeight() - pos.y;

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		mSystem->touch_down(static_cast<float>(pos.x), static_cast<float>(pos.y));
		mTouchDown = true;
	}
	else if (mTouchDown)
	{
		mTouchDown = false;
		mSystem->touch_up(static_cast<float>(pos.x), static_cast<float>(pos.y));
	}*/
}

void AirDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
}

}
