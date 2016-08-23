
#include "GameComponent.h"

namespace Library
{
RTTI_DEFINITIONS(GameComponent)

GameComponent::GameComponent() :
	mGame(nullptr),
	mEnabled(true)
{
}

GameComponent::GameComponent(Game& aGame) :
	mGame(&aGame),
	mEnabled(true)
{
}

GameComponent::~GameComponent()
{
}

Game* GameComponent::GetGame()
{
	return mGame;
}

void GameComponent::SetGame(Game& aGame)
{
	mGame = &aGame;
}

bool GameComponent::IsEnabled() const
{
	return mEnabled;
}

void GameComponent::SetEnabled(bool aEnabled)
{
	mEnabled = aEnabled;
}

void GameComponent::Initialize()
{
}

void GameComponent::Update(const GameTime&)
{
}

void GameComponent::Release()
{
}

}
