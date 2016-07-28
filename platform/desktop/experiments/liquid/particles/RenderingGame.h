#ifndef _RENDERING_GAME_H_
#define _RENDERING_GAME_H_

#include "Game.h"
#include "DrawableGameComponent.h"
#include <glm/glm.hpp>
#include <memory>

namespace Rendering
{
class RenderingGame : public Library::Game
{
public:
	RenderingGame(const TCHAR* aWindowTitle);

	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

protected:
	virtual void Shutdown() override;

private:
	void OnKey(int aKey, int aScancode, int aAction, int aMods);

	KeyboardHandler mKeyboardHandler;
	std::unique_ptr<Library::DrawableGameComponent> mGameComponent;

private:
	static const glm::vec4 sBackgroundColor;
};

class RenderingGame2 : public Library::Game
{
public:
	RenderingGame2(const TCHAR* aWindowTitle, int aX, int aY);

	virtual void Run() override;
	virtual void Initialize() override;

protected:
	virtual void InitializeOpenGL() override;

private:
	int mX;
	int mY;

	std::unique_ptr<Library::DrawableGameComponent> mGameComponent;

private:
	static Game* sInternalInstance2;
};

}

#endif
