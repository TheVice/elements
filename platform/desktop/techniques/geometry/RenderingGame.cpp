
#include "RenderingGame.h"
#include "GeometryDemo.h"
#include "CustomUi.h"
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
	mDrawableGameComponent(nullptr),
	mUiComponent(nullptr)
{
}

void RenderingGame::Initialize()
{
	mKeyboardHandler = std::bind(&RenderingGame::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	AddKeyboardHandler(mKeyboardHandler);
	//
	eps::assets_storage::instance().mount<Desktop::asset_fs>("");
	eps::preferences::init<Desktop::preferences>();
	eps::metrics::init<Desktop::metrics>(1.0f);
	//
	mUiComponent = std::make_unique<CustomUi>(*this, "assets/settings/techniques/geometry_ui.xml");
	mComponents.push_back(mUiComponent.get());
	mServices.AddService(Rendering::CustomUi::TypeIdClass(), mUiComponent.get());
	//
	mDrawableGameComponent = std::make_unique<GeometryDemo>(*this);
	mComponents.push_back(mDrawableGameComponent.get());
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
