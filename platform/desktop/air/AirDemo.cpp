
#include "AirDemo.h"
#include "Game.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(AirDemo)

AirDemo::AirDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mTouchDown(false),
	mRenderId(-1),
	mAirRendererFactory(nullptr)
{
}

AirDemo::~AirDemo()
{
	mAirRendererFactory->close(mRenderId);
}

void AirDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mAirRendererFactory = std::make_unique<air_renderer_factory>();
	//
	bool preview = true;
	mRenderId = mAirRendererFactory->open(preview);
	//
	auto renderer = mAirRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuantity))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	renderer->set_colors(sColorSpeedDown, sColorSpeedUp);
}

void AirDemo::Update(const Library::GameTime&)
{
	auto renderer = mAirRendererFactory->get(mRenderId);
	//
	glm::dvec2 screen_pos;
	glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN);
		mTouchDown = true;
	}
	else if (mTouchDown)
	{
		mTouchDown = false;
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE);
	}
}

void AirDemo::Draw(const Library::GameTime&)
{
	auto renderer = mAirRendererFactory->get(mRenderId);
	renderer->render();
}

const glm::vec3 AirDemo::sColorSpeedDown = { 0.0f, 0.57f, 0.92f }; //# 0091EA
const glm::vec3 AirDemo::sColorSpeedUp = { 1.0f, 0.44f, 0.0f }; //# FF6F00
const int AirDemo::sQuantity = 1000000;

}
