
#include "LiquidDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/passes/pass_base.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(LiquidDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	VertexAttributeTextureCoordinate = 1,
	//
	FragmentUniformSurface = 0,
	FragmentUniformBackground = 1,
	FragmentUniformColor = 2,
	FragmentUniformTexel = 3
};

LiquidDemo::LiquidDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mProgram(),
	  mSquare(),
	  mSurfaceBackground(),
	  mSurfaceColor(),
	  mSurfaceTexel()
{
}

LiquidDemo::~LiquidDemo()
{
}

void LiquidDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("shaders/experiments/liquid/liquid.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	mSurfaceColor = { 0.33f, 0.098f, 0.38f, 0.44f };
	mSurfaceTexel.x = 1.0f / size.x;
	mSurfaceTexel.y = 1.0f / size.y;
	eps::asset_texture asset = eps::assets_storage::instance().read<eps::asset_texture>("textures/noise.png");

	if (asset.pixels())
	{
		mSurfaceBackground.set_data(asset.pixels(), asset.size(), asset.format());
	}
	else
	{
		throw std::runtime_error("Failed to load texture");
	}
}

void LiquidDemo::Draw(const Library::GameTime&)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(eps::rendering::pass_input_slot::input_0));
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>
				  (eps::rendering::pass_input_slot::input_1));//mSurfaceBackground.get_product());
	EPS_STATE_PROGRAM(mProgram.get_product());
	mProgram.uniform_value(eps::utils::to_int(ProgramEnum::FragmentUniformSurface), 0);
	mProgram.uniform_value(eps::utils::to_int(ProgramEnum::FragmentUniformBackground), 1);
	mProgram.uniform_value(eps::utils::to_int(ProgramEnum::FragmentUniformColor), mSurfaceColor);
	mProgram.uniform_value(eps::utils::to_int(ProgramEnum::FragmentUniformTexel), mSurfaceTexel);
	mSquare.render(mProgram, eps::utils::to_int(ProgramEnum::VertexAttributePosition),
				   eps::utils::to_int(ProgramEnum::VertexAttributeTextureCoordinate));
}

}
