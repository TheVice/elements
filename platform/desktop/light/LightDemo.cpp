
#include "LightDemo.h"
#if defined (_MSC_VER) && !defined(__clang__)
#include "light_renderer.h"
#endif
#include "Game.h"
#include <memory>

namespace Rendering
{
RTTI_DEFINITIONS(LightDemo)

LightDemo::LightDemo(Library::Game& aGame)
	: DrawableGameComponent(aGame),
	  mTouchDown(false),
	  mRenderId(-1),
	  mLightRendererFactory(nullptr)
{
}

LightDemo::~LightDemo()
{
	using namespace std::literals;
	std::this_thread::sleep_for(2s);
	//
	mLightRendererFactory->close(mRenderId);
	//
	std::this_thread::sleep_for(5s);
}

void LightDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	mLightRendererFactory = std::make_unique<light_renderer_factory>();
	//
	bool preview = true;
	mRenderId = mLightRendererFactory->open(preview);
	//
	auto renderer = mLightRendererFactory->get(mRenderId);
	size_t particles_count = 500;

	if (!renderer->startup(size, particles_count))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	const char* pathToTexture = "textures/noise.png";

	if (!renderer->set_background(pathToTexture))
	{
		throw std::runtime_error("renderer->set_background() failed");
	}

	renderer->set_color(glm::vec3(1.0f, 0.5f, 0.25f));
}

void LightDemo::Update(const Library::GameTime&)
{
	glm::dvec2 pos;
	glfwGetCursorPos(mGame->GetWindow(), &pos.x, &pos.y);
	//
	auto renderer = mLightRendererFactory->get(mRenderId);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		renderer->touch(pos.x, pos.y, AMOTION_EVENT_ACTION_DOWN);
		mTouchDown = true;
	}
	else if (mTouchDown)
	{
		mTouchDown = false;
		renderer->touch(pos.x, pos.y, AMOTION_EVENT_ACTION_UP);
	}
}

void LightDemo::Draw(const Library::GameTime& aGameTime)
{
	auto renderer = mLightRendererFactory->get(mRenderId);
	renderer->render();
}

}
