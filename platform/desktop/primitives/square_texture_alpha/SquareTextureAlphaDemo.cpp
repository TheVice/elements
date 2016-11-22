
#include "SquareTextureAlphaDemo.h"
#include "SettingsReader.h"
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/rendering/core/texture_maker.h>
#include <elements/rendering/core/texture_policy.h>
#include <elements/utils/std/enum.h>
#include <TestCard.h>
#include <Game.h>
#include <algorithm>

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
	mProgram(nullptr),
	mTexture(nullptr),
	mSquare(nullptr),
	mTransform(),
	mColor(),
	mColorTexture(0),
	rate_(60)
{
}

SquareTextureAlphaDemo::~SquareTextureAlphaDemo()
{
}

bool SquareTextureAlphaDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mTexture = eps::utils::make_unique<eps::rendering::texture>();
	mSquare = eps::utils::make_unique<eps::rendering::primitive::square>();

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/primitives/square_texture_alpha.prog", (*mProgram.get())))
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
	//	SettingsReader settings;
	//	bool settingLoaded = load_data("settings/primitives/square_texture_alpha.xml", settings);
	//
	mTransform = eps::math::mat4();
	mColor = eps::math::vec4(0.1f, 0.1f, 0.1f, 0.1f);
	//
	return true;
}

void SquareTextureAlphaDemo::Update()
{
	float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		const float elapsedTime = rate_.elapsed() - lastTime;

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_Z))
		{
			mColor.r = std::max(0.0f, mColor.r - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_X))
		{
			mColor.r = std::min(1.0f, mColor.r + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_C))
		{
			mColor.g = std::max(0.0f, mColor.g - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_V))
		{
			mColor.g = std::min(1.0f, mColor.g + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_B))
		{
			mColor.b = std::max(0.0f, mColor.b - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_N))
		{
			mColor.b = std::min(1.0f, mColor.b + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_M))
		{
			mColor.a = std::max(0.0f, mColor.a - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_COMMA))
		{
			mColor.a = std::min(1.0f, mColor.a + 0.0125f * elapsedTime);
		}
	}
}

void SquareTextureAlphaDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mColorTexture);
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformSource), 0);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformColor), mColor);
	mSquare->render((*mProgram.get()), eps::utils::to_int(VertexAttributePosition),
					eps::utils::to_int(VertexAttributeTextureCoordinate));
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
