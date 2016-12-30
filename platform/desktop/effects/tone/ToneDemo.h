#ifndef _TONE_DEMO_H_
#define _TONE_DEMO_H_

#include "ToneSettings.h"
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
class ToneEffect;
class ToneUi;
class ToneDemo : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(ToneDemo, DrawableGameComponent)

public:
	ToneDemo(Library::Game& aGame);
	~ToneDemo();

public:
	ToneDemo() = delete;
	ToneDemo(const ToneDemo& aRhs) = delete;
	ToneDemo& operator = (const ToneDemo& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	eps::utils::unique<eps::rendering::program> mToneProgram;
	eps::utils::unique<ToneEffect> mToneEffect;
	eps::utils::unique<eps::rendering::texture> u_source_1;
	eps::utils::unique<eps::rendering::texture> u_source_2;
	eps::utils::optional<ToneSettings> mToneSettings;
	ToneUi* mToneUi;
};
}

#endif
