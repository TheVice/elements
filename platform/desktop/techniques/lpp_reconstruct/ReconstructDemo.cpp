
#include "ReconstructDemo.h"
#include "ReconstructEffect.h"
#include "ReconstructUi.h"
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
RTTI_DEFINITIONS(ReconstructDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_pos = 0,
	a_vertex_uv = 1,
	// uniforms
	u_matrix_mvp = 0,
	u_map_light = 1,
	u_map_diffuse = 2,
	u_map_specular = 3,
	u_has_map_diffuse = 4,
	u_has_map_specular = 5,
	u_color_diffuse = 6,
	u_color_specular = 7
};

ReconstructDemo::ReconstructDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mReconstructProgram(nullptr),
	mReconstructEffect(nullptr),
	u_map_light(nullptr),
	u_map_diffuse(nullptr),
	u_map_specular(nullptr),
	mReconstructSettings(),
	mReconstructUi(nullptr)
{
}

ReconstructDemo::~ReconstructDemo() = default;

bool ReconstructDemo::Initialize()
{
	// Build the shader program
	mReconstructProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/techniques/lpp_reconstruct.prog";

	if (!eps::rendering::load_program(assetPath, (*mReconstructProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/techniques/lpp_reconstruct.xml";
	mReconstructSettings = eps::assets_storage::instance().read<ReconstructSettings>(assetPath);

	if (!mReconstructSettings || mReconstructSettings->mIsEmpty)
	{
		return false;
	}

	u_map_light = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mReconstructSettings->u_map_light, (*u_map_light.get()))
	u_map_diffuse = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mReconstructSettings->u_map_diffuse, (*u_map_diffuse.get()))
	u_map_specular = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mReconstructSettings->u_map_specular, (*u_map_specular.get()))
	// Create the effect
	mReconstructEffect = eps::utils::make_unique<ReconstructEffect>(mReconstructSettings->mVertices,
						 mReconstructSettings->mIndices,
						 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mReconstructUi = static_cast<Rendering::ReconstructUi*>(mGame->GetServices().GetService(
						 Rendering::ReconstructUi::TypeIdClass()));
	assert(mReconstructUi);
	return mReconstructUi != nullptr;
}

void ReconstructDemo::Update()
{
	if (mReconstructUi->IsNeedRestore())
	{
		mReconstructUi->Set_u_matrix_mvp(mReconstructSettings->u_matrix_mvp);
		mReconstructUi->Set_u_color_diffuse(mReconstructSettings->u_color_diffuse);
		mReconstructUi->Set_u_color_specular(mReconstructSettings->u_color_specular);
		//
		mReconstructUi->SetVertices(mReconstructSettings->mVertices);
	}
}

void ReconstructDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_map_light->get_product()));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_map_diffuse->get_product()));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_map_specular->get_product()));
	//
	EPS_STATE_PROGRAM(mReconstructProgram->get_product());
	//
	mReconstructProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_mvp),
									   mReconstructUi->Get_u_matrix_mvp());
	mReconstructProgram->uniform_value(eps::utils::to_int(program_enum::u_has_map_diffuse),
									   mReconstructUi->Get_u_has_map_diffuse());
	mReconstructProgram->uniform_value(eps::utils::to_int(program_enum::u_has_map_specular),
									   mReconstructUi->Get_u_has_map_specular());
	mReconstructProgram->uniform_value(eps::utils::to_int(program_enum::u_color_diffuse),
									   mReconstructUi->Get_u_color_diffuse());
	mReconstructProgram->uniform_value(eps::utils::to_int(program_enum::u_color_specular),
									   mReconstructUi->Get_u_color_specular());
	//
	mReconstructEffect->construct(mReconstructUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_pos), eps::utils::to_int(program_enum::a_vertex_uv) };
	mReconstructEffect->render(*mReconstructProgram.get(), attributes, mReconstructSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

