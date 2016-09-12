#ifndef _DRAWABLE_UI_GAME_COMPONENT_H_
#define _DRAWABLE_UI_GAME_COMPONENT_H_

#include "DrawableGameComponent.h"
#include "ui/system.h"

namespace Library
{
class DrawableUiGameComponent : public DrawableGameComponent
{
	RTTI_DECLARATIONS(DrawableUiGameComponent, DrawableGameComponent)

public:
	DrawableUiGameComponent(Game& aGame);
	~DrawableUiGameComponent();

public:
	DrawableUiGameComponent() = delete;
	DrawableUiGameComponent(const DrawableUiGameComponent& aRhs) = delete;
	DrawableUiGameComponent& operator = (const DrawableUiGameComponent& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const GameTime& aGameTime) override;
	virtual void Draw(const GameTime& aGameTime) override;

private:
	eps::math::mat4 mTransformTouch;

protected:
	std::shared_ptr<eps::ui::control> mUiSystem;
};
}

#endif
