
#include "Demo.h"
#include "ui/types.h"
#include "android/input.h"
#include "metrics/metrics.h"

namespace Rendering
{
RTTI_DEFINITIONS(Demo)

Demo::Demo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr),
	rate_(60),
	mKeyboardHandler(nullptr)
{
}

Demo::~Demo()
{
	mRendererFactory->close(mRenderId);
	mGame->RemoveKeyboardHandler(mKeyboardHandler);
}

bool Demo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mRendererFactory = eps::utils::make_unique<RendererFactory>();
	mRenderId = mRendererFactory->open();
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size))
	{
		return false;
	}

	// Attach the keyboard handler
	mKeyboardHandler = std::bind(&Demo::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	mGame->AddKeyboardHandler(mKeyboardHandler);
	//
	return true;
}

void Demo::Update()
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
			renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
							static_cast<int>(eps::ui::touch_finger::finger0));
			touchDown = true;
		}

		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}
	else if (touchDown)
	{
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
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
			phi = std::min(glm::radians<float>(10), phi + glm::radians<float>(1) * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_RIGHT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_D))
		{
			phi = std::max(glm::radians<float>(-10), phi - glm::radians<float>(1) * elapsedTime);
		}

		renderer->set_rotation(theta, phi);
	}
}

void Demo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

void Demo::OnKey(int aKey, int aScancode, int aAction, int aMods)
{
	(void)aScancode;
	(void)aMods;
	//
	auto renderer = mRendererFactory->get(mRenderId);
	glm::dvec2 screen_pos;
	//
	using namespace eps::metric_literals;

	if (aKey == GLFW_KEY_1 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(9_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_2 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(49_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_3 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(89_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_4 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(129_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_5 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(169_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_6 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(209_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_7 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(249_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}

	if (aKey == GLFW_KEY_8 && aAction == GLFW_PRESS)
	{
		screen_pos = glm::dvec2(289_dp, mGame->GetScreenHeight() - 9_dp);
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_DOWN,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_MOVE,
						static_cast<int>(eps::ui::touch_finger::finger0));
		renderer->touch(screen_pos.x, screen_pos.y, AMOTION_EVENT_ACTION_UP,
						static_cast<int>(eps::ui::touch_finger::finger0));
	}
}

}
