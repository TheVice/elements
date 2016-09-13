
#include "LiquidDemo.h"
#include "Game.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

LiquidDemo::LiquidDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mLiquidRendererFactory(nullptr)
{
}

LiquidDemo::~LiquidDemo()
{
	mLiquidRendererFactory->close(mRenderId);
}

void LiquidDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mLiquidRendererFactory = std::make_unique<liquid_renderer_factory>();
	//
	bool preview = true;
	mRenderId = mLiquidRendererFactory->open(preview);
	//
	auto renderer = mLiquidRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuantity))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	if (!renderer->set_background(sBackground))
	{
		throw std::runtime_error("renderer->set_background() failed");
	}

	renderer->set_color(sColor.x, sColor.y, sColor.z, sColor.w);
	renderer->acceleration(sGravity.x, sGravity.y, sGravity.z);
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void LiquidDemo::Update(const Library::GameTime&)
{
	static bool touchDown = false;
	auto renderer = mLiquidRendererFactory->get(mRenderId);
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

void LiquidDemo::Draw(const Library::GameTime&)
{
	auto renderer = mLiquidRendererFactory->get(mRenderId);
	renderer->render();
}

const char* LiquidDemo::sBackground = "assets/textures/background.png";
const glm::vec4 LiquidDemo::sColor = { 0.33f, 0.098f, 0.38f, 0.44f }; //#55196271
const int LiquidDemo::sQuantity = 1;
const glm::vec3 LiquidDemo::sGravity = { 0.0f, -9.8f, 0.0f };

}
