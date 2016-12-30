
#include "PositionsResetDemo.h"
#include "PositionsResetEffect.h"
#include "PositionsResetUi.h"
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
RTTI_DEFINITIONS(PositionsResetDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	// uniforms

};

PositionsResetDemo::PositionsResetDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mPositionsResetProgram(nullptr),
	mPositionsResetEffect(nullptr),
	mPositionsResetSettings(),
	mPositionsResetUi(nullptr)
{
}

PositionsResetDemo::~PositionsResetDemo() = default;

bool PositionsResetDemo::Initialize()
{
	// Build the shader program
	mPositionsResetProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/air/positions_product_reset.prog";

	if (!eps::rendering::load_program(assetPath, (*mPositionsResetProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/air/positions_product_reset.xml";
	mPositionsResetSettings = eps::assets_storage::instance().read<PositionsResetSettings>(assetPath);

	if (!mPositionsResetSettings || mPositionsResetSettings->mIsEmpty)
	{
		return false;
	}

	// Create the effect
	mPositionsResetEffect = eps::utils::make_unique<PositionsResetEffect>(mPositionsResetSettings->mVertices,
							mPositionsResetSettings->mIndices,
							eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mPositionsResetUi = static_cast<Rendering::PositionsResetUi*>(mGame->GetServices().GetService(
							Rendering::PositionsResetUi::TypeIdClass()));
	assert(mPositionsResetUi);
	return mPositionsResetUi != nullptr;
}

void PositionsResetDemo::Update()
{
	if (mPositionsResetUi->IsNeedRestore())
	{
		//
		mPositionsResetUi->SetVertices(mPositionsResetSettings->mVertices);
	}
}

void PositionsResetDemo::Draw()
{
	EPS_STATE_PROGRAM(mPositionsResetProgram->get_product());
	//
	//
	mPositionsResetEffect->construct(mPositionsResetUi->GetVertices());
	mPositionsResetEffect->render(*mPositionsResetProgram.get(), eps::utils::to_int(program_enum::a_vertex_xy),
								  mPositionsResetSettings->mIndices.size());
}

}

