
#include "ModelDemo.h"
#include "ModelEffect.h"
#include "ModelUi.h"
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

namespace Rendering
{
RTTI_DEFINITIONS(ModelDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_pos = 0,
	a_vertex_normal = 1,
	a_vertex_tangent = 2,
	a_vertex_uv = 3,
	// uniforms
	u_matrix_mvp = 0,
	u_matrix_model_view = 1,
	u_matrix_normal = 2,
	u_matrix_view = 3,
	u_camera_pos = 4,
	u_map_diffuse = 5,
	u_map_specular = 6,
	u_map_normal = 7,
	u_light_pos = 8,
	u_light_intensity = 9,
	u_light_range = 10
};

ModelDemo::ModelDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mModelEffect(nullptr),
	mDiffuseTexture(nullptr),
	mSpecularTexture(nullptr),
	mNormalTexture(nullptr),
	mModelSettings(),
	mModelUi(nullptr)
{
}

ModelDemo::~ModelDemo() = default;

bool ModelDemo::Initialize()
{
	// Build the shader program
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/techniques/forward.prog";

	if (!eps::rendering::load_program(assetPath, (*mProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/techniques/forward.xml";
	mModelSettings = eps::assets_storage::instance().read<ModelSettings>(assetPath);

	if (!mModelSettings || mModelSettings->mIsEmpty)
	{
		return false;
	}

	// Load the textures
	const auto textureMaker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	//
	auto textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mModelSettings->mMapDiffuse);

	if (!textureAsset || !textureAsset->pixels())
	{
		return false;
	}

	mDiffuseTexture = eps::utils::make_unique<eps::rendering::texture>();
	(*mDiffuseTexture.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	//
	textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mModelSettings->mMapSpecular);

	if (!textureAsset || !textureAsset->pixels())
	{
		return false;
	}

	mSpecularTexture = eps::utils::make_unique<eps::rendering::texture>();
	(*mSpecularTexture.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	//
	textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mModelSettings->mMapNormal);

	if (!textureAsset || !textureAsset->pixels())
	{
		return false;
	}

	mNormalTexture = eps::utils::make_unique<eps::rendering::texture>();
	(*mNormalTexture.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	// Create the effect
	mModelEffect = eps::utils::make_unique<ModelEffect>(mModelSettings->mVertices, mModelSettings->mIndices,
				   eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mModelUi = static_cast<Rendering::ModelUi*>(mGame->GetServices().GetService(
				   Rendering::ModelUi::TypeIdClass()));
	assert(mModelUi);
	return mModelUi != nullptr;
}

void ModelDemo::Update()
{
	if (mModelUi->IsNeedRestore())
	{
		mModelUi->Set_u_matrix_mvp(mModelSettings->mMatrixMvp);
		mModelUi->Set_u_matrix_model_view(mModelSettings->mMatrixModelView);
		mModelUi->Set_u_matrix_view(mModelSettings->mMatrixView);
		mModelUi->Set_u_matrix_normal(mModelSettings->mMatrixNormal);
		//
		mModelUi->Set_u_light_pos(mModelSettings->mLightPos);
		mModelUi->Set_u_camera_pos(mModelSettings->mCameraPos);
		//
		mModelUi->Set_u_light_intensity(mModelSettings->mLightIntensity);
		mModelUi->Set_u_light_range(mModelSettings->mLightRange);
		//
		mModelUi->SetVertices(mModelSettings->mVertices);
	}
}

void ModelDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(mDiffuseTexture->get_product()));
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(mSpecularTexture->get_product()));
	//
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(mNormalTexture->get_product()));
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_mvp), mModelUi->Get_u_matrix_mvp());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_model_view),
							mModelUi->Get_u_matrix_model_view());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_normal), mModelUi->Get_u_matrix_normal());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_view), mModelUi->Get_u_matrix_view());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_camera_pos), mModelUi->Get_u_camera_pos());
	//
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_light_pos), mModelUi->Get_u_light_pos());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_light_intensity),
							mModelUi->Get_u_light_intensity());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_light_range), mModelUi->Get_u_light_range());
	//
	mModelEffect->construct(mModelUi->GetVertices());
	//
	std::array<short, 4> attributes = { eps::utils::to_int(program_enum::a_vertex_pos), eps::utils::to_int(program_enum::a_vertex_normal),
										eps::utils::to_int(program_enum::a_vertex_tangent), eps::utils::to_int(program_enum::a_vertex_uv)
									  };
	mModelEffect->render(*mProgram.get(), attributes, mModelSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
