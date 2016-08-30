#ifndef _RENDERING_GAME_H_
#define _RENDERING_GAME_H_

#include "Game.h"
#include "SquareColorDemo.h"
#include <glm/glm.hpp>
#include <memory>

namespace Rendering
{
class SquareColorDemo;
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
	std::unique_ptr<SquareColorDemo> mSquareColorDemo;

private:
	static const glm::vec4 sBackgroundColor;
};
}

#endif