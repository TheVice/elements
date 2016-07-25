
#include "DrawableGameComponent.h"

namespace Library
{
RTTI_DEFINITIONS(DrawableGameComponent)

DrawableGameComponent::DrawableGameComponent() :
	GameComponent(),
	mVisible(true),
	mCamera(nullptr)
{
}

DrawableGameComponent::DrawableGameComponent(Game& aGame) :
	GameComponent(aGame),
	mVisible(true),
	mCamera(nullptr)
{
}

DrawableGameComponent::DrawableGameComponent(Game& aGame, Camera& aCamera) :
	GameComponent(aGame),
	mVisible(true),
	mCamera(&aCamera)
{
}

DrawableGameComponent::~DrawableGameComponent()
{
}

bool DrawableGameComponent::IsVisible() const
{
	return mVisible;
}

void DrawableGameComponent::SetVisible(bool aVisible)
{
	mVisible = aVisible;
}

Camera* DrawableGameComponent::GetCamera()
{
	return mCamera;
}

void DrawableGameComponent::SetCamera(Camera* aCamera)
{
	mCamera = aCamera;
}

void DrawableGameComponent::Draw(const GameTime&)
{
}

}
