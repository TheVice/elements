
#include "VelocitiesProcessDemo.h"
#include "VelocitiesProcessEffect.h"
#include "VelocitiesProcessUi.h"
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
RTTI_DEFINITIONS(VelocitiesProcessDemo)

enum class program_enum : short
{
	// attributes
	a_field_uv = 0,
	a_field_data = 1,
	// uniforms
	u_product = 0,
	u_dt = 1
};

VelocitiesProcessDemo::VelocitiesProcessDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mVelocitiesProcessProgram(nullptr),
	mVelocitiesProcessEffect(nullptr),
	u_product(nullptr),
	mVelocitiesProcessSettings(),
	mVelocitiesProcessUi(nullptr)
{
}

VelocitiesProcessDemo::~VelocitiesProcessDemo() = default;

bool VelocitiesProcessDemo::Initialize()
{
	// Build the shader program
	mVelocitiesProcessProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/light/velocities_product_process.prog";

	if (!eps::rendering::load_program(assetPath, (*mVelocitiesProcessProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/light/velocities_product_process.xml";
	mVelocitiesProcessSettings = eps::assets_storage::instance().read<VelocitiesProcessSettings>(assetPath);

	if (!mVelocitiesProcessSettings || mVelocitiesProcessSettings->mIsEmpty)
	{
		return false;
	}

	u_product = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mVelocitiesProcessSettings->u_product, (*u_product.get()))
	// Create the effect
	mVelocitiesProcessEffect = eps::utils::make_unique<VelocitiesProcessEffect>
							   (mVelocitiesProcessSettings->mVertices, mVelocitiesProcessSettings->mIndices,
								eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mVelocitiesProcessUi = static_cast<Rendering::VelocitiesProcessUi*>(mGame->GetServices().GetService(
							   Rendering::VelocitiesProcessUi::TypeIdClass()));
	assert(mVelocitiesProcessUi);
	return mVelocitiesProcessUi != nullptr;
}

void VelocitiesProcessDemo::Update()
{
	if (mVelocitiesProcessUi->IsNeedRestore())
	{
		mVelocitiesProcessUi->Set_u_dt(mVelocitiesProcessSettings->u_dt);
		//
		mVelocitiesProcessUi->SetVertices(mVelocitiesProcessSettings->mVertices);
	}
}

void VelocitiesProcessDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_product->get_product()));
	//
	EPS_STATE_PROGRAM(mVelocitiesProcessProgram->get_product());
	//
	mVelocitiesProcessProgram->uniform_value(eps::utils::to_int(program_enum::u_dt),
			mVelocitiesProcessUi->Get_u_dt());
	//
	mVelocitiesProcessEffect->construct(mVelocitiesProcessUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_field_uv), eps::utils::to_int(program_enum::a_field_data) };
	mVelocitiesProcessEffect->render(*mVelocitiesProcessProgram.get(), attributes,
									 mVelocitiesProcessSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

