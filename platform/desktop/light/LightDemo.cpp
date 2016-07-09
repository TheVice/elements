
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
	mLightRendererFactory->close(mRenderId);
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

	if (!renderer->startup(size, sQuantity))
	{
		throw std::runtime_error("renderer->startup() failed");
	}

	if (!renderer->set_background(sBackground))
	{
		throw std::runtime_error("renderer->set_background() failed");
	}

	renderer->set_color(sColor);
	//
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
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

void LightDemo::Draw(const Library::GameTime&)
{
	auto renderer = mLightRendererFactory->get(mRenderId);
	renderer->render();
}

const char* LightDemo::sBackground =  "textures/background.png";
const glm::vec3 LightDemo::sColor = { 1.0f, 1.0f, 1.0f }; //# FFFFFF
const int LightDemo::sQuantity = 1000;

}
