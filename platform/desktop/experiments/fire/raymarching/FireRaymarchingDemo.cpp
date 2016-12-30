
#include "FireRaymarchingDemo.h"
#include "FireRaymarchingEffect.h"
#include "FireRaymarchingUi.h"
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
RTTI_DEFINITIONS(FireRaymarchingDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_noise = 0,
	u_dt = 1,
	u_intensity = 2,
	u_covering = 3,
	u_texel = 4,
	u_color_hot = 5,
	u_color_cold = 6
};

FireRaymarchingDemo::FireRaymarchingDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mFireRaymarchingProgram(nullptr),
	mFireRaymarchingEffect(nullptr),
	u_noise(nullptr),
	mFireRaymarchingSettings(),
	mFireRaymarchingUi(nullptr)
{
}

FireRaymarchingDemo::~FireRaymarchingDemo() = default;

bool FireRaymarchingDemo::Initialize()
{
	// Build the shader program
	mFireRaymarchingProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/fire/raymarching.prog";

	if (!eps::rendering::load_program(assetPath, (*mFireRaymarchingProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/fire/raymarching.xml";
	mFireRaymarchingSettings = eps::assets_storage::instance().read<FireRaymarchingSettings>(assetPath);

	if (!mFireRaymarchingSettings || mFireRaymarchingSettings->mIsEmpty)
	{
		return false;
	}

	u_noise = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mFireRaymarchingSettings->u_noise, (*u_noise.get()))
	// Create the effect
	mFireRaymarchingEffect = eps::utils::make_unique<FireRaymarchingEffect>(mFireRaymarchingSettings->mVertices,
							 mFireRaymarchingSettings->mIndices,
							 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mFireRaymarchingUi = static_cast<Rendering::FireRaymarchingUi*>(mGame->GetServices().GetService(
							 Rendering::FireRaymarchingUi::TypeIdClass()));
	assert(mFireRaymarchingUi);
	return mFireRaymarchingUi != nullptr;
}

void FireRaymarchingDemo::Update()
{
	if (mFireRaymarchingUi->IsNeedRestore())
	{
		mFireRaymarchingUi->Set_u_dt(mFireRaymarchingSettings->u_dt);
		mFireRaymarchingUi->Set_u_intensity(mFireRaymarchingSettings->u_intensity);
		mFireRaymarchingUi->Set_u_covering(mFireRaymarchingSettings->u_covering);
		mFireRaymarchingUi->Set_u_texel(mFireRaymarchingSettings->u_texel);
		mFireRaymarchingUi->Set_u_color_hot(mFireRaymarchingSettings->u_color_hot);
		mFireRaymarchingUi->Set_u_color_cold(mFireRaymarchingSettings->u_color_cold);
		//
		mFireRaymarchingUi->SetVertices(mFireRaymarchingSettings->mVertices);
	}
}

void FireRaymarchingDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_noise->get_product()));
	//
	EPS_STATE_PROGRAM(mFireRaymarchingProgram->get_product());
	//
	mFireRaymarchingProgram->uniform_value(eps::utils::to_int(program_enum::u_dt),
										   mFireRaymarchingUi->Get_u_dt());
	mFireRaymarchingProgram->uniform_value(eps::utils::to_int(program_enum::u_intensity),
										   mFireRaymarchingUi->Get_u_intensity());
	mFireRaymarchingProgram->uniform_value(eps::utils::to_int(program_enum::u_covering),
										   mFireRaymarchingUi->Get_u_covering());
	mFireRaymarchingProgram->uniform_value(eps::utils::to_int(program_enum::u_texel),
										   mFireRaymarchingUi->Get_u_texel());
	mFireRaymarchingProgram->uniform_value(eps::utils::to_int(program_enum::u_color_hot),
										   mFireRaymarchingUi->Get_u_color_hot());
	mFireRaymarchingProgram->uniform_value(eps::utils::to_int(program_enum::u_color_cold),
										   mFireRaymarchingUi->Get_u_color_cold());
	//
	mFireRaymarchingEffect->construct(mFireRaymarchingUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mFireRaymarchingEffect->render(*mFireRaymarchingProgram.get(), attributes,
								   mFireRaymarchingSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

