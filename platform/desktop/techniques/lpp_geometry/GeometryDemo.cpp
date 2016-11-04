
#include "GeometryDemo.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "utils/std/enum.h"
#include "utils/std/product.h"
#include "CustomUi.h"

namespace Rendering
{
RTTI_DEFINITIONS(GeometryDemo)

GeometryDemo::GeometryDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgramEncodeNormal(nullptr),
	mProgramNonEncodeNormal(nullptr),
	mGeometryEffect(nullptr),
	mVertexArrayObject(0),
	mVertexBuffer(nullptr),
	mIndexBuffer(nullptr),
	mColorTexture(0),
	mTexture(nullptr),
	mSettings(),
	mUi(nullptr),
	mIsNonEncodeProgramLoaded(false)
{
}

GeometryDemo::~GeometryDemo()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

bool GeometryDemo::Initialize()
{
	mProgramEncodeNormal = eps::utils::make_unique<eps::rendering::program>();
	mProgramNonEncodeNormal = eps::utils::make_unique<eps::rendering::program>();
	mGeometryEffect = eps::utils::make_unique<Library::GeometryEffect>();
	mVertexBuffer = eps::utils::make_unique<eps::rendering::vertices>(eps::rendering::buffer_usage::STATIC_DRAW);
	mIndexBuffer = eps::utils::make_unique<eps::rendering::indices>(eps::rendering::buffer_usage::STATIC_DRAW);
	mTexture = eps::utils::make_unique<eps::rendering::texture>();
	// Build the shader program
	auto assetPath = "assets/shaders/techniques/lpp_geometry.prog";

	if (!eps::rendering::load_program(assetPath, (*mProgramEncodeNormal.get())))
	{
		return false;
	}

	mGeometryEffect->SetProgram(eps::utils::raw_product(mProgramEncodeNormal->get_product()));
	assetPath = "assets/shaders/techniques/lpp_geometry_non_encode.prog";
	mIsNonEncodeProgramLoaded = eps::rendering::load_program(assetPath, (*mProgramNonEncodeNormal.get()));
	// Load the settings
	assetPath = "assets/settings/techniques/geometry.xml"; //TODO: lpp_geometry.xml;
	mSettings = eps::assets_storage::instance().read<SettingsReader>(assetPath);

	if (!mSettings || mSettings->mIsEmpty)
	{
		return false;
	}

	// Load the texture
	const auto textureAsset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mTexturePath);

	if (!textureAsset || !textureAsset->pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	auto textureMaker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	(*mTexture.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	mColorTexture = eps::utils::raw_product(mTexture->get_product());
	// Create the vertex buffer object
	mVertexBuffer->allocate(&mSettings->mVertices.front(), mSettings->mVertices.size(),
							sizeof(mSettings->mVertices.front()));
	// Create the index buffer object
	mIndexBuffer->allocate(&mSettings->mIndices.front(), mSettings->mIndices.size(),
						   sizeof(mSettings->mIndices.front()));
	// Create the vertex array object
	glGenVertexArrays(1, &mVertexArrayObject);
	mGeometryEffect->Initialize(mVertexArrayObject);
	glBindVertexArray(0);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Retry the UI service and set the values from settings class
	mUi = static_cast<Rendering::CustomUi*>(mGame->GetServices().GetService(Rendering::CustomUi::TypeIdClass()));
	assert(mUi);
	mUi->Set_u_matrix_mvp(mSettings->mMatrixMvp);
	mUi->Set_u_matrix_normal(mSettings->mMatrixNormal);
	mUi->SetVertices(mSettings->mVertices);

	if (!mIsNonEncodeProgramLoaded)
	{
		mUi->SetEncodeNormalControlsVisible(false);
	}

	return true;
}

void GeometryDemo::Update()
{
	if (mUi->IsNeedRestore())
	{
		mUi->Set_u_matrix_mvp(mSettings->mMatrixMvp);
		mUi->Set_u_matrix_normal(mSettings->mMatrixNormal);
		mUi->SetVertices(mSettings->mVertices);
	}
}

void GeometryDemo::Draw()
{
	glBindVertexArray(mVertexArrayObject);
	mVertexBuffer->allocate(&mUi->GetVertices().front(), mUi->GetVertices().size(),
							sizeof(mUi->GetVertices().front()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eps::utils::raw_product(mIndexBuffer->get_product()));
	glBindTexture(GL_TEXTURE_2D, mColorTexture);

	if (mIsNonEncodeProgramLoaded)
	{
		if (mUi->IsEncodeNormal())
		{
			mGeometryEffect->SetProgram(eps::utils::raw_product(mProgramEncodeNormal->get_product()));
		}
		else
		{
			mGeometryEffect->SetProgram(eps::utils::raw_product(mProgramNonEncodeNormal->get_product()));
		}
	}

	mGeometryEffect->Use();
	mGeometryEffect->u_matrix_mvp() << mUi->Get_u_matrix_mvp();
	mGeometryEffect->u_matrix_normal() << mUi->Get_u_matrix_normal();
	//
	glDrawElements(GL_TRIANGLES, mSettings->mIndices.size(), GL_UNSIGNED_INT, nullptr);
	//
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

}
