
#include "DrawableGameComponent.h"

namespace Library
{
RTTI_DEFINITIONS(DrawableGameComponent)

DrawableGameComponent::DrawableGameComponent() :
	GameComponent(),
	mVisible(true)
{
}

DrawableGameComponent::DrawableGameComponent(Game& aGame) :
	GameComponent(aGame),
	mVisible(true)
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

void DrawableGameComponent::Draw()
{
}

}
