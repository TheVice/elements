
#include "MetaballDemo.h"
#include "MetaballEffect.h"
#include "MetaballUi.h"
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
RTTI_DEFINITIONS(MetaballDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_source = 0
};

MetaballDemo::MetaballDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mMetaballProgram(nullptr),
	mMetaballEffect(nullptr),
	u_source(nullptr),
	mMetaballSettings(),
	mMetaballUi(nullptr)
{
}

MetaballDemo::~MetaballDemo() = default;

bool MetaballDemo::Initialize()
{
	// Build the shader program
	mMetaballProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/experiments/liquid/metaballs.prog";

	if (!eps::rendering::load_program(assetPath, (*mMetaballProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/experiments/liquid/metaballs.xml";
	mMetaballSettings = eps::assets_storage::instance().read<MetaballSettings>(assetPath);

	if (!mMetaballSettings || mMetaballSettings->mIsEmpty)
	{
		return false;
	}

	u_source = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mMetaballSettings->u_source, (*u_source.get()))
	// Create the effect
	mMetaballEffect = eps::utils::make_unique<MetaballEffect>(mMetaballSettings->mVertices,
					  mMetaballSettings->mIndices,
					  eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mMetaballUi = static_cast<Rendering::MetaballUi*>(mGame->GetServices().GetService(
					  Rendering::MetaballUi::TypeIdClass()));
	assert(mMetaballUi);
	return mMetaballUi != nullptr;
}

void MetaballDemo::Update()
{
	if (mMetaballUi->IsNeedRestore())
	{
		//
		mMetaballUi->SetVertices(mMetaballSettings->mVertices);
	}
}

void MetaballDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_source->get_product()));
	//
	EPS_STATE_PROGRAM(mMetaballProgram->get_product());
	//
	//
	mMetaballEffect->construct(mMetaballUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mMetaballEffect->render(*mMetaballProgram.get(), attributes, mMetaballSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
