
#include "ParticlesDemo.h"
#include "rendering/utils/program_loader.h"
#include "assets/assets_storage.h"

namespace Rendering
{
RTTI_DEFINITIONS(ParticlesDemo)

ParticlesDemo::ParticlesDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mParticlesEffect(),
	mVertexArrayObject(0),
	mVertexBuffer(0),
	mVertexCount(0),
	mSettings(nullptr)
{
}

ParticlesDemo::~ParticlesDemo()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void ParticlesDemo::Initialize()
{
	// Build the shader program
	auto data =
		eps::assets_storage::instance().read<eps::rendering::program_data>("assets/shaders/experiments/liquid/particles.prog");

	if (!data || !data.value().v_shader() || !data.value().f_shader())
	{
		throw std::runtime_error("Failed to load shader");
	}

	std::vector<Library::ShaderDefinition> shaders(2);
	shaders.clear();
	//
	shaders.push_back(Library::ShaderDefinition(GL_VERTEX_SHADER, data.value().v_shader()));
	shaders.push_back(Library::ShaderDefinition(GL_FRAGMENT_SHADER, data.value().f_shader()));
	//
	mParticlesEffect.BuildProgram(shaders);
	// Load the settings
	mSettings = std::make_unique<SettingsReader>();
	bool settingLoaded = load_data("settings/experiments/liquid/particles.xml", *mSettings.get());

	if (!settingLoaded)
	{
		throw std::runtime_error("Failed to load settings");
	}

	// Create the vertex buffer object
	mVertexCount = mSettings->mVertices.size();
	mParticlesEffect.CreateVertexBuffer(&mSettings->mVertices.front(), mVertexCount, mVertexBuffer);
	// Create the vertex array object
	glGenVertexArrays(1, &mVertexArrayObject);
	mParticlesEffect.Initialize(mVertexArrayObject);
	glBindVertexArray(0);
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void ParticlesDemo::Draw(const Library::GameTime&)
{
	glBindVertexArray(mVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//
	mParticlesEffect.Use();
	mParticlesEffect.u_transform() << mSettings->mTransform;
	mParticlesEffect.u_size() << mSettings->mSize;
	//
	glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
	//
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

}
