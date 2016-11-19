#ifndef _GAME_H_
#define _GAME_H_

#include "RTTI.h"
#include "ServiceContainer.h"

#define GLEW_STATIC
#include <GL/glew.h>
#ifdef WIN32
#ifndef _WIN32
#define _WIN32
#endif
#define NOCOMM
#define WIN32_LEAN_AND_MEAN
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#else
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#endif
#include <GLFW/glfw3.h>

#include <map>
#include <vector>
#include <utility>
#include <functional>

#ifndef WIN32
#include <X11/Xlib.h>
#else
#include <windows.h>
#undef far
#undef near
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
	GLfloat GetAspectRatio() const;
	GLint GetDPI() const;
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
	static const GLuint sDefaultDPI;

	std::string mWindowTitle;
	GLuint mScreenWidth;
	GLuint mScreenHeight;
	bool mIsFullScreen;
	GLFWwindow* mWindow;
	std::vector<GameComponent*> mComponents;
	ServiceContainer mServices;
	std::map<KeyboardHandler*, KeyboardHandler> mKeyboardHandlers;

private:
	static Game* sInternalInstance;

	static void OnKey(GLFWwindow* aWindow, int aKey, int aScancode, int aAction, int aMods);
	static std::pair<int, int> CenterWindow(int aWindowWidth, int aWindowHeight);
	static void glfwErrorCallback(int aError, const char* aDescription);
};

}

#endif
