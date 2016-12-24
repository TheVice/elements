
#include "BlurDemo.h"
#include "BlurEffect.h"
#include "BlurUi.h"
#include <TextureLoader.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/core/texture_maker.h>
#include <elements/rendering/core/texture_policy.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/assets/asset_texture.h>
#include <elements/assets/assets_storage.h>
#include <elements/utils/std/enum.h>
#include <elements/utils/std/product.h>
#include <Game.h>
#include <array>

namespace Rendering
{
RTTI_DEFINITIONS(BlurDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_source = 0,
	u_offset = 1
};

BlurDemo::BlurDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mBlurProgram(nullptr),
	mBlurEffect(nullptr),
	u_source(nullptr),
	mBlurSettings(),
	mBlurUi(nullptr)
{
}

BlurDemo::~BlurDemo() = default;

bool BlurDemo::Initialize()
{
	// Build the shader program
	mBlurProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/effects/blur.prog";

	if (!eps::rendering::load_program(assetPath, (*mBlurProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/effects/blur.xml";
	mBlurSettings = eps::assets_storage::instance().read<BlurSettings>(assetPath);

	if (!mBlurSettings || mBlurSettings->mIsEmpty)
	{
		return false;
	}

	u_source = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mBlurSettings->u_source, (*u_source.get()))
	// Create the effect
	mBlurEffect = eps::utils::make_unique<BlurEffect>(mBlurSettings->mVertices, mBlurSettings->mIndices,
				  eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mBlurUi = static_cast<Rendering::BlurUi*>(mGame->GetServices().GetService(
				  Rendering::BlurUi::TypeIdClass()));
	assert(mBlurUi);
	return mBlurUi != nullptr;
}

void BlurDemo::Update()
{
	if (mBlurUi->IsNeedRestore())
	{
		mBlurUi->Set_u_offset(mBlurSettings->u_offset);
		mBlurUi->SetVertices(mBlurSettings->mVertices);
	}
}

void BlurDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_source->get_product()));
	//
	EPS_STATE_PROGRAM(mBlurProgram->get_product());
	//
	mBlurProgram->uniform_value(eps::utils::to_int(program_enum::u_offset), mBlurUi->Get_u_offset());
	//
	mBlurEffect->construct(mBlurUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mBlurEffect->render(*mBlurProgram.get(), attributes, mBlurSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
