#ifndef _DRAWABLE_UI_GAME_COMPONENT_H_
#define _DRAWABLE_UI_GAME_COMPONENT_H_

#include <DrawableGameComponent.h>
#include <elements/ui/system.h>

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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::math::mat4 mTransformTouch;

protected:
	std::shared_ptr<eps::ui::control> mUiSystem;
};
}

#endif
