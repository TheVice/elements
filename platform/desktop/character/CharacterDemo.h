#ifndef _CHARACTER_DEMO_H_
#define _CHARACTER_DEMO_H_

#include "DrawableGameComponent.h"
#include "character_renderer.h"
#include "../renderer_factory.h"
#include "Game.h"

namespace Rendering
{
class CharacterDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(CharacterDemo, DrawableGameComponent)

public:
	CharacterDemo(Library::Game& aGame);
	~CharacterDemo();

public:
	CharacterDemo() = delete;
	CharacterDemo(const CharacterDemo& aRhs) = delete;
	CharacterDemo& operator = (const CharacterDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void OnKey(int aKey, int aScancode, int aAction, int aMods);

private:
	int mRenderId;
	using RendererFactory = renderer_factory<character_renderer>;
	eps::utils::unique<RendererFactory> mRendererFactory;
	eps::timing::framerate rate_;
	Library::Game::KeyboardHandler mKeyboardHandler;

private:
	static const std::string sModels[];
};
}

#endif
