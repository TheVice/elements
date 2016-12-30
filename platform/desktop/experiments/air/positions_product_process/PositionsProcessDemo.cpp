
#include "PositionsProcessDemo.h"
#include "PositionsProcessEffect.h"
#include "PositionsProcessUi.h"
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
RTTI_DEFINITIONS(PositionsProcessDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	// uniforms
	u_positions = 0,
	u_velocities = 1,
	u_dt = 2
};

PositionsProcessDemo::PositionsProcessDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mPositionsProcessProgram(nullptr),
	mPositionsProcessEffect(nullptr),
	u_positions(nullptr),
	u_velocities(nullptr),
	mPositionsProcessSettings(),
	mPositionsProcessUi(nullptr)
{
}

PositionsProcessDemo::~PositionsProcessDemo() = default;

bool PositionsProcessDemo::Initialize()
{
	// Build the shader program
	mPositionsProcessProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/air/positions_product_process.prog";

	if (!eps::rendering::load_program(assetPath, (*mPositionsProcessProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/air/positions_product_process.xml";
	mPositionsProcessSettings = eps::assets_storage::instance().read<PositionsProcessSettings>(assetPath);

	if (!mPositionsProcessSettings || mPositionsProcessSettings->mIsEmpty)
	{
		return false;
	}

	u_positions = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mPositionsProcessSettings->u_positions, (*u_positions.get()))
	u_velocities = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mPositionsProcessSettings->u_velocities, (*u_velocities.get()))
	// Create the effect
	mPositionsProcessEffect = eps::utils::make_unique<PositionsProcessEffect>
							  (mPositionsProcessSettings->mVertices, mPositionsProcessSettings->mIndices,
							   eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mPositionsProcessUi = static_cast<Rendering::PositionsProcessUi*>(mGame->GetServices().GetService(
							  Rendering::PositionsProcessUi::TypeIdClass()));
	assert(mPositionsProcessUi);
	return mPositionsProcessUi != nullptr;
}

void PositionsProcessDemo::Update()
{
	if (mPositionsProcessUi->IsNeedRestore())
	{
		mPositionsProcessUi->Set_u_dt(mPositionsProcessSettings->u_dt);
		//
		mPositionsProcessUi->SetVertices(mPositionsProcessSettings->mVertices);
	}
}

void PositionsProcessDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_positions->get_product()));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_velocities->get_product()));
	//
	EPS_STATE_PROGRAM(mPositionsProcessProgram->get_product());
	//
	mPositionsProcessProgram->uniform_value(eps::utils::to_int(program_enum::u_dt),
											mPositionsProcessUi->Get_u_dt());
	//
	mPositionsProcessEffect->construct(mPositionsProcessUi->GetVertices());
	mPositionsProcessEffect->render(*mPositionsProcessProgram.get(),
									eps::utils::to_int(program_enum::a_vertex_xy), mPositionsProcessSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

