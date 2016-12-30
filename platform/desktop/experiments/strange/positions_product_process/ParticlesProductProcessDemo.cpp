
#include "ParticlesProductProcessDemo.h"
#include "ParticlesProductProcessEffect.h"
#include "ParticlesProductProcessUi.h"
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
RTTI_DEFINITIONS(ParticlesProductProcessDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	// uniforms
	u_attractor_a = 0,
	u_attractor_b = 1,
	u_attractor_c = 2,
	u_attractor_d = 3
};

ParticlesProductProcessDemo::ParticlesProductProcessDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mParticlesProductProcessProgram(nullptr),
	mParticlesProductProcessEffect(nullptr),
	mParticlesProductProcessSettings(),
	mParticlesProductProcessUi(nullptr)
{
}

ParticlesProductProcessDemo::~ParticlesProductProcessDemo() = default;

bool ParticlesProductProcessDemo::Initialize()
{
	// Build the shader program
	mParticlesProductProcessProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/strange/positions_product_process.prog";

	if (!eps::rendering::load_program(assetPath, (*mParticlesProductProcessProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/strange/positions_product_process.xml";
	mParticlesProductProcessSettings = eps::assets_storage::instance().read<ParticlesProductProcessSettings>
									   (assetPath);

	if (!mParticlesProductProcessSettings || mParticlesProductProcessSettings->mIsEmpty)
	{
		return false;
	}

	// Create the effect
	mParticlesProductProcessEffect = eps::utils::make_unique<ParticlesProductProcessEffect>
									 (mParticlesProductProcessSettings->mVertices, mParticlesProductProcessSettings->mIndices,
									  eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mParticlesProductProcessUi = static_cast<Rendering::ParticlesProductProcessUi*>
								 (mGame->GetServices().GetService(
									  Rendering::ParticlesProductProcessUi::TypeIdClass()));
	assert(mParticlesProductProcessUi);
	return mParticlesProductProcessUi != nullptr;
}

void ParticlesProductProcessDemo::Update()
{
	if (mParticlesProductProcessUi->IsNeedRestore())
	{
		mParticlesProductProcessUi->Set_u_attractor_a(mParticlesProductProcessSettings->u_attractor_a);
		mParticlesProductProcessUi->Set_u_attractor_b(mParticlesProductProcessSettings->u_attractor_b);
		mParticlesProductProcessUi->Set_u_attractor_c(mParticlesProductProcessSettings->u_attractor_c);
		mParticlesProductProcessUi->Set_u_attractor_d(mParticlesProductProcessSettings->u_attractor_d);
		//
		mParticlesProductProcessUi->SetVertices(mParticlesProductProcessSettings->mVertices);
	}
}

void ParticlesProductProcessDemo::Draw()
{
	EPS_STATE_PROGRAM(mParticlesProductProcessProgram->get_product());
	//
	mParticlesProductProcessProgram->uniform_value(eps::utils::to_int(program_enum::u_attractor_a),
			mParticlesProductProcessUi->Get_u_attractor_a());
	mParticlesProductProcessProgram->uniform_value(eps::utils::to_int(program_enum::u_attractor_b),
			mParticlesProductProcessUi->Get_u_attractor_b());
	mParticlesProductProcessProgram->uniform_value(eps::utils::to_int(program_enum::u_attractor_c),
			mParticlesProductProcessUi->Get_u_attractor_c());
	mParticlesProductProcessProgram->uniform_value(eps::utils::to_int(program_enum::u_attractor_d),
			mParticlesProductProcessUi->Get_u_attractor_d());
	//
	mParticlesProductProcessEffect->construct(mParticlesProductProcessUi->GetVertices());
	mParticlesProductProcessEffect->render(*mParticlesProductProcessProgram.get(),
										   eps::utils::to_int(program_enum::a_vertex_xy), mParticlesProductProcessSettings->mIndices.size());
}

}

