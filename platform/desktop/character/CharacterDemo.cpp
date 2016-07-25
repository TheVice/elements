
#include "CharacterDemo.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(CharacterDemo)

CharacterDemo::CharacterDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
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
	//void set_rotation(float theta, float phi);
}

void CharacterDemo::Draw(const Library::GameTime&)
{
	auto renderer = mCharacterRendererFactory->get(mRenderId);
	renderer->render();
}

const std::string CharacterDemo::sModel = "assets/models/R2-D2/R2-D2.dae";

}
