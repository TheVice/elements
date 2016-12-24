#ifndef _METABALL_DEMO_H_
#define _METABALL_DEMO_H_

#include "MetaballSettings.h"
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
class MetaballEffect;
class MetaballUi;
class MetaballDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(MetaballDemo, DrawableGameComponent)

public:
	MetaballDemo(Library::Game& aGame);
	~MetaballDemo();

public:
	MetaballDemo() = delete;
	MetaballDemo(const MetaballDemo& aRhs) = delete;
	MetaballDemo& operator = (const MetaballDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mMetaballProgram;
	eps::utils::unique<MetaballEffect> mMetaballEffect;
	eps::utils::unique<eps::rendering::texture> u_source;
	eps::utils::optional<MetaballSettings> mMetaballSettings;
	MetaballUi* mMetaballUi;
};
}

#endif
