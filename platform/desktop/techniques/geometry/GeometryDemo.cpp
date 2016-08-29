
#include "GeometryDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "utils/std/enum.h"
#include "Game.h"
#include "CustomUi.h"

namespace Rendering
{
RTTI_DEFINITIONS(GeometryDemo)

GeometryDemo::GeometryDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mGeometryEffect(),
	mVertexArrayObject(0),
	mVertexBuffer(0),
	mIndexBuffer(0),
	mColorTexture(0),
	mTexture(),
	mSettings(),
	mUi(nullptr)
{
}

GeometryDemo::~GeometryDemo()
{
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void GeometryDemo::Initialize()
{
	// Build the shader program
	auto data =
		eps::assets_storage::instance().read<eps::rendering::program_data>("assets/shaders/techniques/geometry.prog");

	if (!data || !data.value().v_shader() || !data.value().f_shader())
	{
		throw std::runtime_error("Failed to load shader");
	}

	std::vector<Library::ShaderDefinition> shaders(2);
	shaders.clear();
	//
	shaders.push_back(Library::ShaderDefinition(GL_VERTEX_SHADER, data.value().v_shader()));
	shaders.push_back(Library::ShaderDefinition(GL_FRAGMENT_SHADER, data.value().f_shader()));
	//
	mGeometryEffect.BuildProgram(shaders);
	// Load the settings
	auto assetPath = "assets/settings/techniques/geometry.xml";
	mSettings = eps::assets_storage::instance().read<SettingsReader>(assetPath);

	if (!mSettings || mSettings->mIsEmpty)
	{
		throw std::runtime_error("Failed to load settings");
	}

	// Load the texture
	auto asset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mTexturePath);

	if (!asset.value().pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	auto maker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>(asset->format());
	mTexture = maker.construct(asset->pixels(), asset->size());
	mColorTexture = (*eps::utils::ptr_product(mTexture.get_product()));
	// Create the vertex buffer object
	mGeometryEffect.CreateVertexBuffer(&mSettings->mVertices.front(), mSettings->mVertices.size(), mVertexBuffer);
	// Create the index buffer
	mGeometryEffect.CreateIndexBuffer(&mSettings->mIndices.front(), mSettings->mIndices.size(), mIndexBuffer);
	// Create the vertex array object
	glGenVertexArrays(1, &mVertexArrayObject);
	mGeometryEffect.Initialize(mVertexArrayObject);
	glBindVertexArray(0);
	// Retry the UI service and set the values from settings class
	mUi = static_cast<Rendering::CustomUi*>(mGame->GetServices().GetService(Rendering::CustomUi::TypeIdClass()));
	assert(mUi);
	mUi->SetMatrixMvp(mSettings->mMatrixMvp);
	mUi->SetMatrixNormal(mSettings->mMatrixNormal);
	//	mUi->SetVertices(mSettings->mVertices);
	mUi->_setNormalLT_x(mSettings->mVertices[0].a_vertex_normal.x);
}

void GeometryDemo::Update(const Library::GameTime&)
{
	mSettings->mMatrixMvp = mUi->GetMatrixMvp();
	mSettings->mMatrixNormal = mUi->GetMatrixNormal();
	//	mSettings->mVertices = mUi->GetVertices();
	mSettings->mVertices.begin()->a_vertex_normal.x = mUi->_getNormalLT_x();
}

void GeometryDemo::Draw(const Library::GameTime&)
{
	glBindVertexArray(mVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mGeometryEffect.GetVertexSize() * mSettings->mVertices.size(),
				 &mSettings->mVertices.front(),
				 GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBindTexture(GL_TEXTURE_2D, mColorTexture);
	//
	mGeometryEffect.Use();
	mGeometryEffect.u_matrix_mvp() << mSettings->mMatrixMvp;
	mGeometryEffect.u_matrix_normal() << mSettings->mMatrixNormal;
	//
	glDrawElements(GL_TRIANGLES, mSettings->mIndices.size(), GL_UNSIGNED_INT, nullptr);
	//
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

}
