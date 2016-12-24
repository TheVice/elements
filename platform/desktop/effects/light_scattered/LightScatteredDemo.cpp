
#include "LightScatteredDemo.h"
#include "LightScatteredEffect.h"
#include "LightScatteredUi.h"
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
RTTI_DEFINITIONS(LightScatteredDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_occluding = 0,
	u_exposure = 1,
	u_decay = 2,
	u_density = 3,
	u_weight = 4,
	u_light_position = 5
};

LightScatteredDemo::LightScatteredDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mLightScatteredProgram(nullptr),
	mLightScatteredEffect(nullptr),
	u_occluding(nullptr),
	mLightScatteredSettings(),
	mLightScatteredUi(nullptr)
{
}

LightScatteredDemo::~LightScatteredDemo() = default;

bool LightScatteredDemo::Initialize()
{
	// Build the shader program
	mLightScatteredProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/effects/light_scattered.prog";

	if (!eps::rendering::load_program(assetPath, (*mLightScatteredProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/effects/light_scattered.xml";
	mLightScatteredSettings = eps::assets_storage::instance().read<LightScatteredSettings>(assetPath);

	if (!mLightScatteredSettings || mLightScatteredSettings->mIsEmpty)
	{
		return false;
	}

	u_occluding = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mLightScatteredSettings->u_occluding, (*u_occluding.get()))
	// Create the effect
	mLightScatteredEffect = eps::utils::make_unique<LightScatteredEffect>(mLightScatteredSettings->mVertices,
							mLightScatteredSettings->mIndices,
							eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mLightScatteredUi = static_cast<Rendering::LightScatteredUi*>(mGame->GetServices().GetService(
							Rendering::LightScatteredUi::TypeIdClass()));
	assert(mLightScatteredUi);
	return mLightScatteredUi != nullptr;
}

void LightScatteredDemo::Update()
{
	if (mLightScatteredUi->IsNeedRestore())
	{
		mLightScatteredUi->Set_u_exposure(mLightScatteredSettings->u_exposure);
		mLightScatteredUi->Set_u_decay(mLightScatteredSettings->u_decay);
		mLightScatteredUi->Set_u_density(mLightScatteredSettings->u_density);
		mLightScatteredUi->Set_u_weight(mLightScatteredSettings->u_weight);
		mLightScatteredUi->Set_u_light_position(mLightScatteredSettings->u_light_position);
		//
		mLightScatteredUi->SetVertices(mLightScatteredSettings->mVertices);
	}
}

void LightScatteredDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_occluding->get_product()));
	//
	EPS_STATE_PROGRAM(mLightScatteredProgram->get_product());
	//
	mLightScatteredProgram->uniform_value(eps::utils::to_int(program_enum::u_exposure),
										  mLightScatteredUi->Get_u_exposure());
	mLightScatteredProgram->uniform_value(eps::utils::to_int(program_enum::u_decay),
										  mLightScatteredUi->Get_u_decay());
	mLightScatteredProgram->uniform_value(eps::utils::to_int(program_enum::u_density),
										  mLightScatteredUi->Get_u_density());
	mLightScatteredProgram->uniform_value(eps::utils::to_int(program_enum::u_weight),
										  mLightScatteredUi->Get_u_weight());
	mLightScatteredProgram->uniform_value(eps::utils::to_int(program_enum::u_light_position),
										  mLightScatteredUi->Get_u_light_position());
	//
	mLightScatteredEffect->construct(mLightScatteredUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mLightScatteredEffect->render(*mLightScatteredProgram.get(), attributes,
								  mLightScatteredSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
