
#include "SquareTextureAlphaDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "utils/std/enum.h"
#include "SettingsReader.h"
#include "TestCard.h"
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(SquareTextureAlphaDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformSource = 0,
	FragmentUniformTransformation = 1,
	FragmentUniformColor = 2
};

SquareTextureAlphaDemo::SquareTextureAlphaDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(),
	mSquare(),
	mTexture(),
	mTransform(),
	mColor()
{
}

SquareTextureAlphaDemo::~SquareTextureAlphaDemo()
{
}

void SquareTextureAlphaDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("assets/shaders/primitives/square_texture_alpha.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	glm::uvec2 texture_size = size;
	auto texture_data = std::make_unique<GLubyte[]>(4 * texture_size.x * texture_size.y);
	Library::MakeColorBars(texture_data.get(), texture_size.x, texture_size.y);
	//
	auto maker = eps::rendering::get_texture_maker<eps::rendering::default_texture_policy>();
	mTexture = maker.construct(texture_data.get(), size);
	//
//	SettingsReader settings;
//	bool settingLoaded = load_data("settings/primitives/square_texture_alpha.xml", settings);
	//
	mTransform = eps::math::mat4();
	mColor = eps::math::vec4(0.1f, 0.1f, 0.1f, 0.1f);
}

void SquareTextureAlphaDemo::Draw(const Library::GameTime&)
{
	GLuint colorTexture = (*eps::utils::ptr_product(mTexture.get_product()));
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	//
	EPS_STATE_PROGRAM(mProgram.get_product());
	//
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformSource), 0);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformColor), mColor);
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition),
				   eps::utils::to_int(VertexAttributeTextureCoordinate));
}

}
