
#include "Demo.h"
#include "ui/types.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(Demo)

Demo::Demo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mDemoRendererFactory(nullptr),
	rate_(60),
	mKeyboardHandler(nullptr)
{
}

Demo::~Demo()
{
	mDemoRendererFactory->close(mRenderId);
	mGame->RemoveKeyboardHandler(mKeyboardHandler);
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

	// Attach the keyboard handler
	mKeyboardHandler = std::bind(&Demo::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	mGame->AddKeyboardHandler(mKeyboardHandler);
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

	static float theta = glm::radians<float>(70);
	static float phi = glm::zero<float>();
	static float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		const float elapsedTime = rate_.elapsed() - lastTime;
		lastTime = rate_.elapsed();

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_UP) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_W))
		{
			theta = std::min(glm::radians<float>(90), theta + glm::radians<float>(1) * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_DOWN) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_S))
		{
			theta = std::max(glm::radians<float>(70), theta - glm::radians<float>(1) * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_LEFT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_A))
		{
			phi = std::min(glm::radians<float>(10), phi +glm::radians<float>(1) * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_RIGHT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_D))
		{
			phi = std::max(glm::radians<float>(-10), phi - glm::radians<float>(1) * elapsedTime);
		}

		renderer->set_rotation(theta, phi);
	}
}

void Demo::Draw(const Library::GameTime&)
{
	auto renderer = mDemoRendererFactory->get(mRenderId);
	renderer->render();
}

void Demo::OnKey(int aKey, int aScancode, int aAction, int aMods)
{
	(void)aScancode;
	(void)aMods;
	//
	auto renderer = mDemoRendererFactory->get(mRenderId);
	glm::dvec2 screen_pos;

	if (aKey == GLFW_KEY_1 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(9/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_2 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(49/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_3 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(89/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_4 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(129/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_5 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(169/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_6 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(209/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_7 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(249/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_8 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(289/*_dp*/, mGame->GetScreenHeight() - 9/*_dp*/);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE, static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP, static_cast<int>(eps::ui::touch_finger::finger0));
	}
}

}
