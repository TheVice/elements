
#include "FireDemo.h"
#include "Game.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(FireDemo)

FireDemo::FireDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mTouchDown(false),
	mRenderId(-1),
	mFireRendererFactory(nullptr)
{
}

FireDemo::~FireDemo()
{
	mFireRendererFactory->close(mRenderId);
}

void FireDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mFireRendererFactory = std::make_unique<fire_renderer_factory>();
	//
	bool preview = true;
	mRenderId = mFireRendererFactory->open(preview);
	//
	auto renderer = mFireRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuality))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	if (!renderer->set_background(sBackground))
	{
		throw std::runtime_error("renderer->set_background() failed");
	}

	renderer->set_color_hot(sColorHot);
	renderer->set_color_cold(sColorCold);
}

void FireDemo::Update(const Library::GameTime&)
{
	auto renderer = mFireRendererFactory->get(mRenderId);
	//
	glm::dvec2 screen_pos;
	glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		mTouchDown = true;
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN);
	}
	else if (mTouchDown)
	{
		mTouchDown = false;
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP);
	}

	renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE);
}

void FireDemo::Draw(const Library::GameTime&)
{
	auto renderer = mFireRendererFactory->get(mRenderId);
	renderer->render();
}

const char* FireDemo::sBackground = "assets/textures/background.png"; //"images/background.jpg";
const glm::vec3 FireDemo::sColorHot = { 0.098f, 0.5f, 1.0f }; //# 1980ff
const glm::vec3 FireDemo::sColorCold = { 1.0f, 0.5f, 0.098f }; //# ff8019
const int FireDemo::sQuality = 1;

}
