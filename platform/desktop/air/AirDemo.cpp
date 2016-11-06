
#include "AirDemo.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(AirDemo)

AirDemo::AirDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr)
{
}

AirDemo::~AirDemo()
{
	mRendererFactory->close(mRenderId);
}

bool AirDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mRendererFactory = eps::utils::make_unique<RendererFactory>();
	mRenderId = mRendererFactory->open(true);
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuantity))
	{
		return false;
	}

	renderer->set_colors(sColorSpeedDown, sColorSpeedUp);
	return true;
}

void AirDemo::Update()
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

void AirDemo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

const glm::vec3 AirDemo::sColorSpeedDown = { 0.0f, 0.57f, 0.92f }; //# 0091EA
const glm::vec3 AirDemo::sColorSpeedUp = { 1.0f, 0.44f, 0.0f }; //# FF6F00
const int AirDemo::sQuantity = 1000000;

}
