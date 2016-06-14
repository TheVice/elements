
#include "StrangeDemo.h"
#ifdef _MSC_VER
#include "renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(StrangeDemo)

StrangeDemo::StrangeDemo(Library::Game& aGame, Library::Camera& aCamera)
	: DrawableGameComponent(aGame, aCamera),
	  mRenderer(nullptr),
	  mParticlesCount(10)
{
}

StrangeDemo::~StrangeDemo()
{
}

void StrangeDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mRenderer = std::make_unique<eps::experiment::strange::renderer>();
	//	if (!mRenderer->initialize(mParticlesCount))
	//	{
	//		throw std::runtime_error("mRenderer->initialize() failed");
	//	}
	//mRenderer->color_background(glm::vec3(1.0f, 0.5f, 0.25f));
	//
	//void color_gradient(const math::vec3 & color_1, const math::vec3 & color_2);
	// construct renderer
	//	mRenderer->construct(size);
}

void StrangeDemo::Draw(const Library::GameTime& aGameTime)
{
	//	mRenderer->render(static_cast<float>(aGameTime.GetElapsedGameTime()));
}

}
