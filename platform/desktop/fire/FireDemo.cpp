
#include "FireDemo.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(FireDemo)

FireDemo::FireDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr)
{
}

FireDemo::~FireDemo()
{
	mRendererFactory->close(mRenderId);
}

bool FireDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mRendererFactory = eps::utils::make_unique<RendererFactory>();
	mRenderId = mRendererFactory->open(true);
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuality))
	{
		return false;
	}

	if (!renderer->set_background(sBackground))
	{
		return false;
	}

	renderer->set_color_hot(sColorHot);
	renderer->set_color_cold(sColorCold);
	//
	return true;
}

void FireDemo::Update()
{
	static bool touchDown = false;
	auto renderer = mRendererFactory->get(mRenderId);
	//
	glm::dvec2 screen_pos;
	glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		if (!touchDown)
		{
			renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN);
			touchDown = true;
		}

		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE);
	}
	else if (touchDown)
	{
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP);
		touchDown = false;
	}
}

void FireDemo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

const char* FireDemo::sBackground = "assets/textures/background.png"; //"images/background.jpg";
const glm::vec3 FireDemo::sColorHot = { 0.098f, 0.5f, 1.0f }; //# 1980ff
const glm::vec3 FireDemo::sColorCold = { 1.0f, 0.5f, 0.098f }; //# ff8019
const int FireDemo::sQuality = 1;

}
