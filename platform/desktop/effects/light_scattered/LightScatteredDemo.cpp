
#include "LightScatteredDemo.h"
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
	mProgram(),
	mSquare(),
	mTexture(),
	mExposure(),
	mDecay(),
	mDensity(),
	mWeight(),
	mLightPosition()
{
}

LightScatteredDemo::~LightScatteredDemo()
{
}

void LightScatteredDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("assets/shaders/effects/light_scattered.prog", mProgram))
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
//	bool settingLoaded = load_data("settings/effects/light_scattered.xml", settings);
	//
	mExposure = 1.0f;
	mDecay = 1.0f;
	mDensity = 1.0f;
	mWeight = 1.0f;
	mLightPosition = eps::math::vec2(1.0f, 1.0f);
}

void LightScatteredDemo::Draw(const Library::GameTime&)
{
	GLuint colorTexture = (*eps::utils::ptr_product(mTexture.get_product()));
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	//
	EPS_STATE_PROGRAM(mProgram.get_product());
	//
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformOccluding), 0);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformExposure), mExposure);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformDecay), mDecay);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformDensity), mDensity);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformWeight), mWeight);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformLightPosition), mLightPosition);
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition),
				   eps::utils::to_int(VertexAttributeTextureCoordinate));
}

}
