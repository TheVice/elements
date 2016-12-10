#ifndef _PROJECTOR_DEMO_H_
#define _PROJECTOR_DEMO_H_

#include "ProjectorSettings.h"
#include <DrawableGameComponent.h>
#include <elements/utils/std/pointer.h>
#include <elements/utils/std/optional.h>
#include <elements/rendering/core/buffer.h>

namespace Library
{
class ProjectorEffect;
}

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
class ProjectorEffect;
class ProjectorUi;
class ProjectorDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(ProjectorDemo, DrawableGameComponent)

public:
	ProjectorDemo(Library::Game& aGame);
	~ProjectorDemo();

public:
	ProjectorDemo() = delete;
	ProjectorDemo(const ProjectorDemo& aRhs) = delete;
	ProjectorDemo& operator = (const ProjectorDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mProgram;
	eps::utils::unique<ProjectorEffect> mProjectorEffect;
	eps::utils::unique<eps::rendering::texture> mMapProjectiveTexture;
	GLuint mMapProjective;
	eps::utils::optional<ProjectorSettings> mProjectorSettings;
	ProjectorUi* mProjectorUi;
};
}

#endif
