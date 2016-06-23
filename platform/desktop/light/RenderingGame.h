#ifndef _RENDERING_GAME_H_
#define _RENDERING_GAME_H_

#include "Game.h"
#if !defined(_MSC_VER) || defined(__clang__)
#include "LightDemo.h"
#endif
#include <glm/glm.hpp>
#include <memory>

namespace Rendering
{
class LightDemo;
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
	std::unique_ptr<LightDemo> mLightDemo;

private:
	static const glm::vec4 sBackgroundColor;
};
}

#endif
