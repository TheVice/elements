
#include "RenderingGame.h"
#include "ParticlesDemo.h"
#include "SettingsWindow.h"
#include "asset_fs.h"
#include "preferences.h"
#include "metrics.h"
#include "assets/assets_storage.h"
#include <glm/gtc/constants.hpp>

namespace Rendering
{
RenderingGame::RenderingGame(const TCHAR* aWindowTitle) :
	Game(aWindowTitle),
	mKeyboardHandler(nullptr),
	mGameComponent(nullptr)
{
}

void RenderingGame::Initialize()
{
	mKeyboardHandler = std::bind(&RenderingGame::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	AddKeyboardHandler(mKeyboardHandler);
	//
	eps::assets_storage::instance().mount<asset_fs>("");
	//
	eps::preferences::init<preferences>();
	//
	eps::metrics::init<metrics>(1.0f);
	//
	mGameComponent = std::make_unique<ParticlesDemo>(*this);
	mComponents.push_back(mGameComponent.get());
	//
	Game::Initialize();
}

void RenderingGame::Draw(const Library::GameTime& aGameTime)
{
	static const GLfloat one = glm::one<GLfloat>();
	//
	glClearBufferfv(GL_COLOR, 0, &sBackgroundColor[0]);
	glClearBufferfv(GL_DEPTH, 0, &one);
	//
	Game::Draw(aGameTime);
	glfwSwapBuffers(mWindow);
}

void RenderingGame::Shutdown()
{
	RemoveKeyboardHandler(mKeyboardHandler);
	Game::Shutdown();
}

void RenderingGame::OnKey(int aKey, int aScancode, int aAction, int aMods)
{
	(void)aScancode;
	(void)aMods;

	if (aKey == GLFW_KEY_ESCAPE && aAction == GLFW_PRESS)
	{
		Exit();
	}
}

const glm::vec4 RenderingGame::sBackgroundColor = { 0.392f, 0.584f, 0.929f, 1.0f };

RenderingGame2::RenderingGame2(const TCHAR* aWindowTitle, int aX, int aY) :
	Game(aWindowTitle),
	mX(aX),
	mY(aY),
	mGameComponent(nullptr)
{
}

void RenderingGame2::Run()
{
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

	Shutdown();
}

void RenderingGame2::Initialize()
{
	eps::assets_storage::instance().mount<asset_fs>("");
	//
	eps::preferences::init<preferences>();
	//
	eps::metrics::init<metrics>(1.0f);
	//
	mGameComponent = std::make_unique<SettingsWindow>(*this);
	mComponents.push_back(mGameComponent.get());
	//
	glfwSetWindowPos(mWindow, mX, mY);
	//
	Game::Initialize();
}

void RenderingGame2::InitializeOpenGL()
{
	glfwMakeContextCurrent(mWindow);
	GLenum ret = glewInit();

	if (GLEW_OK != ret)
	{
		const GLubyte* resultStringPointer = glewGetErrorString(ret);
		std::ostringstream glewErrors;
		glewErrors << resultStringPointer << std::endl;
		glewErrors << "glewInit() failed" << std::endl;
		throw std::runtime_error(glewErrors.str());
	}
}

}
