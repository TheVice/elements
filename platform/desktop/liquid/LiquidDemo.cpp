
#include "LiquidDemo.h"
#if defined (_MSC_VER) && !defined(__clang__)
#include "liquid_renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

LiquidDemo::LiquidDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
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
}

void LiquidDemo::Update(const Library::GameTime&)
{
	auto renderer = mLiquidRendererFactory->get(mRenderId);
	//
	glm::dvec2 screen_pos;
	glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE);
	}
	else
	{
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN);
	}
}

void LiquidDemo::Draw(const Library::GameTime&)
{
	auto renderer = mLiquidRendererFactory->get(mRenderId);
	renderer->render();
}

const char* LiquidDemo::sBackground = "textures/background.png";
const glm::vec4 LiquidDemo::sColor = { 0.33f, 0.098f, 0.38f, 0.44f }; //#55196271
const int LiquidDemo::sQuantity = 1;
const glm::vec3 LiquidDemo::sGravity = { 0.0f, -9.8f, 0.0f };

}
