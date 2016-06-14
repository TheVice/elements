
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
	  mRenderer(nullptr),
	  mParticlesCount(10)
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
	//	if (!mRenderer->initialize())
	//	{
	//		throw std::runtime_error("mRenderer->initialize() failed");
	//	}
	//    bool set_background(const char * asset);
	//
	//    void set_intensity(float intensity);
	//
	//    void set_covering(float covering);
	//
	//    void set_color_hot(const math::vec3 & color);
	//
	//    void set_color_cold(const math::vec3 & color);
	//
	// construct renderer
	mRenderer->construct(size, mParticlesCount);
}

void FireDemo::Draw(const Library::GameTime& aGameTime)
{
	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
}

}
