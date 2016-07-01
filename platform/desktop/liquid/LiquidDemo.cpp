
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
	  mLiquidRendererFactory(nullptr),
	  mGravity(sDefaultGravity)
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
	enum QUALITY { LOW = 0, MEDIUM = 1, HIGH = 2};
	size_t quality = MEDIUM;

	if (!renderer->startup(size, quality))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	if (!renderer->set_background("textures/noise.png"))
	{
		throw std::runtime_error("renderer->set_background() failed");
	}

	renderer->set_color(1.0f, 0.65f, 0.95f, 1.0f);
	//
	renderer->acceleration(mGravity.x, mGravity.y, 0.0f);
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

const glm::vec2 LiquidDemo::sDefaultGravity(0.0f, -9.8f);

}
