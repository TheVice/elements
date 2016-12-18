
#include "SquareTextureDemo.h"
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/rendering/core/texture_maker.h>
#include <elements/rendering/core/texture_policy.h>
#include <elements/utils/std/enum.h>
#include <TestCard.h>
#include <Game.h>

namespace Rendering
{
RTTI_DEFINITIONS(SquareTextureDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformSource = 0,
	FragmentUniformTransformation = 1,
};

SquareTextureDemo::SquareTextureDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mTexture(nullptr),
	mSquare(nullptr),
	mTransform(),
	mColorTexture(0)
{
}

SquareTextureDemo::~SquareTextureDemo()
{
}

bool SquareTextureDemo::Initialize()
{
	const glm::uvec2 texture_size(1920, 1080);//(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mTexture = eps::utils::make_unique<eps::rendering::texture>();
	mSquare = eps::utils::make_unique<eps::rendering::primitive::square>();

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/primitives/square_texture.prog", (*mProgram.get())))
	{
		return false;
	}

	// Load the texture
	auto texture_data = eps::utils::make_unique<GLubyte[]>(4 * texture_size.x * texture_size.y);
	Library::TestCard::MakeSmpteColorBarsHD(texture_data.get(), texture_size.x, texture_size.y);
	//
	auto maker = eps::rendering::get_texture_maker<eps::rendering::default_texture_policy>();
	(*mTexture.get()) = maker.construct(texture_data.get(), texture_size);
	mColorTexture = eps::utils::raw_product(mTexture->get_product());
	//
	return true;
}

void SquareTextureDemo::Update()
{
}

void SquareTextureDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mColorTexture);
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformSource), 0);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mSquare->render((*mProgram.get()), eps::utils::to_int(VertexAttributePosition),
					eps::utils::to_int(VertexAttributeTextureCoordinate));
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
