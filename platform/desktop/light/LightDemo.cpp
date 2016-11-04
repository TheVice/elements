
#include "LightDemo.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(LightDemo)

LightDemo::LightDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr)
{
}

LightDemo::~LightDemo()
{
	mRendererFactory->close(mRenderId);
}

bool LightDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mRendererFactory = eps::utils::make_unique<RendererFactory>();
	mRenderId = mRendererFactory->open(true);
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuantity))
	{
		return false;
	}

	if (!renderer->set_background(sBackground))
	{
		return false;
	}

	renderer->set_color(sColor);
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//
	return true;
}

void LightDemo::Update()
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

void LightDemo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

const char* LightDemo::sBackground = "assets/textures/background.png";
const glm::vec3 LightDemo::sColor = { 1.0f, 1.0f, 1.0f }; //# FFFFFF
const int LightDemo::sQuantity = 1000;

}
