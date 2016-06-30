
#include "Game.h"
#include "DrawableGameComponent.h"
#include "Utility.h"
#include <cassert>
#ifndef _MSC_VER
#include <iostream>
#endif

namespace Library
{
RTTI_DEFINITIONS(Game)

const GLuint Game::sDefaultScreenWidth = 800;
const GLuint Game::sDefaultScreenHeight = 600;

Game* Game::sInternalInstance = nullptr;

std::ostringstream Game::sGlfwErrors;

Game::Game(const TCHAR* aWindowTitle)
	: mWindowTitle(aWindowTitle),
	  mOGLES2HelloAPI_LinuxX11(nullptr),
	  mScreenWidth(sDefaultScreenWidth),
	  mScreenHeight(sDefaultScreenHeight),
	  mIsFullScreen(false),
	  mMajorVersion(0),
	  mMinorVersion(0),
	  mVersionOfGLSL(0),
	  mIsDepthStencilBufferEnabled(false),
	  mGameClock(),
	  mGameTime(0.0, 0.0),
	  mComponents(),
	  mServices(),
	  mKeyboardHandlers()
{
}

Game::~Game()
{
	mComponents.clear();
#ifndef NDEBUG
	std::string glfwErrors = sGlfwErrors.str();

	if (glfwErrors.length())
	{
#ifdef _MSC_VER
		OutputDebugStringA(glfwErrors.c_str());
#else
		std::cerr << glfwErrors.c_str() << std::endl;
#endif
	}

#endif
}

const TCHAR* Game::GetWindowTitle() const
{
	return mWindowTitle.c_str();
}

GLuint Game::GetScreenWidth() const
{
	return mScreenWidth;
}

GLuint Game::GetScreenHeight() const
{
	return mScreenHeight;
}

bool Game::IsDebthStencilBufferEnabled() const
{
	return mIsDepthStencilBufferEnabled;
}

GLfloat Game::GetAspectRatio() const
{
	return static_cast<GLfloat>(mScreenWidth) / mScreenHeight;
}

bool Game::IsFullScreen() const
{
	return mIsFullScreen;
}

const std::vector<GameComponent*>& Game::GetComponents() const
{
	return mComponents;
}

const ServiceContainer& Game::GetServices() const
{
	return mServices;
}

void Game::Run()
{
	sInternalInstance = this;
	//
	InitializeWindow();
	InitializeOpenGL();
	Initialize();
	//
	mGameClock.Reset();

	while (1)//!glfwWindowShouldClose(mWindow))
	{
		mGameClock.UpdateGameTime(mGameTime);
		Update(mGameTime);
		Draw(mGameTime);
	}

	Shutdown();
}

void Game::Exit()
{
	//glfwSetWindowShouldClose(mWindow, GL_TRUE);
}

void Game::Initialize()
{
	for (GameComponent* component : mComponents)
	{
		component->Initialize();
	}
}

void Game::Update(const GameTime& aGameTime)
{
	for (GameComponent* component : mComponents)
	{
		if (component->IsEnabled())
		{
			component->Update(aGameTime);
		}
	}

	mOGLES2HelloAPI_LinuxX11->Update();
}

void Game::Draw(const GameTime& aGameTime)
{
	for (GameComponent* component : mComponents)
	{
		DrawableGameComponent* drawableGameComponent = component->As<DrawableGameComponent>();

		if (drawableGameComponent && drawableGameComponent->IsVisible())
		{
			drawableGameComponent->Draw(aGameTime);
		}
	}
}

void Game::AddKeyboardHandler(KeyboardHandler aHandler)
{
	mKeyboardHandlers[&aHandler] = aHandler;
}

void Game::RemoveKeyboardHandler(KeyboardHandler aHandler)
{
	mKeyboardHandlers.erase(&aHandler);
}

GLshort Game::GetVersionOfGLSL() const
{
	return mVersionOfGLSL;
}

GLshort Game::GetVersionOfGLSL_()
{
	const GLubyte* version = glGetString(GL_SHADING_LANGUAGE_VERSION);
	const GLubyte versionParts[] = "0123456789";
	const GLshort count = sizeof(versionParts) / sizeof(*versionParts);
	//
	const GLshort multiply[5] = { 1, 10, 100, 1000, 10000 };
	GLshort version2[5];
	assert(sizeof(multiply) == sizeof(version2));
	//
	GLshort i = 0;
	GLshort k = 0;

	while (version[i] != ' ' && version[i] != '\0')
	{
		for (GLshort j = 0; j < count; ++j)
		{
			if (version[i] == versionParts[j])
			{
				assert(k < static_cast<GLshort>(sizeof(version2) / sizeof(*version2)));
				version2[k++] = j;
				break;
			}
		}

		i++;
	}

	GLshort retVersion = 0;

	for (i = 0; i < k; ++i)
	{
		retVersion += multiply[k - 1 - i] * version2[i];
	}

	return retVersion;
}

void Game::InitializeWindow()
{
}

void Game::InitializeOpenGL()
{
	mOGLES2HelloAPI_LinuxX11 = std::make_unique<OGLES2HelloAPI_LinuxX11>();

	if (!mOGLES2HelloAPI_LinuxX11->Initialize())
	{
		throw std::runtime_error("mOGLES2HelloAPI_LinuxX11->Initialize() failed");
	}

#ifdef DesktopGL
	glGetIntegerv(GL_MAJOR_VERSION, &mMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &mMinorVersion);
#endif
	mVersionOfGLSL = GetVersionOfGLSL_();

	if (mIsDepthStencilBufferEnabled)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}

	glViewport(0, 0, mScreenWidth, mScreenHeight);
}

void Game::Shutdown()
{
//	glfwDestroyWindow(mWindow);
//	glfwTerminate();
}

#ifndef WIN32
std::pair<int, int> Game::CenterWindow(int aWindowWidth, int aWindowHeight)
{
	std::pair<int, int> center = std::make_pair(0, 0);
	Display* display = XOpenDisplay(nullptr);

	if (!display)
	{
		return center;
	}

	int screenNumber = XDefaultScreen(display);
	int screenWidth = XDisplayWidth(display, screenNumber);
	int screenHeight = XDisplayHeight(display, screenNumber);
	XCloseDisplay(display);
	std::get<0>(center) = static_cast<int>(static_cast<GLfloat>(screenWidth - aWindowWidth) / 2);
	std::get<1>(center) = static_cast<int>(static_cast<GLfloat>(screenHeight - aWindowHeight) / 2);
	return center;
}
#else
POINT Game::CenterWindow(int aWindowWidth, int aWindowHeight)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	POINT center = { 0, 0 };
	center.x = static_cast<LONG>(static_cast<GLfloat>(screenWidth - aWindowWidth) / 2);
	center.y = static_cast<LONG>(static_cast<GLfloat>(screenHeight - aWindowHeight) / 2);
	return center;
}
#endif
void Game::glfwErrorCallback(int aError, const char* aDescription)
{
#ifdef NDEBUG
	(void)aError;
	(void)aDescription;
#else
	sGlfwErrors << aDescription << " (Error #" << aError << ")" << std::endl;
#endif
}

}
