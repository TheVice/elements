
#include "LightDemo.h"
#include "Game.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(LightDemo)

LightDemo::LightDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mTouchDown(false),
	mRenderId(-1),
	mLightRendererFactory(nullptr)
{
}

LightDemo::~LightDemo()
{
	mLightRendererFactory->close(mRenderId);
}

void LightDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mLightRendererFactory = std::make_unique<light_renderer_factory>();
	//
	bool preview = true;
	mRenderId = mLightRendererFactory->open(preview);
	//
	auto renderer = mLightRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuantity))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	if (!renderer->set_background(sBackground))
	{
		throw std::runtime_error("renderer->set_background() failed");
	}

	renderer->set_color(sColor);
}

void LightDemo::Update(const Library::GameTime&)
{
	auto renderer = mLightRendererFactory->get(mRenderId);
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
}

void LightDemo::Draw(const Library::GameTime&)
{
	auto renderer = mLightRendererFactory->get(mRenderId);
	renderer->render();
}

const char* LightDemo::sBackground =  "assets/textures/background.png";
const glm::vec3 LightDemo::sColor = { 1.0f, 1.0f, 1.0f }; //# FFFFFF
const int LightDemo::sQuantity = 1000;

}
