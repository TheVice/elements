
#include "BlurDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/passes/pass_base.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "utils/std/product.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(BlurDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformSource = 0,
	FragmentUniformOffset = 1
};

BlurDemo::BlurDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mProgram(),
	  mTexture(),
	  mSquare(),
	  mOffset()
{
}

BlurDemo::~BlurDemo()
{
}

void BlurDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/effects/blur.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	// Load the texture
	auto asset = eps::assets_storage::instance().read<eps::asset_texture>("assets/textures/noise.png");

	if (!asset.value().pixels())
	{
		throw std::runtime_error("Failed to load texture");
	}

	mTexture.set_data(asset.value().pixels(), asset.value().size(), asset.value().format());
	//
	mOffset.x = 0.5f;
	mOffset.y = 0.75f;
}

void BlurDemo::Draw(const Library::GameTime&)
{
	GLuint colorTexture = (*eps::utils::ptr_product(mTexture.get_product()));
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	//
	EPS_STATE_PROGRAM(mProgram.get_product());
	//
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformSource), 0);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformOffset), mOffset);
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition),
				   eps::utils::to_int(VertexAttributeTextureCoordinate));
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
