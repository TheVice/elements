
#include "GeometryDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "utils/std/product.h"
#include "utils/std/enum.h"
#include "SettingsReader.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(GeometryDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeNormal = 1,
	VertexAttributeTangen = 2,
	VertexAttributeUv = 3,
	//
	FragmentUniformMatrixMvp = 0,
	FragmentUniformMatrixNormal = 1,
	FragmentUniformMapNormal = 2
};

GeometryDemo::GeometryDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(),
	mTexture(),
	mSquare(),
	mSettings(nullptr)
{
}

GeometryDemo::~GeometryDemo()
{
}

void GeometryDemo::Initialize()
{
	if (!eps::rendering::load_program("assets/shaders/techniques/geometry.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

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
}

void GeometryDemo::Draw(const Library::GameTime&)
{
	GLuint colorTexture = (*eps::utils::ptr_product(mTexture.get_product()));
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	//
	EPS_STATE_PROGRAM(mProgram.get_product());
	//
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformMatrixMvp), mSettings->mMatrixMvp);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformMatrixNormal), mSettings->mMatrixNormal);
	//
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition), eps::utils::to_int(VertexAttributeUv));
}

}
