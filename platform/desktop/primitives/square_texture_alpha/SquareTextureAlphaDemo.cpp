
#include "SquareTextureAlphaDemo.h"
#include "SquareTextureAlphaEffect.h"
#include "SquareTextureAlphaUi.h"
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
RTTI_DEFINITIONS(SquareTextureAlphaDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_source = 0,
	u_transform = 1,
	u_color = 2
};

SquareTextureAlphaDemo::SquareTextureAlphaDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mSquareTextureAlphaProgram(nullptr),
	mSquareTextureAlphaEffect(nullptr),
	u_source(nullptr),
	mSquareTextureAlphaSettings(),
	mSquareTextureAlphaUi(nullptr)
{
}

SquareTextureAlphaDemo::~SquareTextureAlphaDemo() = default;

bool SquareTextureAlphaDemo::Initialize()
{
	// Build the shader program
	mSquareTextureAlphaProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/primitives/square_texture_alpha.prog";

	if (!eps::rendering::load_program(assetPath, (*mSquareTextureAlphaProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/primitives/square_texture_alpha.xml";
	mSquareTextureAlphaSettings = eps::assets_storage::instance().read<SquareTextureAlphaSettings>(assetPath);

	if (!mSquareTextureAlphaSettings || mSquareTextureAlphaSettings->mIsEmpty)
	{
		return false;
	}

	u_source = eps::utils::make_unique<eps::rendering::texture>();
	LOAD_TEXTURE(mSquareTextureAlphaSettings->u_source, (*u_source.get()))
	// Create the effect
	mSquareTextureAlphaEffect = eps::utils::make_unique<SquareTextureAlphaEffect>
								(mSquareTextureAlphaSettings->mVertices, mSquareTextureAlphaSettings->mIndices,
								 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mSquareTextureAlphaUi = static_cast<Rendering::SquareTextureAlphaUi*>(mGame->GetServices().GetService(
								Rendering::SquareTextureAlphaUi::TypeIdClass()));
	assert(mSquareTextureAlphaUi);
	return mSquareTextureAlphaUi != nullptr;
}

void SquareTextureAlphaDemo::Update()
{
	if (mSquareTextureAlphaUi->IsNeedRestore())
	{
		mSquareTextureAlphaUi->Set_u_transform(mSquareTextureAlphaSettings->u_transform);
		mSquareTextureAlphaUi->Set_u_color(mSquareTextureAlphaSettings->u_color);
		//
		mSquareTextureAlphaUi->SetVertices(mSquareTextureAlphaSettings->mVertices);
	}
}

void SquareTextureAlphaDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(u_source->get_product()));
	//
	EPS_STATE_PROGRAM(mSquareTextureAlphaProgram->get_product());
	//
	mSquareTextureAlphaProgram->uniform_value(eps::utils::to_int(program_enum::u_transform),
			mSquareTextureAlphaUi->Get_u_transform());
	mSquareTextureAlphaProgram->uniform_value(eps::utils::to_int(program_enum::u_color),
			mSquareTextureAlphaUi->Get_u_color());
	//
	mSquareTextureAlphaEffect->construct(mSquareTextureAlphaUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mSquareTextureAlphaEffect->render(*mSquareTextureAlphaProgram.get(), attributes,
									  mSquareTextureAlphaSettings->mIndices.size());
	//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
