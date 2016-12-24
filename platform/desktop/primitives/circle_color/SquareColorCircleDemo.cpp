
#include "SquareColorCircleDemo.h"
#include "SquareColorCircleEffect.h"
#include "SquareColorCircleUi.h"
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
RTTI_DEFINITIONS(SquareColorCircleDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_xy = 0,
	a_vertex_uv = 1,
	// uniforms
	u_transform = 0,
	u_color = 1
};

SquareColorCircleDemo::SquareColorCircleDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mSquareColorCircleProgram(nullptr),
	mSquareColorCircleEffect(nullptr),
	mSquareColorCircleSettings(),
	mSquareColorCircleUi(nullptr)
{
}

SquareColorCircleDemo::~SquareColorCircleDemo() = default;

bool SquareColorCircleDemo::Initialize()
{
	// Build the shader program
	mSquareColorCircleProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/primitives/circle_color.prog";

	if (!eps::rendering::load_program(assetPath, (*mSquareColorCircleProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/primitives/circle_color.xml";
	mSquareColorCircleSettings = eps::assets_storage::instance().read<SquareColorCircleSettings>(assetPath);

	if (!mSquareColorCircleSettings || mSquareColorCircleSettings->mIsEmpty)
	{
		return false;
	}

	// Create the effect
	mSquareColorCircleEffect = eps::utils::make_unique<SquareColorCircleEffect>
							   (mSquareColorCircleSettings->mVertices, mSquareColorCircleSettings->mIndices,
								eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mSquareColorCircleUi = static_cast<Rendering::SquareColorCircleUi*>(mGame->GetServices().GetService(
							   Rendering::SquareColorCircleUi::TypeIdClass()));
	assert(mSquareColorCircleUi);
	return mSquareColorCircleUi != nullptr;
}

void SquareColorCircleDemo::Update()
{
	if (mSquareColorCircleUi->IsNeedRestore())
	{
		mSquareColorCircleUi->Set_u_transform(mSquareColorCircleSettings->u_transform);
		mSquareColorCircleUi->Set_u_color(mSquareColorCircleSettings->u_color);
		//
		mSquareColorCircleUi->SetVertices(mSquareColorCircleSettings->mVertices);
	}
}

void SquareColorCircleDemo::Draw()
{
	EPS_STATE_PROGRAM(mSquareColorCircleProgram->get_product());
	//
	mSquareColorCircleProgram->uniform_value(eps::utils::to_int(program_enum::u_transform),
			mSquareColorCircleUi->Get_u_transform());
	mSquareColorCircleProgram->uniform_value(eps::utils::to_int(program_enum::u_color),
			mSquareColorCircleUi->Get_u_color());
	//
	mSquareColorCircleEffect->construct(mSquareColorCircleUi->GetVertices());
	std::array<short, 2> attributes = { eps::utils::to_int(program_enum::a_vertex_xy), eps::utils::to_int(program_enum::a_vertex_uv) };
	mSquareColorCircleEffect->render(*mSquareColorCircleProgram.get(), attributes,
									 mSquareColorCircleSettings->mIndices.size());
}
}
