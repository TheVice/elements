#ifndef _GEOMETRY_DEMO_H_
#define _GEOMETRY_DEMO_H_

#include "DrawableGameComponent.h"
#include "GeometryEffect.h"
#include "SettingsReader.h"
#include <elements/rendering/core/buffer.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/utils/std/optional.h>
#include "Game.h"

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
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgramEncodeNormal;
	eps::utils::unique<eps::rendering::program> mProgramNonEncodeNormal;
	eps::utils::unique<Library::GeometryEffect> mGeometryEffect;
	GLuint mVertexArrayObject;
	eps::utils::unique<eps::rendering::vertices> mVertexBuffer;
	eps::utils::unique<eps::rendering::indices> mIndexBuffer;
	GLuint mColorTexture;

	eps::utils::unique<eps::rendering::texture> mTexture;
	eps::utils::optional<SettingsReader> mSettings;

	CustomUi* mUi;

	bool mIsNonEncodeProgramLoaded;
};
}

#endif
