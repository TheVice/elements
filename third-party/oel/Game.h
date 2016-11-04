#ifndef _GAME_H_
#define _GAME_H_

#include "RTTI.h"
#include "ServiceContainer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>
#include <functional>

#ifdef WIN32
#include <windows.h>
#undef far
#undef near
#else
#include <X11/Xlib.h>
#endif

namespace Library
{
class GameComponent;

class Game : public RTTI
{
	RTTI_DECLARATIONS(Game, RTTI)

public:
	using KeyboardHandler = std::function<void(int, int, int, int)>;

public:
	Game(const std::string& aWindowTitle, GLuint aScreenWidth, GLuint aScreenHeight);
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
	const std::string& GetWindowTitle() const;

	GLuint GetScreenWidth() const;
	GLuint GetScreenHeight() const;
	GLint GetDPI() const;

	GLfloat GetAspectRatio() const;
	bool IsFullScreen() const;

	const std::vector<GameComponent*>& GetComponents() const;
	const ServiceContainer& GetServices() const;

	virtual void Run();
	virtual void Exit();
	virtual bool Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	void AddKeyboardHandler(KeyboardHandler aHandler);
	void RemoveKeyboardHandler(KeyboardHandler aHandler);

protected:
	virtual void InitializeWindow();
	virtual void InitializeOpenGL();
	virtual void Shutdown();

protected:
	static const GLuint sDefaultScreenWidth;
	static const GLuint sDefaultScreenHeight;
	std::string mWindowTitle;
	GLFWwindow* mWindow;
	GLuint mScreenWidth;
	GLuint mScreenHeight;
	bool mIsFullScreen;
	std::vector<GameComponent*> mComponents;
	ServiceContainer mServices;
	std::map<KeyboardHandler*, KeyboardHandler> mKeyboardHandlers;

private:
	static Game* sInternalInstance;

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
