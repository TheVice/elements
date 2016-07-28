
#include "SettingsWindow.h"
#include "metrics/metrics.h"
#include "math/transform.h"
//#include "ui/controls/button.h"
#include "ui/controls/label.h"
//#include "ui/controls/panel.h"
#include "ui/controls/slider.h"
#include "Game.h"

namespace Rendering
{
RTTI_DEFINITIONS(SettingsWindow)

class s_model : public eps::ui::slider_model
{
private:
	float mValue;
public:
	s_model() : slider_model(), mValue(0.0f) {}
	float get_value()  const
	{
		return mValue;
	}
	void set_value(float aValue)
	{
		mValue = aValue;
	}
};

SettingsWindow::SettingsWindow(Library::Game& aGame) :
	DrawableGameComponent(aGame),
	mTouchDown(false),
	mTransformTouch(),
	mUiSystem(nullptr)
{
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::Initialize()
{
	const eps::math::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mUiSystem = std::make_unique<eps::ui::system>();

	if (!mUiSystem->construct(size))
	{
		throw std::runtime_error("mUiSystem->construct() failed");
	}

	using namespace eps::metric_literals;
	eps::utils::link<eps::ui::label> labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 580_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("X Shear:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 550_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Y Shear:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 520_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Z Shear:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 490_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("X Scale:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 460_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Y Scale:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 430_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Z Scale:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 400_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("X Translate:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 370_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Y Translate:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 340_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Z Translate:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 310_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Size:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 580_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X1:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 550_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y1");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 520_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X2:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 490_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y2:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 460_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X3:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 430_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y3:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 400_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X4:");
	}

	labelControl = mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 370_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y4:");
	}

	eps::utils::link<eps::ui::slider> sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 580_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 550_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 520_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 490_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 460_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 430_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 400_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 370_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 340_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 310_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 580_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 550_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 520_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 490_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 460_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 430_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 400_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	sliderControl = mUiSystem->add<eps::ui::slider>(new s_model());

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 370_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	mTransformTouch = eps::math::translate(0.0f, size.y, 0.0f) * eps::math::scale(1.0f, -1.0f, 1.0f);
}

void SettingsWindow::Update(const Library::GameTime&)
{
	glm::dvec2 screenPos;
	glfwGetCursorPos(mGame->GetWindow(), &screenPos.x, &screenPos.y);
	//
	const eps::math::vec4 posTouch = mTransformTouch * eps::math::vec4(screenPos.x, screenPos.y, 1.0f, 1.0f);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		mTouchDown = true;
		mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::DOWN);
	}
	else if (mTouchDown)
	{
		mTouchDown = false;
		mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::UP);
	}

	mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::MOVE);
}

void SettingsWindow::Draw(const Library::GameTime&)
{
	mUiSystem->draw();
}

}
