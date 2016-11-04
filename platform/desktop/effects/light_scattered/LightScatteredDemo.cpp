
#include "LightScatteredDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "utils/std/enum.h"
#include "SettingsReader.h"
#include "TestCard.h"

namespace Rendering
{
RTTI_DEFINITIONS(LightScatteredDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformOccluding = 0,
	FragmentUniformExposure = 1,
	FragmentUniformDecay = 2,
	FragmentUniformDensity = 3,
	FragmentUniformWeight = 4,
	FragmentUniformLightPosition = 5
};

LightScatteredDemo::LightScatteredDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mTexture(nullptr),
	mSquare(nullptr),
	mExposure(0.0f),
	mDecay(0.0f),
	mDensity(0.0f),
	mWeight(0.0f),
	mLightPosition(),
	mColorTexture(0),
	rate_(60)
{
}

LightScatteredDemo::~LightScatteredDemo()
{
}

bool LightScatteredDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mTexture = eps::utils::make_unique<eps::rendering::texture>();
	mSquare = eps::utils::make_unique<eps::rendering::primitive::square>();

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/effects/light_scattered.prog", *mProgram.get()))
	{
		return false;
	}

	// Load the texture
	glm::uvec2 texture_size = size;
	auto texture_data = eps::utils::make_unique<GLubyte[]>(4 * texture_size.x * texture_size.y);
	Library::MakeColorBars(texture_data.get(), texture_size.x, texture_size.y);
	//
	auto maker = eps::rendering::get_texture_maker<eps::rendering::default_texture_policy>();
	(*mTexture.get()) = maker.construct(texture_data.get(), size);
	mColorTexture = (*eps::utils::ptr_product(mTexture->get_product()));
	//
	mExposure = 1.0f;
	mDecay = 1.0f;
	mDensity = 1.0f;
	mWeight = 1.0f;
	mLightPosition = eps::math::vec2(1.0f, 1.0f);
	//
	return true;
}

void LightScatteredDemo::Update()
{
	static float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		const float elapsedTime = rate_.elapsed() - lastTime;
		lastTime = rate_.elapsed();

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_UP) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_W))
		{
			mLightPosition.y = std::min(1.0f, mLightPosition.y + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_DOWN) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_S))
		{
			mLightPosition.y = std::max(-1.0f, mLightPosition.y - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_LEFT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_A))
		{
			mLightPosition.x = std::max(-1.0f, mLightPosition.x - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_RIGHT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_D))
		{
			mLightPosition.x = std::min(1.0f, mLightPosition.x + 0.0125f * elapsedTime);
		}
	}
}

void LightScatteredDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mColorTexture);
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformOccluding), 0);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformExposure), mExposure);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformDecay), mDecay);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformDensity), mDensity);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformWeight), mWeight);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformLightPosition), mLightPosition);
	mSquare->render((*mProgram.get()), eps::utils::to_int(VertexAttributePosition),
					eps::utils::to_int(VertexAttributeTextureCoordinate));
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
