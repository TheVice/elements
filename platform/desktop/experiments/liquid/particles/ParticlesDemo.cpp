
#include "ParticlesDemo.h"
#include "rendering/utils/program_loader.h"
#include "assets/assets_storage.h"
#include "utils/std/product.h"

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
	mSettings()
{
}

ParticlesDemo::~ParticlesDemo()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void ParticlesDemo::Initialize()
{
	// Build the shader program
	if (!eps::rendering::load_program("assets/shaders/experiments/liquid/particles.prog", mProgram))
	{
		throw std::runtime_error("Failed to load shader");
	}

	mParticlesEffect.SetProgram(eps::utils::raw_product(mProgram.get_product()));
	// Load the settings
	const auto assetPath = "assets/settings/experiments/liquid/particles.xml";
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
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void ParticlesDemo::Draw(const Library::GameTime&)
{
	glBindVertexArray(mVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, eps::utils::raw_product(mVertexBuffer.get_product()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eps::utils::raw_product(mIndexBuffer.get_product()));
	//
	mParticlesEffect.Use();
	mParticlesEffect.u_transform() << mSettings->mTransform;
	mParticlesEffect.u_size() << mSettings->mSize;
	//
	glDrawElements(GL_TRIANGLES, mSettings->mIndices.size(), GL_UNSIGNED_INT, nullptr);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

}
