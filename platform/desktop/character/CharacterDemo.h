#ifndef _CHARACTER_DEMO_H_
#define _CHARACTER_DEMO_H_

#include "DrawableGameComponent.h"
#include "character_renderer.h"
#include "../renderer_factory.h"

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
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	int mRenderId;
	using character_renderer_factory = renderer_factory<character_renderer>;
	std::unique_ptr<character_renderer_factory> mCharacterRendererFactory;
	eps::timing::framerate rate_;

private:
	static const std::string sModel;
};
}

#endif
