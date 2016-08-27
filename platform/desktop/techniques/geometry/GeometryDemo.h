#ifndef _GEOMETRY_DEMO_H_
#define _GEOMETRY_DEMO_H_

#include "DrawableGameComponent.h"
#include "GeometryEffect.h"
#include "SettingsReader.h"
#include "rendering/core/texture.h"
#include <memory>

namespace Rendering
{
class CustomUi;
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
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	Library::GeometryEffect mGeometryEffect;
	GLuint mVertexArrayObject;
	GLuint mVertexBuffer;
	GLuint mVertexCount;
	GLuint mColorTexture;

	eps::rendering::texture mTexture;
	std::unique_ptr<SettingsReader> mSettings;

	CustomUi* mUi;
};
}

#endif
