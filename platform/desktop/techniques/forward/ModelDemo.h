#ifndef _MODEL_DEMO_H_
#define _MODEL_DEMO_H_

#include "ModelEffect.h"
#include "SettingsReader.h"
#include <DrawableGameComponent.h>
#include <elements/rendering/core/buffer.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/utils/std/optional.h>

namespace Rendering
{
class CustomUi;
class ModelDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(ModelDemo, DrawableGameComponent)

public:
	ModelDemo(Library::Game& aGame);
	~ModelDemo();

public:
	ModelDemo() = delete;
	ModelDemo(const ModelDemo& aRhs) = delete;
	ModelDemo& operator = (const ModelDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<Library::ModelEffect> mModelEffect;

	GLuint mVertexArrayObject;
	eps::utils::unique<eps::rendering::vertices> mVertexBuffer;
	eps::utils::unique<eps::rendering::indices> mIndexBuffer;

	GLuint mDiffuseTexture;
	GLuint mSpecularTexture;
	GLuint mNormalTexture;

	eps::utils::unique<eps::rendering::texture> mDiffuse;
	eps::utils::unique<eps::rendering::texture> mSpecular;
	eps::utils::unique<eps::rendering::texture> mNormal;

	eps::utils::optional<SettingsReader> mSettings;
	CustomUi* mUi;
};
}

#endif
