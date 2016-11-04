#ifndef _DRAWABLE_GAME_COMPONENT_H_
#define _DRAWABLE_GAME_COMPONENT_H_

#include "GameComponent.h"

namespace Library
{
class DrawableGameComponent : public GameComponent
{
	RTTI_DECLARATIONS(DrawableGameComponent, GameComponent)

public:
	DrawableGameComponent();
	DrawableGameComponent(Game& aGame);
	virtual ~DrawableGameComponent();

public:
	DrawableGameComponent(const DrawableGameComponent& aRhs) = delete;
	DrawableGameComponent& operator = (const DrawableGameComponent& aRhs) = delete;

public:
	bool IsVisible() const;
	void SetVisible(bool aVisible);

	virtual void Draw();

protected:
	bool mVisible;
};
}

#endif
