
#include "DeferredDemo.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "Game.h"
#include "CustomUi.h"

namespace Rendering
{
RTTI_DEFINITIONS(DeferredDemo)

DeferredDemo::DeferredDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(),
	mDeferredEffect(),
	mVertexArrayObject(0),
	mVertexBuffer(eps::rendering::buffer_usage::STATIC_DRAW),
	mIndexBuffer(eps::rendering::buffer_usage::STATIC_DRAW),
	mDiffuseTexture(0),
	mSpecularTexture(0),
	mNormalTexture(0),
	mDiffuse(),
	mSpecular(),
	mNormal(),
	mSettings(),
	mUi(nullptr)
{
}

DeferredDemo::~DeferredDemo()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void DeferredDemo::Initialize()
{
	// Build the shader program
	auto assetPath = "assets/shaders/techniques/lpp.prog";

	if (!eps::rendering::load_program(assetPath, mProgram))
	{
		throw std::runtime_error("Failed to load shader");
	}

	mDeferredEffect.SetProgram(eps::utils::raw_product(mProgram.get_product()));
	// Load the settings
	assetPath = "assets/settings/techniques/lpp.xml";
	mSettings = eps::assets_storage::instance().read<SettingsReader>(assetPath);

	if (!mSettings || mSettings->mIsEmpty)
	{
		throw std::runtime_error("Failed to load settings");
	}

	// Load the textures
	const auto textureMaker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	//
	auto textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mMapDiffuse);

	if (!textureAsset || !textureAsset->pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	mDiffuse = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	mDiffuseTexture = eps::utils::raw_product(mDiffuse.get_product());
	//
	textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mMapSpecular);

	if (!textureAsset || !textureAsset->pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	mSpecular = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	mSpecularTexture = eps::utils::raw_product(mSpecular.get_product());
	//
	textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mMapNormal);

	if (!textureAsset || !textureAsset->pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	mNormal = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	mNormalTexture = eps::utils::raw_product(mNormal.get_product());
	// Create the vertex buffer object
	mVertexBuffer.allocate(&mSettings->mVertices.front(), mSettings->mVertices.size(),
						   sizeof(mSettings->mVertices.front()));
	// Create the index buffer object
	mIndexBuffer.allocate(&mSettings->mIndices.front(), mSettings->mIndices.size(),
						  sizeof(mSettings->mIndices.front()));
	// Create the vertex array object
	glGenVertexArrays(1, &mVertexArrayObject);
	mDeferredEffect.Initialize(mVertexArrayObject);
	glBindVertexArray(0);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Retry the UI service
	mUi = static_cast<Rendering::CustomUi*>(mGame->GetServices().GetService(Rendering::CustomUi::TypeIdClass()));
	assert(mUi);
}

void DeferredDemo::Update(const Library::GameTime&)
{
	if (mUi->IsNeedRestore())
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
	}
}

void DeferredDemo::Draw(const Library::GameTime&)
{
	glBindVertexArray(mVertexArrayObject);
	mVertexBuffer.allocate(&mUi->GetVertices().front(), mUi->GetVertices().size(),
						   sizeof(mUi->GetVertices().front()));
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eps::utils::raw_product(mIndexBuffer.get_product()));
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
	mDeferredEffect.Use();
	//
	mDeferredEffect.u_matrix_mvp() << mUi->Get_u_matrix_mvp();
	mDeferredEffect.u_matrix_model_view() << mUi->Get_u_matrix_model_view();
	mDeferredEffect.u_matrix_view() << mUi->Get_u_matrix_view();
	mDeferredEffect.u_matrix_normal() << mUi->Get_u_matrix_normal();
	//
	mDeferredEffect.u_light_pos() << mUi->Get_u_light_pos();
	mDeferredEffect.u_camera_pos() << mUi->Get_u_camera_pos();
	//
	mDeferredEffect.u_light_diffuse() << mUi->Get_u_light_diffuse();
	mDeferredEffect.u_light_specular() << mUi->Get_u_light_specular();
	mDeferredEffect.u_light_ambient() << mUi->Get_u_light_ambient();
	mDeferredEffect.u_light_range() << mUi->Get_u_light_range();
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

