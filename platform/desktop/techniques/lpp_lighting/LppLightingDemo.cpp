
#include "LppLightingDemo.h"
#include "LppLightingEffect.h"
#include "LppLightingUi.h"
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
RTTI_DEFINITIONS(LppLightingDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_pos = 0,
	// uniforms
	u_matrix_mvp = 0,
	u_camera_view_param = 1,
	u_camera_near = 2,
	u_camera_far = 3,
	u_map_geometry = 4,
	u_map_depth = 5,
	u_light_pos = 6,
	u_light_intensity = 7,
	u_light_inv_range_square = 8
};

LppLightingDemo::LppLightingDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mLppLightingProgram(nullptr),
	mLppLightingEffect(nullptr),
	u_map_geometry(nullptr),
	u_map_depth(nullptr),
	mLppLightingSettings(),
	mLppLightingUi(nullptr)
{
}

LppLightingDemo::~LppLightingDemo() = default;

bool LppLightingDemo::Initialize()
{
	// Build the shader program
	mLppLightingProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/techniques/lpp_lighting.prog";

	if (!eps::rendering::load_program(assetPath, (*mLppLightingProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/techniques/lpp_lighting.xml";
	mLppLightingSettings = eps::assets_storage::instance().read<LppLightingSettings>(assetPath);

	if (!mLppLightingSettings || mLppLightingSettings->mIsEmpty)
	{
		return false;
	}

	u_map_geometry = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mLppLightingSettings->u_map_geometry, (*u_map_geometry.get()))
	u_map_depth = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mLppLightingSettings->u_map_depth, (*u_map_depth.get()))
	// Create the effect
	mLppLightingEffect = eps::utils::make_unique<LppLightingEffect>(mLppLightingSettings->mVertices,
						 mLppLightingSettings->mIndices,
						 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mLppLightingUi = static_cast<Rendering::LppLightingUi*>(mGame->GetServices().GetService(
						 Rendering::LppLightingUi::TypeIdClass()));
	assert(mLppLightingUi);
	return mLppLightingUi != nullptr;
}

void LppLightingDemo::Update()
{
	if (mLppLightingUi->IsNeedRestore())
	{
		mLppLightingUi->Set_u_matrix_mvp(mLppLightingSettings->u_matrix_mvp);
		mLppLightingUi->Set_u_camera_view_param(mLppLightingSettings->u_camera_view_param);
		mLppLightingUi->Set_u_camera_near(mLppLightingSettings->u_camera_near);
		mLppLightingUi->Set_u_camera_far(mLppLightingSettings->u_camera_far);
		mLppLightingUi->Set_u_light_pos(mLppLightingSettings->u_light_pos);
		mLppLightingUi->Set_u_light_intensity(mLppLightingSettings->u_light_intensity);
		mLppLightingUi->Set_u_light_inv_range_square(mLppLightingSettings->u_light_inv_range_square);
		//
		mLppLightingUi->SetVertices(mLppLightingSettings->mVertices);
	}
}

void LppLightingDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_map_geometry->get_product()));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_map_depth->get_product()));
	//
	EPS_STATE_PROGRAM(mLppLightingProgram->get_product());
	//
	mLppLightingProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_mvp),
									   mLppLightingUi->Get_u_matrix_mvp());
	mLppLightingProgram->uniform_value(eps::utils::to_int(program_enum::u_camera_view_param),
									   mLppLightingUi->Get_u_camera_view_param());
	mLppLightingProgram->uniform_value(eps::utils::to_int(program_enum::u_camera_near),
									   mLppLightingUi->Get_u_camera_near());
	mLppLightingProgram->uniform_value(eps::utils::to_int(program_enum::u_camera_far),
									   mLppLightingUi->Get_u_camera_far());
	mLppLightingProgram->uniform_value(eps::utils::to_int(program_enum::u_light_pos),
									   mLppLightingUi->Get_u_light_pos());
	mLppLightingProgram->uniform_value(eps::utils::to_int(program_enum::u_light_intensity),
									   mLppLightingUi->Get_u_light_intensity());
	mLppLightingProgram->uniform_value(eps::utils::to_int(program_enum::u_light_inv_range_square),
									   mLppLightingUi->Get_u_light_inv_range_square());
	//
	mLppLightingEffect->construct(mLppLightingUi->GetVertices());
	mLppLightingEffect->render(*mLppLightingProgram.get(), eps::utils::to_int(program_enum::a_vertex_pos),
							   mLppLightingSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

