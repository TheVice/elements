
#include "RenderingGame.h"
#include "asset_fs.h"
#include "assets/assets_storage.h"
#include "preferences.h"
#include "metrics.h"
#ifndef WIN32
#include "OGLES2HelloAPI_LinuxX11.h"
#endif

namespace Library
{
RenderingGame::RenderingGame(const std::string& aWindowTitle, GLuint aScreenWidth, GLuint aScreenHeight) :
	Game(aWindowTitle, aScreenWidth, aScreenHeight),
	mKeyboardHandler(nullptr),
	mGameComponents()
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
#ifndef WIN32
	mGameComponents.insert(mGameComponents.begin(), eps::utils::make_unique<OGLES2HelloAPI_LinuxX11>(*this, GetWindowHandle()));
#endif

	for (const auto& component : mGameComponents)
	{
		mComponents.push_back(component.get());
	}

	return Game::Initialize();
}

void RenderingGame::Draw()
{
	Game::Draw();
	//glfwSwapBuffers(mWindow);
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
