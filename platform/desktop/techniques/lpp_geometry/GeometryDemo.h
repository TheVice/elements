#ifndef _GEOMETRY_DEMO_H_
#define _GEOMETRY_DEMO_H_

#include "GeometrySettings.h"
#include <DrawableGameComponent.h>
#include <elements/utils/std/pointer.h>
#include <elements/utils/std/optional.h>

namespace eps
{
namespace rendering
{
class program;
class texture;
}
}

namespace Rendering
{
class GeometryEffect;
class GeometryUi;
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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<GeometryEffect> mGeometryEffect;
	eps::utils::unique<eps::rendering::texture> mMapNormalTexture;
	eps::utils::optional<GeometrySettings> mGeometrySettings;
	GeometryUi* mGeometryUi;
};
}

#endif
