
#include "StrangeDemo.h"
#if defined (_MSC_VER) && !defined(__clang__)
#include "strange_renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(StrangeDemo)

StrangeDemo::StrangeDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mRenderId(-1),
	  mStrangeRendererFactory(nullptr)
{
}

StrangeDemo::~StrangeDemo()
{
	mStrangeRendererFactory->close(mRenderId);
}

void StrangeDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mStrangeRendererFactory = std::make_unique<strange_renderer_factory>();
	//
	bool preview = true;
	mRenderId = mStrangeRendererFactory->open(preview);
	//
	auto renderer = mStrangeRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuantity))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	renderer->set_background(sColorBackground);
	renderer->set_gradient(sColorGradient1, sColorGradient2);
}

void StrangeDemo::Draw(const Library::GameTime&)
{
	auto renderer = mStrangeRendererFactory->get(mRenderId);
	renderer->render();
}

const glm::vec3 StrangeDemo::sColorBackground = { 0.13f, 0.13f, 0.13f }; //#202020
const glm::vec3 StrangeDemo::sColorGradient1 = { 0.45f, 0.45f, 0.45f }; //#747474
const glm::vec3 StrangeDemo::sColorGradient2 = { 0.98f, 0.96f, 0.09f }; //# f9f517
const int StrangeDemo::sQuantity = 500000;

}
