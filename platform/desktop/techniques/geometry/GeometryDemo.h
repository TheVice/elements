#ifndef _GEOMETRY_DEMO_H_
#define _GEOMETRY_DEMO_H_

#include "DrawableGameComponent.h"
#include "SettingsReader.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "rendering/core/texture_policy.h"
#include "rendering/primitives/square.h"
#include <memory>

namespace Rendering
{
class GeometryDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(GeometryDemo, DrawableGameComponent)

public:
	GeometryDemo(Library::Game& aGame);
	~GeometryDemo();

public:
	GeometryDemo() = delete;
	GeometryDemo(const GeometryDemo& aRhs) = delete;
	GeometryDemo& operator = (const GeometryDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	eps::rendering::texture mTexture;
	eps::rendering::primitive::square mSquare;
	std::unique_ptr<SettingsReader> mSettings;
};
}

#endif
