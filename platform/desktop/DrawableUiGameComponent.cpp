
#include "DrawableUiGameComponent.h"
#include "math/transform.h"
#include "Game.h"

namespace Desktop
{
RTTI_DEFINITIONS(DrawableUiGameComponent)

DrawableUiGameComponent::DrawableUiGameComponent(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mTransformTouch(),
	mUiSystem(nullptr)
{
}

DrawableUiGameComponent::~DrawableUiGameComponent()
{
}

void DrawableUiGameComponent::Initialize()
{
	const auto screenSize = eps::math::uvec2(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mUiSystem = std::make_shared<eps::ui::system>();

	if (!std::static_pointer_cast<eps::ui::system>(mUiSystem)->construct(screenSize))
	{
		throw std::runtime_error("eps::ui::system::construct() failed");
	}

	mTransformTouch = eps::math::translate(0.0f, screenSize.y, 0.0f) * eps::math::scale(1.0f, -1.0f, 1.0f);
}

void DrawableUiGameComponent::Update(const Library::GameTime&)
{
	static bool touchDown = false;
	auto screenPos = glm::dvec2();
	glfwGetCursorPos(mGame->GetWindow(), &screenPos.x, &screenPos.y);
	const auto touchPos = mTransformTouch * eps::math::vec4(screenPos.x, screenPos.y, 1.0f, 1.0f);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		if (!touchDown)
		{
			mUiSystem->touch(touchPos.x, touchPos.y, eps::ui::touch_action::DOWN);
			touchDown = true;
		}

		mUiSystem->touch(touchPos.x, touchPos.y, eps::ui::touch_action::MOVE);
	}
	else if (touchDown)
	{
		mUiSystem->touch(touchPos.x, touchPos.y, eps::ui::touch_action::MOVE);
		mUiSystem->touch(touchPos.x, touchPos.y, eps::ui::touch_action::UP);
		touchDown = false;
	}
}

void DrawableUiGameComponent::Draw(const Library::GameTime&)
{
	mUiSystem->draw();
}

}
