
#include "CompassDemo.h"

namespace Rendering
{
RTTI_DEFINITIONS(CompassDemo)

CompassDemo::CompassDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr),
	rate_(60)
{
}

CompassDemo::~CompassDemo()
{
	mRendererFactory->close(mRenderId);
}

bool CompassDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mRendererFactory = eps::utils::make_unique<RendererFactory>();
	mRenderId = mRendererFactory->open();
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size))
	{
		return false;
	}

	return true;
}

void CompassDemo::Update()
{
	static const float east = -glm::half_pi<float>();
	static const float west = glm::half_pi<float>();
	static const float north = glm::zero<float>();
	static const float south = glm::pi<float>();
	static float omega = 0.0f;
	static float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		const float elapsedTime = rate_.elapsed() - lastTime;
		lastTime = rate_.elapsed();

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_UP) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_W))
		{
			if (omega < north)
			{
				omega += glm::radians<float>(1) * elapsedTime;
			}
			else
			{
				omega -= glm::radians<float>(1) * elapsedTime;
			}
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_DOWN) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_S))
		{
			if (omega < south)
			{
				omega += glm::radians<float>(1) * elapsedTime;
			}
			else
			{
				omega -= glm::radians<float>(1) * elapsedTime;
			}
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_LEFT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_A))
		{
			if (omega < west)
			{
				omega += glm::radians<float>(1) * elapsedTime;
			}
			else
			{
				omega -= glm::radians<float>(1) * elapsedTime;
			}
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_RIGHT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_D))
		{
			if (omega < east)
			{
				omega += glm::radians<float>(1) * elapsedTime;
			}
			else
			{
				omega -= glm::radians<float>(1) * elapsedTime;
			}
		}

		auto renderer = mRendererFactory->get(mRenderId);
		renderer->set_rotation(omega);
	}
}

void CompassDemo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

}
