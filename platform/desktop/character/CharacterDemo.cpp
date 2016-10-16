
#include "CharacterDemo.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(CharacterDemo)

CharacterDemo::CharacterDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mCharacterRendererFactory(nullptr),
	rate_(60)
{
}

CharacterDemo::~CharacterDemo()
{
	mCharacterRendererFactory->close(mRenderId);
}

void CharacterDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mCharacterRendererFactory = std::make_unique<character_renderer_factory>();
	//
	bool preview = true;
	mRenderId = mCharacterRendererFactory->open(preview);
	//
	auto renderer = mCharacterRendererFactory->get(mRenderId);

	if (!renderer->startup(size))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	if (!renderer->set_model(sModel))
	{
		throw std::runtime_error("renderer->set_model() failed");
	}

	//renderer->set_rotation(glm::two_over_root_pi<float>(), glm::quarter_pi<float>());
}

void CharacterDemo::Update(const Library::GameTime&)
{
	static float theta = glm::two_over_root_pi<float>();
	static float phi = glm::quarter_pi<float>();
	static float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		auto renderer = mCharacterRendererFactory->get(mRenderId);
		//
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

		renderer->set_rotation(theta, phi);
	}
}

void CharacterDemo::Draw(const Library::GameTime&)
{
	auto renderer = mCharacterRendererFactory->get(mRenderId);
	renderer->render();
}

const std::string CharacterDemo::sModel = "assets/models/R2-D2/R2-D2.dae";

}
