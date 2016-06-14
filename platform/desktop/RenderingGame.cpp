
#include "RenderingGame.h"
#ifdef _MSC_VER
#include "Camera.h"
#include "RenderDemo.h"
#endif
#include <glm/gtc/constants.hpp>

namespace Rendering
{
RenderingGame::RenderingGame(const TCHAR* aWindowTitle)
	: Game(aWindowTitle),
	  mKeyboardHandler(nullptr),
	  mCamera(nullptr),
	  mRenderDemo(nullptr)
{
	//mIsDepthStencilBufferEnabled = true;
}

void RenderingGame::Initialize()
{
	mKeyboardHandler = std::bind(&RenderingGame::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	AddKeyboardHandler(mKeyboardHandler);
	//
	mCamera = std::make_unique<Library::Camera>(*this);
	mComponents.push_back(mCamera.get());
	mServices.AddService(Library::Camera::TypeIdClass(), mCamera.get());
	//
	mRenderDemo = std::make_unique<RenderDemo>(*this, *mCamera);
	mComponents.push_back(mRenderDemo.get());
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

}
