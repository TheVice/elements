
#include "ProjectorDemo.h"
#include "ProjectorEffect.h"
#include "ProjectorUi.h"
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
RTTI_DEFINITIONS(ProjectorDemo)

enum class program_enum : short
{
	// attributes
	a_vertex_pos = 0,
	// uniforms
	u_matrix_mvp = 0,
	u_matrix_model = 1,
	u_matrix_pvp = 2,
	u_map_projective = 3
};

ProjectorDemo::ProjectorDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(nullptr),
	mProjectorEffect(nullptr),
	mMapProjectiveTexture(nullptr),
	mProjectorSettings(),
	mProjectorUi(nullptr)
{
}

ProjectorDemo::~ProjectorDemo() = default;

bool ProjectorDemo::Initialize()
{
	// Build the shader program
	mProgram = eps::utils::make_unique<eps::rendering::program>();
	auto assetPath = "assets/shaders/techniques/projector.prog";

	if (!eps::rendering::load_program(assetPath, (*mProgram.get())))
	{
		return false;
	}

	// Load the settings
	assetPath = "assets/settings/techniques/projector.xml";
	mProjectorSettings = eps::assets_storage::instance().read<ProjectorSettings>(assetPath);

	if (!mProjectorSettings || mProjectorSettings->mIsEmpty)
	{
		return false;
	}

	// Load the texture
	const auto textureAsset = eps::assets_storage::instance().read<eps::asset_texture>
							  (mProjectorSettings->u_map_projective);

	if (!textureAsset || !textureAsset->pixels())
	{
		return false;
	}

	auto textureMaker = eps::rendering::get_texture_maker<eps::rendering::repeat_texture_policy>();
	mMapProjectiveTexture = eps::utils::make_unique<eps::rendering::texture>();
	(*mMapProjectiveTexture.get()) = textureMaker.construct(textureAsset->pixels(), textureAsset->size());
	// Create the effect
	mProjectorEffect = eps::utils::make_unique<ProjectorEffect>(mProjectorSettings->mVertices,
					   mProjectorSettings->mIndices,
					   eps::rendering::buffer_usage::STREAM_DRAW);
	// Retry the UI service
	mProjectorUi = static_cast<Rendering::ProjectorUi*>(mGame->GetServices().GetService(
					   Rendering::ProjectorUi::TypeIdClass()));
	assert(mProjectorUi);
	return true;
}

void ProjectorDemo::Update()
{
	if (mProjectorUi->IsNeedRestore())
	{
		mProjectorUi->Set_u_matrix_mvp(mProjectorSettings->u_matrix_mvp);
		mProjectorUi->Set_u_matrix_model(mProjectorSettings->u_matrix_model);
		mProjectorUi->Set_u_matrix_pvp(mProjectorSettings->u_matrix_pvp);
		mProjectorUi->SetVertices(mProjectorSettings->mVertices);
	}
}

void ProjectorDemo::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, eps::utils::raw_product(mMapProjectiveTexture->get_product()));
	//
	EPS_STATE_PROGRAM(mProgram->get_product());
	//
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_mvp), mProjectorUi->Get_u_matrix_mvp());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_model), mProjectorUi->Get_u_matrix_model());
	mProgram->uniform_value(eps::utils::to_int(program_enum::u_matrix_pvp), mProjectorUi->Get_u_matrix_pvp());
	//
	mProjectorEffect->construct(mProjectorUi->GetVertices());
	//
	mProjectorEffect->render(*mProgram.get(), eps::utils::to_int(program_enum::a_vertex_pos),
							 mProjectorSettings->mIndices.size());
	//
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
