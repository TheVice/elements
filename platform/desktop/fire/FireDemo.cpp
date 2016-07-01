
#include "FireDemo.h"
#if defined (_MSC_VER) && !defined(__clang__)
#include "fire_renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(FireDemo)

FireDemo::FireDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
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
	enum QUALITY { LOW = 0, MEDIUM = 1, HIGH = 2 };
	size_t quality = MEDIUM;

	if (!renderer->startup(size, quality))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	if (!renderer->set_background("textures/noise.png"))
	{
		throw std::runtime_error("renderer->set_background() failed");
	}

	renderer->set_color_hot(glm::vec3(1.0f, 0.0f, 0.0f));
	//
	renderer->set_color_cold(glm::vec3(0.0f, 1.0f, 1.0f));
}

void FireDemo::Update(const Library::GameTime&)
{
	auto renderer = mFireRendererFactory->get(mRenderId);
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

void FireDemo::Draw(const Library::GameTime&)
{
	auto renderer = mFireRendererFactory->get(mRenderId);
	renderer->render();
}

}
