
#include "LiquidDemo.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

LiquidDemo::LiquidDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr)
{
}

LiquidDemo::~LiquidDemo()
{
	mRendererFactory->close(mRenderId);
}

bool LiquidDemo::Initialize()
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

	renderer->set_color(sColor.x, sColor.y, sColor.z, sColor.w);
	renderer->acceleration(sGravity.x, sGravity.y, sGravity.z);
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//
	return true;
}

void LiquidDemo::Update()
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

void LiquidDemo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

const char* LiquidDemo::sBackground = "assets/textures/background.png";
const glm::vec4 LiquidDemo::sColor = { 0.33f, 0.098f, 0.38f, 0.44f }; //#55196271
const int LiquidDemo::sQuantity = 1;
const glm::vec3 LiquidDemo::sGravity = { 0.0f, -9.8f, 0.0f };

}
