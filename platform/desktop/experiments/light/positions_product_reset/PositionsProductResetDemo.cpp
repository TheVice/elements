
#include "PositionsProductResetDemo.h"
#include "PositionsProductResetEffect.h"
#include "PositionsProductResetUi.h"
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
RTTI_DEFINITIONS(PositionsProductResetDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	// uniforms
	u_displacement = 0
};

PositionsProductResetDemo::PositionsProductResetDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mPositionsProductResetProgram(nullptr),
	mPositionsProductResetEffect(nullptr),
	u_displacement(nullptr),
	mPositionsProductResetSettings(),
	mPositionsProductResetUi(nullptr)
{
}

PositionsProductResetDemo::~PositionsProductResetDemo() = default;

bool PositionsProductResetDemo::Initialize()
{
	// Build the shader program
	mPositionsProductResetProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/light/positions_product_reset.prog";

	if (!eps::rendering::load_program(assetPath, (*mPositionsProductResetProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/light/positions_product_reset.xml";
	mPositionsProductResetSettings = eps::assets_storage::instance().read<PositionsProductResetSettings>
									 (assetPath);

	if (!mPositionsProductResetSettings || mPositionsProductResetSettings->mIsEmpty)
	{
		return false;
	}

	u_displacement = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mPositionsProductResetSettings->u_displacement, (*u_displacement.get()))
	// Create the effect
	mPositionsProductResetEffect = eps::utils::make_unique<PositionsProductResetEffect>
								   (mPositionsProductResetSettings->mVertices, mPositionsProductResetSettings->mIndices,
									eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mPositionsProductResetUi = static_cast<Rendering::PositionsProductResetUi*>(mGame->GetServices().GetService(
								   Rendering::PositionsProductResetUi::TypeIdClass()));
	assert(mPositionsProductResetUi);
	return mPositionsProductResetUi != nullptr;
}

void PositionsProductResetDemo::Update()
{
	if (mPositionsProductResetUi->IsNeedRestore())
	{
		//
		mPositionsProductResetUi->SetVertices(mPositionsProductResetSettings->mVertices);
	}
}

void PositionsProductResetDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_displacement->get_product()));
	//
	EPS_STATE_PROGRAM(mPositionsProductResetProgram->get_product());
	//
	//
	mPositionsProductResetEffect->construct(mPositionsProductResetUi->GetVertices());
	mPositionsProductResetEffect->render(*mPositionsProductResetProgram.get(),
										 eps::utils::to_int(program_enum::a_vertex_xy), mPositionsProductResetSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

