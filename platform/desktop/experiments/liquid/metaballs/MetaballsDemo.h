#ifndef _METABALLS_DEMO_H_
#define _METABALLS_DEMO_H_

#include "DrawableGameComponent.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "rendering/primitives/square.h"

namespace Rendering
{
class MetaballsDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(MetaballsDemo, DrawableGameComponent)

public:
	MetaballsDemo(Library::Game& aGame);
	~MetaballsDemo();

public:
	MetaballsDemo() = delete;
	MetaballsDemo(const MetaballsDemo& aRhs) = delete;
	MetaballsDemo& operator = (const MetaballsDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::primitive::square mSquare;
	eps::rendering::texture mTexture;
};
}

#endif
