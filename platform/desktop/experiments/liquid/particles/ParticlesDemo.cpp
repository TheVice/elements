
#include "ParticlesDemo.h"
#include "rendering/state/state_macro.h"
#include "rendering/utils/program_loader.h"
#include "rendering/passes/pass_base.h"
#include "utils/std/enum.h"
#include "math/transform.h"
#include "assets/asset_texture.h"
#include "assets/assets_storage.h"
#include "SettingsReader.h"
#include "SettingsWindow.h"
#include "RenderingGame.h"

#include <atomic>

std::atomic<float> gShearX(0);
std::atomic<float> gShearY(0);
std::atomic<float> gShearZ(0);
std::atomic<float> gScaleX(0);
std::atomic<float> gScaleY(0);
std::atomic<float> gScaleZ(0);
std::atomic<float> gTranslateX(0);
std::atomic<float> gTranslateY(0);
std::atomic<float> gTranslateZ(0);
std::atomic<float> gSize(0);

std::atomic<float> gX1(0);
std::atomic<float> gY1(0);
std::atomic<float> gX2(0);
std::atomic<float> gY2(0);
std::atomic<float> gX3(0);
std::atomic<float> gY3(0);
std::atomic<float> gX4(0);
std::atomic<float> gY4(0);

std::atomic<bool> gChanged(false);
//static std::atomic<bool> mStop(false);

#define GetShear(MAT4) (glm::vec3(MAT4[1].x, MAT4[0].y, MAT4[0].z))
#define GetScale(MAT4) (glm::vec3(MAT4[0].x, MAT4[1].y, MAT4[2].z))
#define GetTranslate(MAT4) (glm::vec3(MAT4[3].x, MAT4[3].y, MAT4[3].z))

#define SetShear(VEC3, MAT4) ({MAT4[1].x = VEC3.x; MAT4[0].y = VEC3.y; MAT4[0].z = VEC3.z;})
#define SetScale(VEC3, MAT4) ({MAT4[0].x = VEC3.x; MAT4[1].y = VEC3.y; MAT4[2].z = VEC3.z;})
#define SetTranslate(VEC3, MAT4) ({MAT4[3].x = VEC3.x; MAT4[3].y = VEC3.y; MAT4[3].z = VEC3.z;})

namespace Rendering
{
RTTI_DEFINITIONS(ParticlesDemo)

enum ProgramEnum
{
	VertexAttributePosition = 0,
	//
	FragmentUniformTransformation = 0,
	FragmentUniformSize = 1
};

ParticlesDemo::ParticlesDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mSettingsWindow(nullptr),
	mProgram(),
	mSquare(),
	mTransform(),
	mSize(1.0f)
{
}

ParticlesDemo::~ParticlesDemo()
{
}

void ParticlesDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());

	if (!eps::rendering::load_program("assets/shaders/experiments/liquid/particles.prog", mProgram))
	{
		throw std::runtime_error("eps::rendering::load_program() failed");
	}

	auto shear = GetShear(mTransform);
	auto scale = GetScale(mTransform);
	auto translate = GetTranslate(mTransform);
	//
	gShearX.store(shear.x);
	gShearY.store(shear.y);
	gShearZ.store(shear.z);
	//
	gScaleX.store(scale.x);
	gScaleY.store(scale.y);
	gScaleZ.store(scale.z);
	//
	gTranslateX.store(translate.x);
	gTranslateY.store(translate.y);
	gTranslateZ.store(translate.z);
	//
	gSize.store(mSize);
	//
	gX1.store(0);
	gY1.store(10);
	gX2.store(10);
	gY2.store(10);
	gX3.store(10);
	gY3.store(0);
	gX4.store(0);
	gY4.store(0);
	//
	mSettingsWindow = std::make_unique<Rendering::SettingsWindow>(*mGame);
	mSettingsWindow->Initialize();
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void ParticlesDemo::Update(const Library::GameTime& aGameTime)
{
	mSettingsWindow->Update(aGameTime);

	/*if (mStop.load())
	{
		mGame->Exit();
	}*/

	if (gChanged.load())
	{
		SetShear(glm::vec3(gShearX.load(), gShearY.load(), gShearZ.load()), mTransform);
		SetScale(glm::vec3(gScaleX.load(), gScaleY.load(), gScaleZ.load()), mTransform);
		SetTranslate(glm::vec3(gTranslateX.load(), gTranslateY.load(), gTranslateZ.load()), mTransform);
		mSize = gSize.load();
		//
		const glm::vec2 positionVertices[] =
		{
			{ gX1.load(), gY1.load() },
			{ gX2.load(), gY2.load() },
			{ gX3.load(), gY3.load() },
			{ gX4.load(), gY4.load() }
		};
		//
		const glm::vec2 textureVertices[] =
		{
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f }
		};
		//
		GLfloat vertices[] =
		{
			positionVertices[0].x, positionVertices[0].y, textureVertices[0].x, textureVertices[0].y,
			positionVertices[1].x, positionVertices[1].y, textureVertices[1].x, textureVertices[1].y,
			positionVertices[2].x, positionVertices[2].y, textureVertices[2].x, textureVertices[2].y,
			positionVertices[3].x, positionVertices[3].y, textureVertices[3].x, textureVertices[3].y
		};
		//
		mSquare.construct(vertices);
		//
		gChanged.store(false);
	}
}

void ParticlesDemo::Draw(const Library::GameTime&)
{
	EPS_STATE_PROGRAM(mProgram.get_product());
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformTransformation), mTransform);
	mProgram.uniform_value(eps::utils::to_int(FragmentUniformSize), mSize);
	mSquare.render(mProgram, eps::utils::to_int(VertexAttributePosition));
}

}
