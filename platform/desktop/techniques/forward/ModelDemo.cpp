
#include "ModelDemo.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "CustomUi.h"

namespace Rendering
{
RTTI_DEFINITIONS(ModelDemo)

ModelDemo::ModelDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(),
	mModelEffect(),
	mVertexArrayObject(0),
	mVertexBuffer(nullptr),
	mIndexBuffer(nullptr),
	mDiffuseTexture(0),
	mSpecularTexture(0),
	mNormalTexture(0),
	mDiffuse(nullptr),
	mSpecular(nullptr),
	mNormal(nullptr),
	mSettings(),
	mUi(nullptr)
{
}

ModelDemo::~ModelDemo()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

bool ModelDemo::Initialize()
{
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mModelEffect = eps::utils::make_unique<Library::ModelEffect>();
	mVertexBuffer = eps::utils::make_unique<eps::rendering::vertices>(eps::rendering::buffer_usage::STATIC_DRAW);
	mIndexBuffer = eps::utils::make_unique<eps::rendering::indices>(eps::rendering::buffer_usage::STATIC_DRAW);
	mDiffuse = eps::utils::make_unique<eps::rendering::texture>();
	mSpecular = eps::utils::make_unique<eps::rendering::texture>();
	mNormal = eps::utils::make_unique<eps::rendering::texture>();
	// Build the shader program
	auto assetPath = "assets/shaders/techniques/forward.prog";

	if (!eps::rendering::load_program(assetPath, (*mProgram.get())))
	{
		return false;
	}

	mModelEffect->SetProgram(eps::utils::raw_product(mProgram->get_product()));
	// Load the settings
	assetPath = "assets/settings/techniques/forward.xml";
	mSettings = eps::assets_storage::instance().read<SettingsReader>(assetPath);

	if (!mSettings || mSettings->mIsEmpty)
	{
		return false;
	}

	// Load the textures
	const auto textureMaker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	//
	auto textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mMapDiffuse);

	if (!textureAsset || !textureAsset->pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	(*mDiffuse.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	mDiffuseTexture = eps::utils::raw_product(mDiffuse->get_product());
	//
	textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mMapSpecular);

	if (!textureAsset || !textureAsset->pixels())
	{
		return false;
	}

	(*mSpecular.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	mSpecularTexture = eps::utils::raw_product(mSpecular->get_product());
	//
	textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mMapNormal);

	if (!textureAsset || !textureAsset->pixels())
	{
		return false;
	}

	(*mNormal.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	mNormalTexture = eps::utils::raw_product(mNormal->get_product());
	// Create the vertex buffer object
	mVertexBuffer->allocate(&mSettings->mVertices.front(), mSettings->mVertices.size(),
							sizeof(mSettings->mVertices.front()));
	// Create the index buffer object
	mIndexBuffer->allocate(&mSettings->mIndices.front(), mSettings->mIndices.size(),
						   sizeof(mSettings->mIndices.front()));
	// Create the vertex array object
	glGenVertexArrays(1, &mVertexArrayObject);
	mModelEffect->Initialize(mVertexArrayObject);
	glBindVertexArray(0);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Retry the UI service
	mUi = static_cast<Rendering::CustomUi*>(mGame->GetServices().GetService(Rendering::CustomUi::TypeIdClass()));
	assert(mUi);
	return true;
}

void ModelDemo::Update()
{
	/*if (mUi->IsNeedRestore())
	{
		mUi->Set_u_matrix_mvp(mSettings->mMatrixMvp);
		mUi->Set_u_matrix_model_view(mSettings->mMatrixModelView);
		mUi->Set_u_matrix_view(mSettings->mMatrixView);
		mUi->Set_u_matrix_normal(mSettings->mMatrixNormal);
		//
		mUi->Set_u_light_pos(mSettings->mLightPos);
		mUi->Set_u_camera_pos(mSettings->mCameraPos);
		//
		mUi->Set_u_light_diffuse(mSettings->mLightDiffuse);
		mUi->Set_u_light_specular(mSettings->mLightSpecular);
		mUi->Set_u_light_ambient(mSettings->mLightAmbient);
		mUi->Set_u_light_range(mSettings->mLightRange);
		//
		mUi->SetVertices(mSettings->mVertices);
	}*/
}

void ModelDemo::Draw()
{
	glBindVertexArray(mVertexArrayObject);
	mVertexBuffer->allocate(&mUi->GetVertices().front(), mUi->GetVertices().size(),
							sizeof(mUi->GetVertices().front()));
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eps::utils::raw_product(mIndexBuffer->get_product()));
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mDiffuseTexture);
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mSpecularTexture);
	//
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mNormalTexture);
	//
	mModelEffect->Use();
	//
	mModelEffect->u_matrix_mvp() << mUi->Get_u_matrix_mvp();
	mModelEffect->u_matrix_model_view() << mUi->Get_u_matrix_model_view();
	mModelEffect->u_matrix_view() << mUi->Get_u_matrix_view();
	mModelEffect->u_matrix_normal() << mUi->Get_u_matrix_normal();
	//
	mModelEffect->u_light_pos() << mUi->Get_u_light_pos();
	mModelEffect->u_camera_pos() << mUi->Get_u_camera_pos();
	//
	/*mModelEffect->u_light_diffuse() << mUi->Get_u_light_diffuse();
	mModelEffect->u_light_specular() << mUi->Get_u_light_specular();
	mModelEffect->u_light_ambient() << mUi->Get_u_light_ambient();
	mModelEffect->u_light_range() << mUi->Get_u_light_range();*/
	//
	glDrawElements(GL_TRIANGLES, mSettings->mIndices.size(), GL_UNSIGNED_INT, nullptr);
	//
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

}
