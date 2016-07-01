#ifndef _GAME_H_
#define _GAME_H_

#include "RTTI.h"
#include "GameTime.h"
#include "GameClock.h"
#include "ServiceContainer.h"
#include "../PowerVR_SDK/Beginner/01_HelloAPI/OGLES2/OGLES2HelloAPI_LinuxX11.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <functional>
#include <vector>
#include <sstream>
#include <memory>
#ifndef WIN32
#include <X11/Xlib.h>
#define TCHAR char
#define TEXT(A) A
#endif

namespace Library
{
class GameComponent;

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
	const TCHAR* GetWindowTitle() const;

	GLuint GetScreenWidth() const;
	GLuint GetScreenHeight() const;

	bool IsDebthStencilBufferEnabled() const;
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

	GLshort GetVersionOfGLSL() const;

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
	std::unique_ptr<OGLES2HelloAPI_LinuxX11> mOGLES2HelloAPI_LinuxX11;

	GLuint mScreenWidth;
	GLuint mScreenHeight;
	bool mIsFullScreen;

	GLint mMajorVersion;
	GLint mMinorVersion;
	GLshort mVersionOfGLSL;

	bool mIsDepthStencilBufferEnabled;

	bool mWindowShouldClose;

	GameClock mGameClock;
	GameTime mGameTime;

	std::vector<GameComponent*> mComponents;
	ServiceContainer mServices;

	std::map<KeyboardHandler*, KeyboardHandler> mKeyboardHandlers;

private:
	static Game* sInternalInstance;
	static std::ostringstream sGlfwErrors;

	static GLshort GetVersionOfGLSL_();
	static void glfwErrorCallback(int aError, const char* aDescription);
};

}

#endif
