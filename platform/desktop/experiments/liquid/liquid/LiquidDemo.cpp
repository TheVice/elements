
#include "LiquidDemo.h"
#include "LiquidEffect.h"
#include "LiquidUi.h"
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
RTTI_DEFINITIONS(LiquidDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_surface = 0,
	u_surface_background = 1,
	u_surface_color = 2,
	u_surface_texel = 3
};

LiquidDemo::LiquidDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mLiquidProgram(nullptr),
	mLiquidEffect(nullptr),
	u_surface(nullptr),
	u_surface_background(nullptr),
	mLiquidSettings(),
	mLiquidUi(nullptr)
{
}

LiquidDemo::~LiquidDemo() = default;

bool LiquidDemo::Initialize()
{
	// Build the shader program
	mLiquidProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/liquid/liquid.prog";

	if (!eps::rendering::load_program(assetPath, (*mLiquidProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/liquid/liquid.xml";
	mLiquidSettings = eps::assets_storage::instance().read<LiquidSettings>(assetPath);

	if (!mLiquidSettings || mLiquidSettings->mIsEmpty)
	{
		return false;
	}

	u_surface = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mLiquidSettings->u_surface, (*u_surface.get()))
	u_surface_background = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mLiquidSettings->u_surface_background, (*u_surface_background.get()))
	// Create the effect
	mLiquidEffect = eps::utils::make_unique<LiquidEffect>(mLiquidSettings->mVertices, mLiquidSettings->mIndices,
					eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mLiquidUi = static_cast<Rendering::LiquidUi*>(mGame->GetServices().GetService(
					Rendering::LiquidUi::TypeIdClass()));
	assert(mLiquidUi);
	return mLiquidUi != nullptr;
}

void LiquidDemo::Update()
{
	if (mLiquidUi->IsNeedRestore())
	{
		mLiquidUi->Set_u_surface_color(mLiquidSettings->u_surface_color);
		mLiquidUi->Set_u_surface_texel(mLiquidSettings->u_surface_texel);
		//
		mLiquidUi->SetVertices(mLiquidSettings->mVertices);
	}
}

void LiquidDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_surface->get_product()));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_surface_background->get_product()));
	//
	EPS_STATE_PROGRAM(mLiquidProgram->get_product());
	//
	mLiquidProgram->uniform_value(eps::utils::to_int(program_enum::u_surface_color),
								  mLiquidUi->Get_u_surface_color());
	mLiquidProgram->uniform_value(eps::utils::to_int(program_enum::u_surface_texel),
								  mLiquidUi->Get_u_surface_texel());
	//
	mLiquidEffect->construct(mLiquidUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mLiquidEffect->render(*mLiquidProgram.get(), attributes, mLiquidSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
