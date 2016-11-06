
#include "Game.h"
#include "DrawableGameComponent.h"
#include <GLFW/glfw3native.h>
#include <cassert>
#include <stdio.h>

namespace Library
{
RTTI_DEFINITIONS(Game)

const GLuint Game::sDefaultScreenWidth = 800;
const GLuint Game::sDefaultScreenHeight = 600;
const GLuint Game::sDefaultDPI = 96;

Game* Game::sInternalInstance = nullptr;

Game::Game(const std::string& aWindowTitle, GLuint aScreenWidth, GLuint aScreenHeight) :
	mWindowTitle(aWindowTitle),
	mScreenWidth(aScreenWidth),
	mScreenHeight(aScreenHeight),
	mIsFullScreen(false),
	mWindow(nullptr),
	mComponents(),
	mKeyboardHandlers()
{
}

Game::~Game()
{
	mComponents.clear();
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

const std::string& Game::GetWindowTitle() const
{
	return mWindowTitle;
}

GLuint Game::GetScreenWidth() const
{
	return mScreenWidth;
}

GLuint Game::GetScreenHeight() const
{
	return mScreenHeight;
}

GLfloat Game::GetAspectRatio() const
{
	return static_cast<GLfloat>(mScreenWidth) / mScreenHeight;
}

GLint Game::GetDPI() const
{
	int widthMM = 0;
	int heightMM = 0;
	const auto monitor = glfwGetPrimaryMonitor();
	glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
	const auto mode = glfwGetVideoMode(monitor);
	const auto dpi = heightMM ? static_cast<GLint>((static_cast<GLfloat>(mode->height) * 25.4f) / heightMM) : 96;
	//
	const std::vector<GLint> dpis = { 96, 120, 144, 192, 240, 288, 384, 480 };
	GLint index = 0;
	GLint minimalDiff = std::abs(dpis[index] - dpi);

	for (size_t i = 0, count = dpis.size(); i < count; ++i)
	{
		GLint diff = std::abs(dpis[i] - dpi);

		if (diff < minimalDiff)
		{
			minimalDiff = diff;
			index = i;
		}
	}

	return dpis[index];
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
	assert(!sInternalInstance);
	sInternalInstance = this;
	InitializeWindow();
	InitializeOpenGL();

	if (Initialize())
	{
		while (!glfwWindowShouldClose(mWindow))
		{
			Update();
			Draw();
			glfwPollEvents();
		}
	}

	Release();
	Shutdown();
}

void Game::Exit()
{
	glfwSetWindowShouldClose(mWindow, GL_TRUE);
}

bool Game::Initialize()
{
	for (const auto& component : mComponents)
	{
		if (!component->Initialize())
		{
			return false;
		}
	}

	return true;
}

void Game::Update()
{
	for (const auto& component : mComponents)
	{
		if (component->IsEnabled())
		{
			component->Update();
		}
	}
}

void Game::Draw()
{
	for (const auto& component : mComponents)
	{
		const auto drawableGameComponent = component->As<DrawableGameComponent>();

		if (drawableGameComponent && drawableGameComponent->IsVisible())
		{
			drawableGameComponent->Draw();
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
	glfwSetErrorCallback(glfwErrorCallback);

	if (!glfwInit())
	{
		throw std::runtime_error("glfwInit() failed");
	}

	mScreenWidth *= static_cast<GLfloat>(GetDPI()) / sDefaultDPI;
	mScreenHeight *= static_cast<GLfloat>(GetDPI()) / sDefaultDPI;
	GLFWmonitor* monitor = (mIsFullScreen ? glfwGetPrimaryMonitor() : nullptr);

	if (!mIsFullScreen)
	{
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, mWindowTitle.c_str(), monitor, nullptr);

	if (!mWindow)
	{
		Shutdown();
		throw std::runtime_error("glfwCreateWindow() failed");
	}

	if (!mIsFullScreen)
	{
		const auto center = CenterWindow(mScreenWidth, mScreenHeight);
		glfwSetWindowPos(mWindow, std::get<0>(center), std::get<1>(center));
	}
}

void Game::InitializeOpenGL()
{
	glfwMakeContextCurrent(mWindow);
	const auto ret = glewInit();

	if (GLEW_OK != ret)
	{
		glfwErrorCallback(ret, reinterpret_cast<const char*>(glewGetErrorString(ret)));
		throw std::runtime_error("glewInit() failed");
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
	assert(sInternalInstance);

	for (const auto& handler : sInternalInstance->mKeyboardHandlers)
	{
		handler.second(aKey, aScancode, aAction, aMods);
	}
}

std::pair<int, int> Game::CenterWindow(int aWindowWidth, int aWindowHeight)
{
	std::pair<int, int> center = std::make_pair(0, 0);
	const auto monitor = glfwGetPrimaryMonitor();
	const auto mode = glfwGetVideoMode(monitor);
	std::get<0>(center) = static_cast<int>(static_cast<float>(mode->width - aWindowWidth) / 2);
	std::get<1>(center) = static_cast<int>(static_cast<float>(mode->height - aWindowHeight) / 2);
	return center;
}

void Game::glfwErrorCallback(int aError, const char* aDescription)
{
	const auto sz = snprintf(nullptr, 0, "%s (Error #%i)\n", aDescription, aError);
	char errorMessage[1 + sz] = "";
	sprintf(errorMessage, "%s (Error #%i)\n", aDescription, aError);
	fprintf(stderr, "%s", errorMessage);
}

}
