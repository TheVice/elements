
#include "GeometryDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "utils/std/enum.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(GeometryDemo)

GeometryDemo::GeometryDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mGeometryEffect(),
	mVertexArrayObject(0),
	mVertexBuffer(0),
	mVertexCount(0),
	mTexture(),
	mSettings(nullptr)
{
}

GeometryDemo::~GeometryDemo()
{
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
		throw std::runtime_error("load shader program failed");
	}

	std::vector<Library::ShaderDefinition> shaders(2);
	shaders.clear();
	//
	shaders.push_back(Library::ShaderDefinition(GL_VERTEX_SHADER, data.value().v_shader()));
	shaders.push_back(Library::ShaderDefinition(GL_FRAGMENT_SHADER, data.value().f_shader()));
	//
	mGeometryEffect.BuildProgram(shaders, GL_TRUE);
	// Load the settings
	mSettings = std::make_unique<SettingsReader>();
	bool settingLoaded = load_data("settings/techniques/geometry.xml", *mSettings.get());

	if (!settingLoaded)
	{
		mGame->Exit();
	}

	// Load the texture
	auto asset = eps::assets_storage::instance().read<eps::asset_texture>(mSettings->mTexturePath);

	if (!asset.value().pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	auto maker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>(asset->format());
	mTexture = maker.construct(asset->pixels(), asset->size());
	// Create the vertex buffer object
	mVertexCount = mSettings->mVertices.size();
	mGeometryEffect.CreateVertexBuffer(&mSettings->mVertices.front(), mVertexCount, mVertexBuffer);
	// Create the vertex array object
	glGenVertexArrays(1, &mVertexArrayObject);
	mGeometryEffect.Initialize(mVertexArrayObject);
	glBindVertexArray(0);
}

void GeometryDemo::Draw(const Library::GameTime&)
{
	GLuint colorTexture = (*eps::utils::ptr_product(mTexture.get_product()));
	glBindVertexArray(mVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	//
	mGeometryEffect.Use();
	mGeometryEffect.u_matrix_mvp() << mSettings->mMatrixMvp;
	mGeometryEffect.u_matrix_normal() << mSettings->mMatrixNormal;
	//
	glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
	//
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

}
