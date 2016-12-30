
#include "GradientMappingDemo.h"
#include "GradientMappingEffect.h"
#include "GradientMappingUi.h"
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
RTTI_DEFINITIONS(GradientMappingDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_source = 0,
	u_color_1 = 1,
	u_color_2 = 2
};

GradientMappingDemo::GradientMappingDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mGradientMappingProgram(nullptr),
	mGradientMappingEffect(nullptr),
	u_source(nullptr),
	mGradientMappingSettings(),
	mGradientMappingUi(nullptr)
{
}

GradientMappingDemo::~GradientMappingDemo() = default;

bool GradientMappingDemo::Initialize()
{
	// Build the shader program
	mGradientMappingProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/effects/gradient.prog";

	if (!eps::rendering::load_program(assetPath, (*mGradientMappingProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/effects/gradient.xml";
	mGradientMappingSettings = eps::assets_storage::instance().read<GradientMappingSettings>(assetPath);

	if (!mGradientMappingSettings || mGradientMappingSettings->mIsEmpty)
	{
		return false;
	}

	u_source = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mGradientMappingSettings->u_source, (*u_source.get()))
	// Create the effect
	mGradientMappingEffect = eps::utils::make_unique<GradientMappingEffect>(mGradientMappingSettings->mVertices,
							 mGradientMappingSettings->mIndices,
							 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mGradientMappingUi = static_cast<Rendering::GradientMappingUi*>(mGame->GetServices().GetService(
							 Rendering::GradientMappingUi::TypeIdClass()));
	assert(mGradientMappingUi);
	return mGradientMappingUi != nullptr;
}

void GradientMappingDemo::Update()
{
	if (mGradientMappingUi->IsNeedRestore())
	{
		mGradientMappingUi->Set_u_color_1(mGradientMappingSettings->u_color_1);
		mGradientMappingUi->Set_u_color_2(mGradientMappingSettings->u_color_2);
		//
		mGradientMappingUi->SetVertices(mGradientMappingSettings->mVertices);
	}
}

void GradientMappingDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_source->get_product()));
	//
	EPS_STATE_PROGRAM(mGradientMappingProgram->get_product());
	//
	mGradientMappingProgram->uniform_value(eps::utils::to_int(program_enum::u_color_1),
										   mGradientMappingUi->Get_u_color_1());
	mGradientMappingProgram->uniform_value(eps::utils::to_int(program_enum::u_color_2),
										   mGradientMappingUi->Get_u_color_2());
	//
	mGradientMappingEffect->construct(mGradientMappingUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mGradientMappingEffect->render(*mGradientMappingProgram.get(), attributes,
								   mGradientMappingSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

