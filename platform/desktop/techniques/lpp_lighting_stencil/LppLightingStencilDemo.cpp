
#include "LppLightingStencilDemo.h"
#include "LppLightingStencilEffect.h"
#include "LppLightingStencilUi.h"
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
RTTI_DEFINITIONS(LppLightingStencilDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_pos = 0,
	// uniforms
	u_matrix_mvp = 0
};

LppLightingStencilDemo::LppLightingStencilDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mLppLightingStencilProgram(nullptr),
	mLppLightingStencilEffect(nullptr),
	mLppLightingStencilSettings(),
	mLppLightingStencilUi(nullptr)
{
}

LppLightingStencilDemo::~LppLightingStencilDemo() = default;

bool LppLightingStencilDemo::Initialize()
{
	// Build the shader program
	mLppLightingStencilProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/techniques/lpp_lighting_stencil.prog";

	if (!eps::rendering::load_program(assetPath, (*mLppLightingStencilProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/techniques/lpp_lighting_stencil.xml";
	mLppLightingStencilSettings = eps::assets_storage::instance().read<LppLightingStencilSettings>(assetPath);

	if (!mLppLightingStencilSettings || mLppLightingStencilSettings->mIsEmpty)
	{
		return false;
	}

	// Create the effect
	mLppLightingStencilEffect = eps::utils::make_unique<LppLightingStencilEffect>
								(mLppLightingStencilSettings->mVertices, mLppLightingStencilSettings->mIndices,
								 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mLppLightingStencilUi = static_cast<Rendering::LppLightingStencilUi*>(mGame->GetServices().GetService(
								Rendering::LppLightingStencilUi::TypeIdClass()));
	assert(mLppLightingStencilUi);
	return mLppLightingStencilUi != nullptr;
}

void LppLightingStencilDemo::Update()
{
	if (mLppLightingStencilUi->IsNeedRestore())
	{
		mLppLightingStencilUi->Set_u_matrix_mvp(mLppLightingStencilSettings->u_matrix_mvp);
		//
		mLppLightingStencilUi->SetVertices(mLppLightingStencilSettings->mVertices);
	}
}

void LppLightingStencilDemo::Draw()
{
	EPS_STATE_PROGRAM(mLppLightingStencilProgram->get_product());
	//
	mLppLightingStencilProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_mvp),
			mLppLightingStencilUi->Get_u_matrix_mvp());
	//
	mLppLightingStencilEffect->construct(mLppLightingStencilUi->GetVertices());
	mLppLightingStencilEffect->render(*mLppLightingStencilProgram.get(),
									  eps::utils::to_int(program_enum::a_vertex_pos), mLppLightingStencilSettings->mIndices.size());
}

}

