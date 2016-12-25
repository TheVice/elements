#ifndef _RECONSTRUCT_DEMO_H_
#define _RECONSTRUCT_DEMO_H_

#include "ReconstructSettings.h"
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
class ReconstructEffect;
class ReconstructUi;
class ReconstructDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(ReconstructDemo, DrawableGameComponent)

public:
	ReconstructDemo(Library::Game& aGame);
	~ReconstructDemo();

public:
	ReconstructDemo() = delete;
	ReconstructDemo(const ReconstructDemo& aRhs) = delete;
	ReconstructDemo& operator = (const ReconstructDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mReconstructProgram;
	eps::utils::unique<ReconstructEffect> mReconstructEffect;
	eps::utils::unique<eps::rendering::texture> u_map_light;
	eps::utils::unique<eps::rendering::texture> u_map_diffuse;
	eps::utils::unique<eps::rendering::texture> u_map_specular;
	eps::utils::optional<ReconstructSettings> mReconstructSettings;
	ReconstructUi* mReconstructUi;
};
}

#endif
