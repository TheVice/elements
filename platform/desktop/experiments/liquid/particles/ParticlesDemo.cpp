
#include "ParticlesDemo.h"
#include "ParticlesEffect.h"
#include "ParticlesUi.h"
#include <elements/rendering/core/program.h>
#include <elements/rendering/state/state_macro.h>
#include <elements/rendering/utils/program_loader.h>
#include <elements/assets/assets_storage.h>
#include <elements/utils/std/enum.h>
#include <elements/utils/std/product.h>
#include <Game.h>

namespace Rendering
{
RTTI_DEFINITIONS(ParticlesDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	// uniforms
	u_transform = 0,
	u_size = 1
};

ParticlesDemo::ParticlesDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mParticlesEffect(nullptr),
	mParticlesSettings(),
	mParticlesUi(nullptr)
{
}

ParticlesDemo::~ParticlesDemo() = default;

bool ParticlesDemo::Initialize()
{
	// Build the shader program
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/liquid/particles.prog";

	if (!eps::rendering::load_program(assetPath, (*mProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/liquid/particles.xml";
	mParticlesSettings = eps::assets_storage::instance().read<ParticlesSettings>(assetPath);

	if (!mParticlesSettings || mParticlesSettings->mIsEmpty)
	{
		return false;
	}

	// Create the effect
	mParticlesEffect = eps::utils::make_unique<ParticlesEffect>(mParticlesSettings->mVertices,
					   mParticlesSettings->mIndices, eps::rendering::buffer_usage::STREAM_DRAW);
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
		mParticlesUi->Set_u_transform(mParticlesSettings->u_transform);
		mParticlesUi->Set_u_size(mParticlesSettings->u_size);
		mParticlesUi->SetVertices(mParticlesSettings->mVertices);
		mParticlesUi->SetCheckBoxState(glIsEnabled(GL_POINT_SPRITE), glIsEnabled(GL_VERTEX_PROGRAM_POINT_SIZE));
	}

	if (mParticlesUi->IsPointSpriteEnabled())
	{
		glEnable(GL_POINT_SPRITE);
	}
	else
	{
		glDisable(GL_POINT_SPRITE);
	}

	if (mParticlesUi->IsVertexProgramPointSizeEnabled())
	{
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	}
	else
	{
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	}
}

void ParticlesDemo::Draw()
{
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_transform), mParticlesUi->Get_u_transform());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_size), mParticlesUi->Get_u_size());
	//
	mParticlesEffect->construct(mParticlesUi->GetVertices());
	//
	mParticlesEffect->render(*mProgram.get(), eps::utils::to_int(program_enum::a_vertex_xy),
							 mParticlesSettings->mIndices.size());
}

}
