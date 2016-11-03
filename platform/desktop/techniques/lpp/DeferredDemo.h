#ifndef _DEFERRED_DEMO_H_
#define _DEFERRED_DEMO_H_

#include "DrawableGameComponent.h"
#include "DeferredEffect.h"
#include "SettingsReader.h"
#include "rendering/core/buffer.h"
#include "rendering/core/program.h"
#include "rendering/core/texture.h"
#include "utils/std/optional.h"

namespace Rendering
{
class CustomUi;
class DeferredDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(DeferredDemo, DrawableGameComponent)

public:
	DeferredDemo(Library::Game& aGame);
	~DeferredDemo();

public:
	DeferredDemo() = delete;
	DeferredDemo(const DeferredDemo& aRhs) = delete;
	DeferredDemo& operator = (const DeferredDemo& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

private:
	eps::rendering::program mProgram;
	Library::DeferredEffect mDeferredEffect;

	GLuint mVertexArrayObject;
	eps::rendering::vertices mVertexBuffer;
	eps::rendering::indices mIndexBuffer;

	GLuint mDiffuseTexture;
	GLuint mSpecularTexture;
	GLuint mNormalTexture;

	eps::rendering::texture mDiffuse;
	eps::rendering::texture mSpecular;
	eps::rendering::texture mNormal;

	eps::utils::optional<SettingsReader> mSettings;
	CustomUi* mUi;
};
}

#endif
