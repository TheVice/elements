
#include "ParticlesDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/passes/pass_base.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "SettingsReader.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(ParticlesDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	//
	FragmentUniformTransformation = 0,
	FragmentUniformSize = 1
};

ParticlesDemo::ParticlesDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mProgram(),
	  mSquare(),
	  mTransform(),
	  mSize()
{
}

ParticlesDemo::~ParticlesDemo()
{
}

void ParticlesDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("shaders/experiments/liquid/particles.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	SettingsReader settings;
	bool settingLoaded = load_data("settings/experiments/liquid/particles.xml", settings);
	//
	glm::vec2 pos = settingLoaded ? settings.mPosition : glm::vec2(1.0f, 0.0f);
	float offset = size.y * 0.5f;
	glm::vec2 tracker(pos.x + (size.x - offset) * 0.5f, pos.y + (size.y - offset) * 0.5f);
	GLfloat vertices[] =
	{
		(tracker.x), (tracker.y),          0.0f, 1.0f,
		(tracker.x + offset), (tracker.y),          1.0f, 1.0f,
		(tracker.x + offset), (tracker.y + offset), 1.0f, 0.0f,
		(tracker.x), (tracker.y + offset), 0.0f, 0.0f
	};
	mSquare.construct(vertices);
	mTransform = eps::math::translate(-1.0f, -1.0f, 0.0f) *
				 eps::math::scale(2.0f, 2.0f, 1.0f) *
				 eps::math::scale(1.0f / size.x, 1.0f / size.y, 1.0f);
	mSize = settingLoaded ? settings.mSize : 10.0f;
}

void ParticlesDemo::Draw(const Library::GameTime&)
{
	EPS_STATE_PROGRAM(mProgram.get_product());
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformSize), mSize);
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition));
}

}
