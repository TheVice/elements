
#include "BlurDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "rendering/passes/pass_base.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include <algorithm>

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

BlurDemo::BlurDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mTexture(nullptr),
	mSquare(nullptr),
	mOffset(0.25f, 0.75f),
	mColorTexture(0),
	rate_(60)
{
}

BlurDemo::~BlurDemo()
{
}

bool BlurDemo::Initialize()
{
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mTexture = eps::utils::make_unique<eps::rendering::texture>();
	mSquare = eps::utils::make_unique<eps::rendering::primitive::square>();

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/effects/blur.prog", *mProgram.get()))
	{
		return false;
	}

	// Load the texture
	auto asset = eps::assets_storage::instance().read<eps::asset_texture>("assets/textures/noise.png");

	if (!asset.value().pixels())
	{
		return false;
	}

	auto maker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	(*mTexture.get()) = maker.construct(asset->pixels(), asset->size());
	mColorTexture = (*eps::utils::ptr_product(mTexture->get_product()));
	return true;
}

void BlurDemo::Update()
{
	static float lastTime = rate_.elapsed();

	if (rate_.update() && rate_.elapsed() > lastTime)
	{
		const float elapsedTime = rate_.elapsed() - lastTime;
		lastTime = rate_.elapsed();

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_UP) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_W))
		{
			mOffset.y = std::min(1.0f, mOffset.y + 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_DOWN) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_S))
		{
			mOffset.y = std::max(-1.0f, mOffset.y - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_LEFT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_A))
		{
			mOffset.x = std::max(-1.0f, mOffset.x - 0.0125f * elapsedTime);
		}

		if (glfwGetKey(mGame->GetWindow(), GLFW_KEY_RIGHT) || glfwGetKey(mGame->GetWindow(), GLFW_KEY_D))
		{
			mOffset.x = std::min(1.0f, mOffset.x + 0.0125f * elapsedTime);
		}
	}
}

void BlurDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mColorTexture);
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformSource), 0);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformOffset), mOffset);
	mSquare->render(*mProgram.get(), eps::utils::to_int(VertexAttributePosition),
					eps::utils::to_int(VertexAttributeTextureCoordinate));
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
