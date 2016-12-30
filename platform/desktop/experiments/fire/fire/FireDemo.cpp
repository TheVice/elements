
#include "FireDemo.h"
#include "FireEffect.h"
#include "FireUi.h"
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
RTTI_DEFINITIONS(FireDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_fire = 0,
	u_background = 1,
	u_texel = 2
};

FireDemo::FireDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mFireProgram(nullptr),
	mFireEffect(nullptr),
	u_fire(nullptr),
	u_background(nullptr),
	mFireSettings(),
	mFireUi(nullptr)
{
}

FireDemo::~FireDemo() = default;

bool FireDemo::Initialize()
{
	// Build the shader program
	mFireProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/fire/fire.prog";

	if (!eps::rendering::load_program(assetPath, (*mFireProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/fire/fire.xml";
	mFireSettings = eps::assets_storage::instance().read<FireSettings>(assetPath);

	if (!mFireSettings || mFireSettings->mIsEmpty)
	{
		return false;
	}

	u_fire = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mFireSettings->u_fire, (*u_fire.get()))
	u_background = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mFireSettings->u_background, (*u_background.get()))
	// Create the effect
	mFireEffect = eps::utils::make_unique<FireEffect>(mFireSettings->mVertices, mFireSettings->mIndices,
				  eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mFireUi = static_cast<Rendering::FireUi*>(mGame->GetServices().GetService(
				  Rendering::FireUi::TypeIdClass()));
	assert(mFireUi);
	return mFireUi != nullptr;
}

void FireDemo::Update()
{
	if (mFireUi->IsNeedRestore())
	{
		mFireUi->Set_u_texel(mFireSettings->u_texel);
		//
		mFireUi->SetVertices(mFireSettings->mVertices);
	}
}

void FireDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_fire->get_product()));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_background->get_product()));
	//
	EPS_STATE_PROGRAM(mFireProgram->get_product());
	//
	mFireProgram->uniform_value(eps::utils::to_int(program_enum::u_texel), mFireUi->Get_u_texel());
	//
	mFireEffect->construct(mFireUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mFireEffect->render(*mFireProgram.get(), attributes, mFireSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

