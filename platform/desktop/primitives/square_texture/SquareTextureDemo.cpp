
#include "SquareTextureDemo.h"
#include "SquareTextureEffect.h"
#include "SquareTextureUi.h"
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
RTTI_DEFINITIONS(SquareTextureDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_source = 0,
	u_transform = 1
};

SquareTextureDemo::SquareTextureDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mSquareTextureProgram(nullptr),
	mSquareTextureEffect(nullptr),
	u_source(nullptr),
	mSquareTextureSettings(),
	mSquareTextureUi(nullptr)
{
}

SquareTextureDemo::~SquareTextureDemo() = default;

bool SquareTextureDemo::Initialize()
{
	// Build the shader program
	mSquareTextureProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/primitives/square_texture.prog";

	if (!eps::rendering::load_program(assetPath, (*mSquareTextureProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/primitives/square_texture.xml";
	mSquareTextureSettings = eps::assets_storage::instance().read<SquareTextureSettings>(assetPath);

	if (!mSquareTextureSettings || mSquareTextureSettings->mIsEmpty)
	{
		return false;
	}

	u_source = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mSquareTextureSettings->u_source, (*u_source.get()))
	// Create the effect
	mSquareTextureEffect = eps::utils::make_unique<SquareTextureEffect>(mSquareTextureSettings->mVertices,
						   mSquareTextureSettings->mIndices,
						   eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mSquareTextureUi = static_cast<Rendering::SquareTextureUi*>(mGame->GetServices().GetService(
						   Rendering::SquareTextureUi::TypeIdClass()));
	assert(mSquareTextureUi);
	return mSquareTextureUi != nullptr;
}

void SquareTextureDemo::Update()
{
	if (mSquareTextureUi->IsNeedRestore())
	{
		mSquareTextureUi->Set_u_transform(mSquareTextureSettings->u_transform);
		mSquareTextureUi->SetVertices(mSquareTextureSettings->mVertices);
	}
}

void SquareTextureDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_source->get_product()));
	//
	EPS_STATE_PROGRAM(mSquareTextureProgram->get_product());
	//
	mSquareTextureProgram->uniform_value(eps::utils::to_int(program_enum::u_transform),
										 mSquareTextureUi->Get_u_transform());
	//
	mSquareTextureEffect->construct(mSquareTextureUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mSquareTextureEffect->render(*mSquareTextureProgram.get(), attributes,
								 mSquareTextureSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
