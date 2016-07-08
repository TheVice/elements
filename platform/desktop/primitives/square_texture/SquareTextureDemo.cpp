
#include "SquareTextureDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "utils/std/enum.h"
#include "TestCard.h"
#include "Game.h"

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

SquareTextureDemo::SquareTextureDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mProgram(),
	  mSquare(),
	  mTexture(),
	  mTransform()
{
}

SquareTextureDemo::~SquareTextureDemo()
{
}

void SquareTextureDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("shaders/primitives/square_texture.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	GLenum texture_format = GL_RGBA;
	glm::uvec2 texture_size = size;
	auto texture_data = std::make_unique<GLubyte[]>(4 * texture_size.x * texture_size.y);
	MakeColorBars(texture_data.get(), texture_size.x, texture_size.y);
	mTexture.set_data(texture_data.get(), texture_size, texture_format);
}

void SquareTextureDemo::Draw(const Library::GameTime&)
{
	GLuint colorTexture = (*eps::utils::ptr_product(mTexture.get_product()));
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	//
	EPS_STATE_PROGRAM(mProgram.get_product());
	//
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformSource), 0);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition),
				   eps::utils::to_int(VertexAttributeTextureCoordinate));
}

}
