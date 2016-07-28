
#include "CharacterDemo.h"
#include "Game.h"
#include "android/input.h"

namespace Rendering
{
RTTI_DEFINITIONS(CharacterDemo)

CharacterDemo::CharacterDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mThetaAndPhi(),
	mRenderId(-1),
	mCharacterRendererFactory(nullptr)
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
}

void CharacterDemo::Update(const Library::GameTime&)
{
	auto renderer = mCharacterRendererFactory->get(mRenderId);
	//
	static int multiPlayX = 1;
	static int multiPlayY = 1;
	//
	mThetaAndPhi.x += multiPlayX * glm::radians<float>(0.5f);
	mThetaAndPhi.y += multiPlayY * glm::radians<float>(0.5f);

	if (mThetaAndPhi.x > glm::radians<float>(360.0f) || mThetaAndPhi.x < 0.0f)
	{
		multiPlayX *= -1;
		mThetaAndPhi.x += multiPlayX * glm::radians<float>(0.5f);
	}

	if (mThetaAndPhi.y > glm::radians<float>(360.0f) || mThetaAndPhi.y < 0.0f)
	{
		multiPlayY *= -1;
		mThetaAndPhi.y += multiPlayY * glm::radians<float>(0.5f);
	}

	renderer->set_rotation(mThetaAndPhi.x, mThetaAndPhi.y);
}

void CharacterDemo::Draw(const Library::GameTime&)
{
	auto renderer = mCharacterRendererFactory->get(mRenderId);
	renderer->render();
}

const std::string CharacterDemo::sModel = "assets/models/R2-D2/R2-D2.dae";

}
