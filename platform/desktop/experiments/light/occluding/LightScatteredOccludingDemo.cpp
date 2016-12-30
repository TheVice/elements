
#include "LightScatteredOccludingDemo.h"
#include "LightScatteredOccludingEffect.h"
#include "LightScatteredOccludingUi.h"
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
RTTI_DEFINITIONS(LightScatteredOccludingDemo)

enum class program_enum : short
{
	// attributes
	a_product_uv = 0,
	// uniforms
	u_positions = 0,
	u_size = 1
};

LightScatteredOccludingDemo::LightScatteredOccludingDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mLightScatteredOccludingProgram(nullptr),
	mLightScatteredOccludingEffect(nullptr),
	u_positions(nullptr),
	mLightScatteredOccludingSettings(),
	mLightScatteredOccludingUi(nullptr)
{
}

LightScatteredOccludingDemo::~LightScatteredOccludingDemo() = default;

bool LightScatteredOccludingDemo::Initialize()
{
	// Build the shader program
	mLightScatteredOccludingProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/light/occluding.prog";

	if (!eps::rendering::load_program(assetPath, (*mLightScatteredOccludingProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/light/occluding.xml";
	mLightScatteredOccludingSettings = eps::assets_storage::instance().read<LightScatteredOccludingSettings>
									   (assetPath);

	if (!mLightScatteredOccludingSettings || mLightScatteredOccludingSettings->mIsEmpty)
	{
		return false;
	}

	u_positions = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mLightScatteredOccludingSettings->u_positions, (*u_positions.get()))
	// Create the effect
	mLightScatteredOccludingEffect = eps::utils::make_unique<LightScatteredOccludingEffect>
									 (mLightScatteredOccludingSettings->mVertices, mLightScatteredOccludingSettings->mIndices,
									  eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mLightScatteredOccludingUi = static_cast<Rendering::LightScatteredOccludingUi*>
								 (mGame->GetServices().GetService(
									  Rendering::LightScatteredOccludingUi::TypeIdClass()));
	assert(mLightScatteredOccludingUi);
	return mLightScatteredOccludingUi != nullptr;
}

void LightScatteredOccludingDemo::Update()
{
	if (mLightScatteredOccludingUi->IsNeedRestore())
	{
		mLightScatteredOccludingUi->Set_u_size(mLightScatteredOccludingSettings->u_size);
		//
		mLightScatteredOccludingUi->SetVertices(mLightScatteredOccludingSettings->mVertices);
	}
}

void LightScatteredOccludingDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_positions->get_product()));
	//
	EPS_STATE_PROGRAM(mLightScatteredOccludingProgram->get_product());
	//
	mLightScatteredOccludingProgram->uniform_value(eps::utils::to_int(program_enum::u_size),
			mLightScatteredOccludingUi->Get_u_size());
	//
	mLightScatteredOccludingEffect->construct(mLightScatteredOccludingUi->GetVertices());
	mLightScatteredOccludingEffect->render(*mLightScatteredOccludingProgram.get(),
										   eps::utils::to_int(program_enum::a_product_uv), mLightScatteredOccludingSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

