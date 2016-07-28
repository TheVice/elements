#ifndef _GAME_H_
#define _GAME_H_

#include "RTTI.h"
#include "ServiceContainer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include <sstream>
#ifdef WIN32
#include <tchar.h>
#include <windows.h>
#undef far
#undef near
#else
#include <X11/Xlib.h>
#define TCHAR char
#define TEXT(A) A
#endif

namespace Library
{
class GameComponent;

class GameTime
{
public:
	GameTime() {};
};

class Game : public RTTI
{
	RTTI_DECLARATIONS(Game, RTTI)

public:
	typedef std::function<void(int, int, int, int)> KeyboardHandler;

public:
	Game(const TCHAR* aWindowTitle);
	virtual ~Game();

public:
	Game(const Game& aRhs) = delete;
	Game& operator = (const Game& aRhs) = delete;

public:
#ifndef WIN32
	Window GetWindowHandle() const;
#else
	HWND GetWindowHandle() const;
#endif
	GLFWwindow* GetWindow() const;
	const TCHAR* GetWindowTitle() const;

	GLuint GetScreenWidth() const;
	GLuint GetScreenHeight() const;

	GLfloat GetAspectRatio() const;
	bool IsFullScreen() const;

	const std::vector<GameComponent*>& GetComponents() const;
	const ServiceContainer& GetServices() const;

	virtual void Run();
	virtual void Exit();
	virtual void Initialize();
	virtual void Update(const GameTime& aGameTime);
	virtual void Draw(const GameTime& aGameTime);

	void AddKeyboardHandler(KeyboardHandler aHandler);
	void RemoveKeyboardHandler(KeyboardHandler aHandler);

protected:
	virtual void InitializeWindow();
	virtual void InitializeOpenGL();
	virtual void Shutdown();

	static const GLuint sDefaultScreenWidth;
	static const GLuint sDefaultScreenHeight;

#ifdef UNICODE
	std::wstring mWindowTitle;
#else
	std::string mWindowTitle;
#endif
	GLFWwindow* mWindow;
	GLuint mScreenWidth;
	GLuint mScreenHeight;
	bool mIsFullScreen;

	GameTime mGameTime;

	std::vector<GameComponent*> mComponents;
	ServiceContainer mServices;

	std::map<KeyboardHandler*, KeyboardHandler> mKeyboardHandlers;

private:
	static Game* sInternalInstance;
	static std::ostringstream sGlfwErrors;

	static void OnKey(GLFWwindow* aWindow, int aKey, int aScancode, int aAction, int aMods);
#ifndef WIN32
	static std::pair<int, int> CenterWindow(int aWindowWidth, int aWindowHeight);
#else
	static POINT CenterWindow(int aWindowWidth, int aWindowHeight);
#endif
	static void glfwErrorCallback(int aError, const char* aDescription);
};

}

#endif
