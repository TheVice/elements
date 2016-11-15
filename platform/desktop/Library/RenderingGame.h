#ifndef _RENDERING_GAME_H_
#define _RENDERING_GAME_H_

#include "Game.h"
#include "DrawableGameComponent.h"
#include <elements/utils/std/pointer.h>
#include <vector>

namespace Library
{
class RenderingGame : public Library::Game
{
public:
	RenderingGame(const std::string& aWindowTitle,
				  GLuint aScreenWidth = Game::sDefaultScreenWidth,
				  GLuint aScreenHeight = Game::sDefaultScreenHeight);

	virtual bool Initialize() override;
	virtual void Draw() override;

	template<typename T, typename... Args>
	void addComponent(Args&& ... args)
	{
		mGameComponents.push_back(eps::utils::make_unique<T>(*this, (args)...));
	}

protected:
	virtual void Shutdown() override;

private:
	void OnKey(int aKey, int aScancode, int aAction, int aMods);

private:
	KeyboardHandler mKeyboardHandler;
	std::vector<eps::utils::unique<GameComponent>> mGameComponents;
};
}

#endif