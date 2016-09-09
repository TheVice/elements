
#include "ParticlesDemo.h"
#include "rendering/utils/program_loader.h"
#include "assets/assets_storage.h"
#include "utils/std/product.h"
#include "Game.h"
#include "CustomUi.h"

namespace Rendering
{
RTTI_DEFINITIONS(ParticlesDemo)

ParticlesDemo::ParticlesDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mProgram(),
	mParticlesEffect(),
	mVertexArrayObject(0),
	mVertexBuffer(eps::rendering::buffer_usage::STATIC_DRAW),
	mIndexBuffer(eps::rendering::buffer_usage::STATIC_DRAW),
	mSettings(),
	mUi(nullptr)
{
}

ParticlesDemo::~ParticlesDemo()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void ParticlesDemo::Initialize()
{
	// Build the shader program
	auto assetPath = "assets/shaders/experiments/liquid/particles.prog";

	if (!eps::rendering::load_program(assetPath, mProgram))
	{
		throw std::runtime_error("Failed to load shader");
	}

	mParticlesEffect.SetProgram(eps::utils::raw_product(mProgram.get_product()));
	// Load the settings
	assetPath = "assets/settings/experiments/liquid/particles.xml";
	mSettings = eps::assets_storage::instance().read<SettingsReader>(assetPath);

	if (!mSettings || mSettings->mIsEmpty)
	{
		throw std::runtime_error("Failed to load settings");
	}

	// Create the vertex buffer object
	mVertexBuffer.allocate(&mSettings->mVertices.front(), mSettings->mVertices.size(),
						   sizeof(mSettings->mVertices.front()));
	// Create the index buffer object
	mIndexBuffer.allocate(&mSettings->mIndices.front(), mSettings->mIndices.size(),
						  sizeof(mSettings->mIndices.front()));
	// Create the vertex array object
	glGenVertexArrays(1, &mVertexArrayObject);
	mParticlesEffect.Initialize(mVertexArrayObject);
	glBindVertexArray(0);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Retry the UI service and set the values from settings class
	mUi = static_cast<Rendering::CustomUi*>(mGame->GetServices().GetService(Rendering::CustomUi::TypeIdClass()));
	assert(mUi);
	mUi->Set_u_transform(mSettings->mTransform);
	mUi->Set_u_size(mSettings->mSize);
	mUi->SetCheckBoxState(glIsEnabled(GL_POINT_SPRITE), glIsEnabled(GL_VERTEX_PROGRAM_POINT_SIZE));
}

void ParticlesDemo::Update(const Library::GameTime&)
{
	if (mUi->IsNeedRestore())
	{
		mUi->Set_u_transform(mSettings->mTransform);
		mUi->Set_u_size(mSettings->mSize);
		// mUi->SetCheckBoxState(glIsEnabled(GL_POINT_SPRITE), glIsEnabled(GL_VERTEX_PROGRAM_POINT_SIZE));
	}

	if (mUi->IsPointSpriteEnabled())
	{
		glEnable(GL_POINT_SPRITE);
	}
	else
	{
		glDisable(GL_POINT_SPRITE);
	}

	if (mUi->IsVertexProgramPointSizeEnabled())
	{
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	}
	else
	{
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	}
}

void ParticlesDemo::Draw(const Library::GameTime&)
{
	glBindVertexArray(mVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, eps::utils::raw_product(mVertexBuffer.get_product()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eps::utils::raw_product(mIndexBuffer.get_product()));
	//
	mParticlesEffect.Use();
	mParticlesEffect.u_transform() << mUi->Get_u_transform();
	mParticlesEffect.u_size() << mUi->Get_u_size();
	//
	glDrawElements(GL_TRIANGLES, mSettings->mIndices.size(), GL_UNSIGNED_INT, nullptr);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

}
