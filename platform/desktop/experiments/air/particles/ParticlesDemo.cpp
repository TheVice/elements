
#include "ParticlesDemo.h"
#include "ParticlesEffect.h"
#include "ParticlesUi.h"
#include <TextureLoader.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/core/texture.h>
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/core/texture_maker.h>
#include <elements/rendering/core/texture_policy.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/assets/asset_texture.h>
#include <elements/assets/assets_storage.h>
#include <elements/utils/std/enum.h>
#include <elements/utils/std/product.h>
#include <Game.h>
#include <array>

namespace Rendering
{
RTTI_DEFINITIONS(ParticlesDemo)

enum class program_enum : short
{
	// attributes
	a_product_uv = 0,
	// uniforms
	u_positions = 0,
	u_velocities = 1,
	u_color_speed_down = 2,
	u_color_speed_up = 3
};

ParticlesDemo::ParticlesDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mParticlesProgram(nullptr),
	mParticlesEffect(nullptr),
	u_positions(nullptr),
	u_velocities(nullptr),
	mParticlesSettings(),
	mParticlesUi(nullptr)
{
}

ParticlesDemo::~ParticlesDemo() = default;

bool ParticlesDemo::Initialize()
{
	// Build the shader program
	mParticlesProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/air/particles.prog";

	if (!eps::rendering::load_program(assetPath, (*mParticlesProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/air/particles.xml";
	mParticlesSettings = eps::assets_storage::instance().read<ParticlesSettings>(assetPath);

	if (!mParticlesSettings || mParticlesSettings->mIsEmpty)
	{
		return false;
	}

	u_positions = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mParticlesSettings->u_positions, (*u_positions.get()))
	u_velocities = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mParticlesSettings->u_velocities, (*u_velocities.get()))
	// Create the effect
	mParticlesEffect = eps::utils::make_unique<ParticlesEffect>(mParticlesSettings->mVertices,
					   mParticlesSettings->mIndices,
					   eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mParticlesUi = static_cast<Rendering::ParticlesUi*>(mGame->GetServices().GetService(
					   Rendering::ParticlesUi::TypeIdClass()));
	assert(mParticlesUi);
	return mParticlesUi != nullptr;
}

void ParticlesDemo::Update()
{
	if (mParticlesUi->IsNeedRestore())
	{
		mParticlesUi->Set_u_color_speed_down(mParticlesSettings->u_color_speed_down);
		mParticlesUi->Set_u_color_speed_up(mParticlesSettings->u_color_speed_up);
		//
		mParticlesUi->SetVertices(mParticlesSettings->mVertices);
	}
}

void ParticlesDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_positions->get_product()));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_velocities->get_product()));
	//
	EPS_STATE_PROGRAM(mParticlesProgram->get_product());
	//
	mParticlesProgram->uniform_value(eps::utils::to_int(program_enum::u_color_speed_down),
									 mParticlesUi->Get_u_color_speed_down());
	mParticlesProgram->uniform_value(eps::utils::to_int(program_enum::u_color_speed_up),
									 mParticlesUi->Get_u_color_speed_up());
	//
	mParticlesEffect->construct(mParticlesUi->GetVertices());
	mParticlesEffect->render(*mParticlesProgram.get(), eps::utils::to_int(program_enum::a_product_uv),
							 mParticlesSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

