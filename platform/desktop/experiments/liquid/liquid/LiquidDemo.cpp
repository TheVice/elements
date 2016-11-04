
#include "LiquidDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/core/texture_maker.h"
#include "rendering/core/texture_policy.h"
#include "rendering/passes/pass_base.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "TestCard.h"

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

LiquidDemo::LiquidDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mTexture(nullptr),
	mSquare(nullptr),
	mSurfaceColor(),
	mSurfaceTexel(),
	mColorTexture(0)
{
}

LiquidDemo::~LiquidDemo()
{
}

bool LiquidDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	mTexture = eps::utils::make_unique<eps::rendering::texture>();
	mSquare = eps::utils::make_unique<eps::rendering::primitive::square>();

	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/experiments/liquid/liquid.prog", (*mProgram.get())))
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
	mSurfaceColor = { 0.33f, 0.098f, 0.38f, 0.44f };
	mSurfaceTexel.x = 1.0f / size.x;
	mSurfaceTexel.y = 1.0f / size.y;
	//
	return true;
}

void LiquidDemo::Update()
{
}

void LiquidDemo::Draw()
{
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(eps::rendering::pass_slot::slot_0));
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(eps::rendering::pass_slot::slot_1));
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformSurface), 0);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformBackground), 1);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformColor), mSurfaceColor);
	mProgram->uniform_value(eps::utils::to_int(FragmentUniformTexel), mSurfaceTexel);
	mSquare->render((*mProgram.get()), eps::utils::to_int(VertexAttributePosition),
					eps::utils::to_int(VertexAttributeTextureCoordinate));
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
