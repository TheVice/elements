
#include "SquareColorDemo.h"
#include "SquareColorEffect.h"
#include "SquareColorUi.h"
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
RTTI_DEFINITIONS(SquareColorDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_transform = 0,
	u_color = 1
};

SquareColorDemo::SquareColorDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mSquareColorProgram(nullptr),
	mSquareColorEffect(nullptr),
	mSquareColorSettings(),
	mSquareColorUi(nullptr)
{
}

SquareColorDemo::~SquareColorDemo() = default;

bool SquareColorDemo::Initialize()
{
	// Build the shader program
	mSquareColorProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/primitives/square_color.prog";

	if (!eps::rendering::load_program(assetPath, (*mSquareColorProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/primitives/square_color.xml";
	mSquareColorSettings = eps::assets_storage::instance().read<SquareColorSettings>(assetPath);

	if (!mSquareColorSettings || mSquareColorSettings->mIsEmpty)
	{
		return false;
	}

	// Create the effect
	mSquareColorEffect = eps::utils::make_unique<SquareColorEffect>(mSquareColorSettings->mVertices,
						 mSquareColorSettings->mIndices,
						 eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mSquareColorUi = static_cast<Rendering::SquareColorUi*>(mGame->GetServices().GetService(
						 Rendering::SquareColorUi::TypeIdClass()));
	assert(mSquareColorUi);
	return mSquareColorUi != nullptr;
}

void SquareColorDemo::Update()
{
	if (mSquareColorUi->IsNeedRestore())
	{
		mSquareColorUi->Set_u_transform(mSquareColorSettings->u_transform);
		mSquareColorUi->Set_u_color(mSquareColorSettings->u_color);
		//
		mSquareColorUi->SetVertices(mSquareColorSettings->mVertices);
	}
}

void SquareColorDemo::Draw()
{
	EPS_STATE_PROGRAM(mSquareColorProgram->get_product());
	//
	mSquareColorProgram->uniform_value(eps::utils::to_int(program_enum::u_transform),
									   mSquareColorUi->Get_u_transform());
	mSquareColorProgram->uniform_value(eps::utils::to_int(program_enum::u_color), mSquareColorUi->Get_u_color());
	//
	mSquareColorEffect->construct(mSquareColorUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mSquareColorEffect->render(*mSquareColorProgram.get(), attributes, mSquareColorSettings->mIndices.size());
}

}
