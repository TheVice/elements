
#include "Demo.h"
#include "ui/types.h"
#include "android/input.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(Demo)

Demo::Demo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mDemoRendererFactory(nullptr)
{
}

Demo::~Demo()
{
	mDemoRendererFactory->close(mRenderId);
}

void Demo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mDemoRendererFactory = std::make_unique<demo_renderer_factory>();
	mRenderId = mDemoRendererFactory->open();
	auto renderer = mDemoRendererFactory->get(mRenderId);

	if (!renderer->startup(size))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	renderer->set_rotation(glm::two_over_root_pi<float>(), glm::quarter_pi<float>());
}

void Demo::Update(const Library::GameTime&)
{
	static bool touchDown = false;
	auto renderer = mDemoRendererFactory->get(mRenderId);
	//
	glm::dvec2 screen_pos;
	glfwGetCursorPos(mGame->GetWindow(), &screen_pos.x, &screen_pos.y);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		if (!touchDown)
		{
			renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
			touchDown = true;
		}

		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
	}
	else if (touchDown)
	{
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
		touchDown = false;
	}
}

void Demo::Draw(const Library::GameTime&)
{
	auto renderer = mDemoRendererFactory->get(mRenderId);
	renderer->render();
}

}
