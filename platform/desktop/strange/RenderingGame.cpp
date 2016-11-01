
#include "RenderingGame.h"
#include "asset_fs.h"
#include "assets/assets_storage.h"
#include "preferences.h"
#include "metrics.h"
#include "StrangeDemo.h"

namespace Rendering
{
RenderingGame::RenderingGame(const TCHAR* aWindowTitle) :
	Game(aWindowTitle),
	mKeyboardHandler(nullptr),
	mDrawableGameComponent(nullptr)
{
}

void RenderingGame::Initialize()
{
	mKeyboardHandler = std::bind(&RenderingGame::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	AddKeyboardHandler(mKeyboardHandler);
	//
	eps::assets_storage::instance().mount<asset_fs>("assets", "assets");
	eps::preferences::init<preferences>();
	eps::metrics::init<metrics>(GetDPI());
	//
	mDrawableGameComponent = std::make_unique<StrangeDemo>(*this);
	mComponents.push_back(mDrawableGameComponent.get());
	//
	Game::Initialize();
}

void RenderingGame::Draw(const Library::GameTime& aGameTime)
{
	Game::Draw(aGameTime);
	//	glfwSwapBuffers(mWindow);
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

}
