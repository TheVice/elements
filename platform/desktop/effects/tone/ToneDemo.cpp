
#include "ToneDemo.h"
#include "ToneEffect.h"
#include "ToneUi.h"
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
RTTI_DEFINITIONS(ToneDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_source_1 = 0,
	u_source_2 = 1,
	u_exposure = 2,
	u_gamma = 3
};

ToneDemo::ToneDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mToneProgram(nullptr),
	mToneEffect(nullptr),
	u_source_1(nullptr),
	u_source_2(nullptr),
	mToneSettings(),
	mToneUi(nullptr)
{
}

ToneDemo::~ToneDemo() = default;

bool ToneDemo::Initialize()
{
	// Build the shader program
	mToneProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/effects/tone.prog";

	if (!eps::rendering::load_program(assetPath, (*mToneProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/effects/tone.xml";
	mToneSettings = eps::assets_storage::instance().read<ToneSettings>(assetPath);

	if (!mToneSettings || mToneSettings->mIsEmpty)
	{
		return false;
	}

	u_source_1 = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mToneSettings->u_source_1, (*u_source_1.get()))
	u_source_2 = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mToneSettings->u_source_2, (*u_source_2.get()))
	// Create the effect
	mToneEffect = eps::utils::make_unique<ToneEffect>(mToneSettings->mVertices, mToneSettings->mIndices,
				  eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mToneUi = static_cast<Rendering::ToneUi*>(mGame->GetServices().GetService(
				  Rendering::ToneUi::TypeIdClass()));
	assert(mToneUi);
	return mToneUi != nullptr;
}

void ToneDemo::Update()
{
	if (mToneUi->IsNeedRestore())
	{
		mToneUi->Set_u_exposure(mToneSettings->u_exposure);
		mToneUi->Set_u_gamma(mToneSettings->u_gamma);
		//
		mToneUi->SetVertices(mToneSettings->mVertices);
	}
}

void ToneDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_source_1->get_product()));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_source_2->get_product()));
	//
	EPS_STATE_PROGRAM(mToneProgram->get_product());
	//
	mToneProgram->uniform_value(eps::utils::to_int(program_enum::u_exposure), mToneUi->Get_u_exposure());
	mToneProgram->uniform_value(eps::utils::to_int(program_enum::u_gamma), mToneUi->Get_u_gamma());
	//
	mToneEffect->construct(mToneUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mToneEffect->render(*mToneProgram.get(), attributes, mToneSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

