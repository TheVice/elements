#ifndef _DRAWABLE_GAME_COMPONENT_H_
#define _DRAWABLE_GAME_COMPONENT_H_

#include "GameComponent.h"

namespace Library
{
class Camera;

class DrawableGameComponent : public GameComponent
{
	RTTI_DECLARATIONS(DrawableGameComponent, GameComponent)

public:
	DrawableGameComponent();
	DrawableGameComponent(Game& aGame);
	DrawableGameComponent(Game& aGame, Camera& aCamera);
	virtual ~DrawableGameComponent();

public:
	DrawableGameComponent(const DrawableGameComponent& aRhs) = delete;
	DrawableGameComponent& operator = (const DrawableGameComponent& aRhs) = delete;

public:
	bool IsVisible() const;
	void SetVisible(bool aVisible);

	Camera* GetCamera();
	void SetCamera(Camera* aCamera);

	virtual void Draw(const GameTime& aGameTime);

protected:
	bool mVisible;
	Camera* mCamera;
};
}

#endif
