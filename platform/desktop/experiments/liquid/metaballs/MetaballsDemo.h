#ifndef _METABALLS_DEMO_H_
#define _METABALLS_DEMO_H_

#include "DrawableGameComponent.h"
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/rendering/primitives/square.h>
#include <elements/utils/std/pointer.h>
#include "Game.h"

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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<eps::rendering::texture> mTexture;
	eps::utils::unique<eps::rendering::primitive::square> mSquare;

	GLuint mColorTexture;
};
}

#endif
