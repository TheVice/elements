#ifndef _MODEL_DEMO_H_
#define _MODEL_DEMO_H_

#include "ModelSettings.h"
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
class ModelEffect;
class ModelUi;
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
	eps::utils::unique<ModelEffect> mModelEffect;
	eps::utils::unique<eps::rendering::texture> mDiffuseTexture;
	eps::utils::unique<eps::rendering::texture> mSpecularTexture;
	eps::utils::unique<eps::rendering::texture> mNormalTexture;
	eps::utils::optional<ModelSettings> mModelSettings;
	ModelUi* mModelUi;
};
}

#endif
