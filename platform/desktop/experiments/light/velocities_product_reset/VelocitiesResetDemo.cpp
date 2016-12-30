
#include "VelocitiesResetDemo.h"
#include "VelocitiesResetEffect.h"
#include "VelocitiesResetUi.h"
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
RTTI_DEFINITIONS(VelocitiesResetDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	// uniforms

};

VelocitiesResetDemo::VelocitiesResetDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mVelocitiesResetProgram(nullptr),
	mVelocitiesResetEffect(nullptr),
	mVelocitiesResetSettings(),
	mVelocitiesResetUi(nullptr)
{
}

VelocitiesResetDemo::~VelocitiesResetDemo() = default;

bool VelocitiesResetDemo::Initialize()
{
	// Build the shader program
	mVelocitiesResetProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/light/velocities_product_reset.prog";

	if (!eps::rendering::load_program(assetPath, (*mVelocitiesResetProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/light/velocities_product_reset.xml";
	mVelocitiesResetSettings = eps::assets_storage::instance().read<VelocitiesResetSettings>(assetPath);

	if (!mVelocitiesResetSettings || mVelocitiesResetSettings->mIsEmpty)
	{
		return false;
	}

	// Create the effect
	mVelocitiesResetEffect = eps::utils::make_unique<VelocitiesResetEffect>(mVelocitiesResetSettings->mVertices,
							 mVelocitiesResetSettings->mIndices,
							 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mVelocitiesResetUi = static_cast<Rendering::VelocitiesResetUi*>(mGame->GetServices().GetService(
							 Rendering::VelocitiesResetUi::TypeIdClass()));
	assert(mVelocitiesResetUi);
	return mVelocitiesResetUi != nullptr;
}

void VelocitiesResetDemo::Update()
{
	if (mVelocitiesResetUi->IsNeedRestore())
	{
		//
		mVelocitiesResetUi->SetVertices(mVelocitiesResetSettings->mVertices);
	}
}

void VelocitiesResetDemo::Draw()
{
	EPS_STATE_PROGRAM(mVelocitiesResetProgram->get_product());
	//
	//
	mVelocitiesResetEffect->construct(mVelocitiesResetUi->GetVertices());
	mVelocitiesResetEffect->render(*mVelocitiesResetProgram.get(), eps::utils::to_int(program_enum::a_vertex_xy),
								   mVelocitiesResetSettings->mIndices.size());
}

}

