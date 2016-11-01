
#include "Game.h"
#include "DrawableGameComponent.h"
#include <GLFW/glfw3native.h>
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

Game::Game(const TCHAR* aWindowTitle) :
	mWindowTitle(aWindowTitle),
	mOGLES2HelloAPI_LinuxX11(nullptr),
	mWindow(nullptr),
	mScreenWidth(sDefaultScreenWidth),
	mScreenHeight(sDefaultScreenHeight),
	mIsFullScreen(false),
	mGameTime(),
	mComponents(),
	mKeyboardHandlers()
{
}

Game::~Game()
{
	mComponents.clear();
#ifndef NDEBUG
	const auto glfwErrors = sGlfwErrors.str();

	if (!glfwErrors.empty())
	{
#ifdef _MSC_VER
		OutputDebugStringA(glfwErrors.c_str());
#else
		std::cerr << glfwErrors.c_str() << std::endl;
#endif
	}

#endif
}
#ifndef WIN32
Window Game::GetWindowHandle() const
{
	return glfwGetX11Window(mWindow);
}
#else
HWND Game::GetWindowHandle() const
{
	return glfwGetWin32Window(mWindow);
}
#endif
GLFWwindow* Game::GetWindow() const
{
	return mWindow;
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

GLint Game::GetDPI() const
{
#ifdef WIN32
	const auto windowHandle = GetWindowHandle();
	const auto hdc = GetDC(windowHandle);
	//
	const auto dpi = GetDeviceCaps(hdc, LOGPIXELSY);
	//
	ReleaseDC(windowHandle, hdc);
	//
	return dpi;
#else
	return 96;
#endif
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

void Game::Run()
{
	assert(!sInternalInstance);
	sInternalInstance = this;
	//
	InitializeWindow();
	InitializeOpenGL();
	Initialize();

	while (!glfwWindowShouldClose(mWindow))
	{
		Update(mGameTime);
		Draw(mGameTime);
		//
		glfwPollEvents();
	}

	Release();
	Shutdown();
}

void Game::Exit()
{
	glfwSetWindowShouldClose(mWindow, GL_TRUE);
}

void Game::Initialize()
{
	for (const auto& component : mComponents)
	{
		component->Initialize();
	}
}

void Game::Update(const GameTime& aGameTime)
{
	for (const auto& component : mComponents)
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
	for (const auto& component : mComponents)
	{
		const auto drawableGameComponent = component->As<DrawableGameComponent>();

		if (drawableGameComponent && drawableGameComponent->IsVisible())
		{
			drawableGameComponent->Draw(aGameTime);
		}
	}
}

void Game::Release()
{
	for (const auto& component : mComponents)
	{
		component->Release();
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

void Game::InitializeWindow()
{
#ifndef NDEBUG
	glfwSetErrorCallback(glfwErrorCallback);
#endif

	if (!glfwInit())
	{
		sGlfwErrors << ("glfwInit() failed") << std::endl;
		throw std::runtime_error(sGlfwErrors.str());
	}

	GLFWmonitor* monitor = (mIsFullScreen ? glfwGetPrimaryMonitor() : nullptr);
#ifdef UNICODE
	const auto length = mWindowTitle.length();
	std::string windowTitle(length + 1, '\0');
	//
	mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, windowTitle.c_str(), monitor, nullptr);
#else
	mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, mWindowTitle.c_str(), monitor, nullptr);
#endif

	if (!mWindow)
	{
		Shutdown();
		sGlfwErrors << ("glfwCreateWindow() failed") << std::endl;
		throw std::runtime_error(sGlfwErrors.str());
	}

	if (!mIsFullScreen)
	{
		auto center = CenterWindow(mScreenWidth, mScreenHeight);
#ifndef WIN32
		glfwSetWindowPos(mWindow, std::get<0>(center), std::get<1>(center));
#else
		glfwSetWindowPos(mWindow, center.x, center.y);
#endif
	}
}

void Game::InitializeOpenGL()
{
	glfwMakeContextCurrent(mWindow);
	mOGLES2HelloAPI_LinuxX11 = std::make_unique<OGLES2HelloAPI_LinuxX11>(GetWindowHandle());

	if (!mOGLES2HelloAPI_LinuxX11->Initialize())
	{
		throw std::runtime_error("mOGLES2HelloAPI_LinuxX11->Initialize() failed");
	}

	glfwSetKeyCallback(mWindow, Game::OnKey);
}

void Game::Shutdown()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Game::OnKey(GLFWwindow* aWindow, int aKey, int aScancode, int aAction, int aMods)
{
	(void)aWindow;

	for (const auto& handler : sInternalInstance->mKeyboardHandlers)
	{
		handler.second(aKey, aScancode, aAction, aMods);
	}
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
#ifndef NDEBUG
void Game::glfwErrorCallback(int aError, const char* aDescription)
{
	sGlfwErrors << aDescription << " (Error #" << aError << ")" << std::endl;
}
#endif
}
