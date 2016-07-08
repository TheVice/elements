
#include "LightScatteredDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "utils/std/enum.h"
#include "SettingsReader.h"
#include "TestCard.h"
#include "Game.h"

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

LightScatteredDemo::LightScatteredDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
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

	if (!eps::rendering::load_program("shaders/effects/light_scattered.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	GLenum texture_format = GL_RGBA;
	glm::uvec2 texture_size = size;
	auto texture_data = std::make_unique<GLubyte[]>(4 * texture_size.x * texture_size.y);
	MakeColorBars(texture_data.get(), texture_size.x, texture_size.y);
	mTexture.set_data(texture_data.get(), texture_size, texture_format);
	//
	SettingsReader settings;
	bool settingLoaded = load_data("settings/effects/light_scattered.xml", settings);
	//
	mExposure = settingLoaded ? settings.mExposure : 1.0f;
	mDecay = settingLoaded ? settings.mDecay : 1.0f;
	mDensity = settingLoaded ? settings.mDensity : 1.0f;
	mWeight = settingLoaded ? settings.mWeight : 1.0f;
	mLightPosition = settingLoaded ? settings.mLightPosition : glm::vec2(1.0f, 1.0f);
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
