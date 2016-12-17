
#include "GeometryDemo.h"
#include "GeometryEffect.h"
#include "GeometryUi.h"
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

namespace Rendering
{
RTTI_DEFINITIONS(GeometryDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_pos = 0,
	a_vertex_normal = 1,
	a_vertex_tangent = 2,
	a_vertex_uv = 3,
	// uniforms
	u_matrix_mvp = 0,
	u_matrix_model_view = 1,
	u_map_normal = 2,
	u_has_map_normal = 3
};

GeometryDemo::GeometryDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mGeometryEffect(nullptr),
	mMapNormalTexture(nullptr),
	mGeometrySettings(),
	mGeometryUi(nullptr)
{
}

GeometryDemo::~GeometryDemo() = default;

bool GeometryDemo::Initialize()
{
	// Build the shader program
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/techniques/lpp_geometry.prog";

	if (!eps::rendering::load_program(assetPath, (*mProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/techniques/lpp_geometry.xml";
	mGeometrySettings = eps::assets_storage::instance().read<GeometrySettings>(assetPath);

	if (!mGeometrySettings || mGeometrySettings->mIsEmpty)
	{
		return false;
	}

	// Load the texture
	const auto textureAsset = eps::assets_storage::instance().read<eps::asset_texture>
							  (mGeometrySettings->u_map_normal);

	if (!textureAsset || !textureAsset->pixels())
	{
		return false;
	}

	auto textureMaker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	mMapNormalTexture = eps::utils::make_unique<eps::rendering::texture>();
	(*mMapNormalTexture.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	// Create the effect
	mGeometryEffect = eps::utils::make_unique<GeometryEffect>(mGeometrySettings->mVertices,
					  mGeometrySettings->mIndices,
					  eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mGeometryUi = static_cast<Rendering::GeometryUi*>(mGame->GetServices().GetService(
					  Rendering::GeometryUi::TypeIdClass()));
	assert(mGeometryUi);
	return true;
}

void GeometryDemo::Update()
{
	if (mGeometryUi->IsNeedRestore())
	{
		mGeometryUi->Set_u_matrix_mvp(mGeometrySettings->u_matrix_mvp);
		mGeometryUi->Set_u_matrix_model_view(mGeometrySettings->u_matrix_model_view);
		mGeometryUi->SetVertices(mGeometrySettings->mVertices);
	}
}

void GeometryDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(mMapNormalTexture->get_product()));
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_mvp), mGeometryUi->Get_u_matrix_mvp());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_model_view),
							mGeometryUi->Get_u_matrix_model_view());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_has_map_normal),
							static_cast<int>(mGeometryUi->Get_u_has_map_normal()));
	//
	mGeometryEffect->construct(mGeometryUi->GetVertices());
	//
	std::array<short, 4> attributes = { eps::utils::to_int(program_enum::a_vertex_pos), eps::utils::to_int(program_enum::a_vertex_normal),
										eps::utils::to_int(program_enum::a_vertex_tangent), eps::utils::to_int(program_enum::a_vertex_uv)
									  };
	mGeometryEffect->render(*mProgram.get(), attributes, mGeometrySettings->mIndices.size());
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
