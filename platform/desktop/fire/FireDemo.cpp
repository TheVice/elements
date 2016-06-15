
#include "FireDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(FireDemo)

FireDemo::FireDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mRenderer(nullptr)
{
}

FireDemo::~FireDemo()
{
}

void FireDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mRenderer = std::make_unique<eps::experiment::fire::renderer>();

	if (!mRenderer->initialize())
	{
		throw std::runtime_error("mRenderer->initialize() failed");
	}

	mRenderer->set_background("textures/noise.png");
	//
	mRenderer->set_color_hot(glm::vec3(1.0f, 0.0f, 0.0f));
	//
	mRenderer->set_color_cold(glm::vec3(0.0f, 1.0f, 1.0f));
	// construct renderer
	mRenderer->construct(size, 512);
}

void FireDemo::Update(const Library::GameTime&)
{
	static GLfloat intensity = 0.0f;
	static GLfloat intensityAddition = 0.005f;
	static GLfloat covering = 0.0f;
	static GLfloat coveringAddition = 0.005f;
	//
	intensity += intensityAddition;

	if (intensity > 1.0f)
	{
		intensity = 1.0f;
		intensityAddition *= -1;
	}
	else if (intensity < 0.0f)
	{
		intensity = 0.0f;
		intensityAddition *= -1;
	}

	mRenderer->set_intensity(intensity);
	//
	covering += coveringAddition;

	if (covering > 1.0f)
	{
		covering = 1.0f;
		coveringAddition *= -1;
	}
	else if (covering < 0.0f)
	{
		covering = 0.0f;
		coveringAddition *= -1;
	}

	mRenderer->set_covering(covering);
}

void FireDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
}

}
