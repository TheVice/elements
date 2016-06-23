
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
	  mRenderId(-1)
{
}

LightDemo::~LightDemo()
{
	light_renderer_factory_.close(mRenderId);
}

void LightDemo::Initialize()
{
	const glm::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	//
	bool preview = true;
	mRenderId = light_renderer_factory_.open(preview);
	//
	auto renderer = light_renderer_factory_.get(mRenderId);
	size_t particles_count = 500;

	if (!renderer->startup(size, particles_count))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	const std::string pathToTexture = "textures/background.png";
	renderer->set_background(pathToTexture.c_str());
	//
	renderer->set_color(glm::vec3(1.0f, 0.5f, 0.25f));
}

void LightDemo::Update(const Library::GameTime&)
{
	glm::dvec2 pos;
	glfwGetCursorPos(mGame->GetWindow(), &pos.x, &pos.y);
	//pos.y = mGame->GetScreenHeight() - pos.y;
	auto renderer = light_renderer_factory_.get(mRenderId);

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
	auto renderer = light_renderer_factory_.get(mRenderId);
	renderer->render();
}

LightDemo::light_renderer_factory LightDemo::light_renderer_factory_;

}
