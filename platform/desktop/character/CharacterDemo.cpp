
#include "CharacterDemo.h"

namespace Rendering
{
RTTI_DEFINITIONS(CharacterDemo)

CharacterDemo::CharacterDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr),
	rate_(60),
	mKeyboardHandler(nullptr)
{
}

CharacterDemo::~CharacterDemo()
{
	mRendererFactory->close(mRenderId);
	mGame->RemoveKeyboardHandler(mKeyboardHandler);
}

bool CharacterDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mRendererFactory = eps::utils::make_unique<RendererFactory>();
	mRenderId = mRendererFactory->open(true);
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size))
	{
		return false;
	}

	if (!renderer->set_model(sModels[0]))
	{
		return false;
	}

	// Attach the keyboard handler
	mKeyboardHandler = std::bind(&CharacterDemo::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	mGame->AddKeyboardHandler(mKeyboardHandler);
	//
	return true;
}

void CharacterDemo::Update()
{
	static float theta = glm::two_over_root_pi<float>();
	static float phi = glm::quarter_pi<float>();
	static float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		const float elapsedTime = rate_.elapsed() - lastTime;
		lastTime = rate_.elapsed();

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_UP) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_W))
		{
			theta += glm::radians<float>(1) * elapsedTime;
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_DOWN) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_S))
		{
			theta -= glm::radians<float>(1) * elapsedTime;
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_LEFT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_A))
		{
			phi += glm::radians<float>(1) * elapsedTime;
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_RIGHT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_D))
		{
			phi -= glm::radians<float>(1) * elapsedTime;
		}

		auto renderer = mRendererFactory->get(mRenderId);
		renderer->set_rotation(theta, phi);
	}
}

void CharacterDemo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

void CharacterDemo::OnKey(int aKey, int aScancode, int aAction, int aMods)
{
	(void)aScancode;
	(void)aMods;
	static int modelNumber = 0;

	if (aKey == GLFW_KEY_SPACE && aAction == GLFW_PRESS)
	{
		if (modelNumber < 1)
		{
			modelNumber++;
		}
		else
		{
			modelNumber = 0;
		}

		auto renderer = mRendererFactory->get(mRenderId);
		renderer->set_model(sModels[modelNumber]);
	}
}

const std::string CharacterDemo::sModels[] = { "assets/models/R2-D2/R2-D2.dae", "assets/models/C-3PO/C-3PO.dae" };

}
