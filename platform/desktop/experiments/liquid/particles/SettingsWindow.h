#ifdef A
#ifndef _SETTINGS_WINDOW_H_
#define _SETTINGS_WINDOW_H_

#include "GameComponent.h"
#include "ui/system.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>

namespace Rendering
{
class SettingsWindow : public Library::GameComponent
{
	RTTI_DECLARATIONS(SettingsWindow, GameComponent)

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
	virtual void Release() override;

public:
	GLFWwindow* GetWindow() const;

private:
	GLFWwindow* mWindow;
	std::unique_ptr<std::thread> mWindowThread;

public:
	bool mTouchDown;
	eps::math::mat4 mTransformTouch;
	std::unique_ptr<eps::ui::system> mUiSystem;
};
}

#endif
#endif
