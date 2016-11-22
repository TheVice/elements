
#include "MetaballsDemo.h"
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/rendering/core/texture_maker.h>
#include <elements/rendering/core/texture_policy.h>
#include <elements/rendering/passes/pass_base.h>
#include <elements/utils/std/enum.h>
#include <elements/math/transform.h>
#include <elements/assets/asset_texture.h>
#include <elements/assets/assets_storage.h>
#include <TestCard.h>
#include <Game.h>

namespace Rendering
{
RTTI_DEFINITIONS(MetaballsDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformSurface = 0
};

MetaballsDemo::MetaballsDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mTexture(nullptr),
	mSquare(nullptr),
	mColorTexture(0)
{
}

MetaballsDemo::~MetaballsDemo()
{
}

bool MetaballsDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mTexture = eps::utils::make_unique<eps::rendering::texture>();
	mSquare = eps::utils::make_unique<eps::rendering::primitive::square>();

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/experiments/liquid/metaballs.prog", (*mProgram.get())))
	{
		return false;
	}

	// Load the texture
	glm::uvec2 texture_size = size;
	auto texture_data = eps::utils::make_unique<GLubyte[]>(4 * texture_size.x * texture_size.y);
	Library::TestCard::MakeColorBars(texture_data.get(), texture_size.x, texture_size.y);
	//
	auto maker = eps::rendering::get_texture_maker<eps::rendering::default_texture_policy>();
	(*mTexture.get()) = maker.construct(texture_data.get(), size);
	mColorTexture = (*eps::utils::ptr_product(mTexture->get_product()));
	//
	return true;
}

void MetaballsDemo::Update()
{
}

void MetaballsDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mColorTexture);
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformSurface), 0);
	mSquare->render((*mProgram.get()), eps::utils::to_int(VertexAttributePosition),
					eps::utils::to_int(VertexAttributeTextureCoordinate));
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
