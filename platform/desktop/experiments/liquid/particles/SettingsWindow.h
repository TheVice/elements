#ifndef _SETTINGS_WINDOW_H_
#define _SETTINGS_WINDOW_H_

#include "DrawableGameComponent.h"
#include "ui/system.h"

namespace Rendering
{
class SettingsWindow : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(SettingsWindow, DrawableGameComponent)

public:
	SettingsWindow(Library::Game& aGame);
	~SettingsWindow();

public:
	SettingsWindow() = delete;
	SettingsWindow(const SettingsWindow& aRhs) = delete;
	SettingsWindow& operator = (const SettingsWindow& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

public:
	bool mTouchDown;
	eps::math::mat4 mTransformTouch;
	std::unique_ptr<eps::ui::system> mUiSystem;
};
}

#endif
