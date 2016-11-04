
#include "StrangeDemo.h"

namespace Rendering
{
RTTI_DEFINITIONS(StrangeDemo)

StrangeDemo::StrangeDemo(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mRenderId(-1),
	mRendererFactory(nullptr)
{
}

StrangeDemo::~StrangeDemo()
{
	mRendererFactory->close(mRenderId);
}

bool StrangeDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mRendererFactory = eps::utils::make_unique<RendererFactory>();
	mRenderId = mRendererFactory->open(true);
	auto renderer = mRendererFactory->get(mRenderId);

	if (!renderer->startup(size, sQuantity))
	{
		return false;
	}

	renderer->set_background(sColorBackground);
	renderer->set_gradient(sColorGradient1, sColorGradient2);
	//
	return true;
}

void StrangeDemo::Update()
{
}

void StrangeDemo::Draw()
{
	auto renderer = mRendererFactory->get(mRenderId);
	renderer->render();
}

const glm::vec3 StrangeDemo::sColorBackground = { 0.13f, 0.13f, 0.13f }; //#202020
const glm::vec3 StrangeDemo::sColorGradient1 = { 0.45f, 0.45f, 0.45f }; //#747474
const glm::vec3 StrangeDemo::sColorGradient2 = { 0.98f, 0.96f, 0.09f }; //# f9f517
const int StrangeDemo::sQuantity = 500000;

}
