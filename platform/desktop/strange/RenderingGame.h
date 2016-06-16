#ifndef _RENDERING_GAME_H_
#define _RENDERING_GAME_H_

#include "Game.h"
#ifndef _MSC_VER
#include "desktop_asset_reader.h"
#include "Camera.h"
#include "StrangeDemo.h"
#endif
#include <glm/glm.hpp>
#include <memory>


namespace Library
{
class Camera;
}

namespace Rendering
{
class StrangeDemo;
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
	std::unique_ptr<Library::Camera> mCamera;
	std::unique_ptr<StrangeDemo> mStrangeDemo;

private:
	static const glm::vec4 sBackgroundColor;
};
}

#endif