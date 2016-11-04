
#include "RenderingGame.h"
#include "asset_fs.h"
#include "assets/assets_storage.h"
#include "preferences.h"
#include "metrics.h"

namespace Library
{
RenderingGame::RenderingGame(const std::string& aWindowTitle, GLuint aScreenWidth, GLuint aScreenHeight) :
	Game(aWindowTitle, aScreenWidth, aScreenHeight),
	mKeyboardHandler(nullptr),
	mDrawableGameComponents()
{
}

bool RenderingGame::Initialize()
{
	mKeyboardHandler = std::bind(&RenderingGame::OnKey, this,
								 std::placeholders::_1, std::placeholders::_2,
								 std::placeholders::_3, std::placeholders::_4);
	AddKeyboardHandler(mKeyboardHandler);
	//
	eps::assets_storage::instance().mount<asset_fs>("assets", "assets");
	eps::preferences::init<preferences>();
	eps::metrics::init<metrics>(GetDPI());

	for (const auto& component : mDrawableGameComponents)
	{
		mComponents.push_back(component.get());
	}

	return Game::Initialize();
}

void RenderingGame::Draw()
{
	Game::Draw();
	glfwSwapBuffers(mWindow);
}

void RenderingGame::Shutdown()
{
	mComponents.clear();
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
