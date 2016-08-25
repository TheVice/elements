#ifdef A
#include "SettingsWindow.h"
#include "metrics/metrics.h"
#include "math/transform.h"
//#include "ui/controls/button.h"
#include "ui/controls/label.h"
//#include "ui/controls/panel.h"
#include "ui/controls/slider.h"
#include "Game.h"
#include <atomic>

static const glm::vec4 gCornflowerBlue = { 0.392f, 0.584f, 0.929f, 1.0f };

extern std::atomic<float> gShearX;
extern std::atomic<float> gShearY;
extern std::atomic<float> gShearZ;

extern std::atomic<float> gScaleX;
extern std::atomic<float> gScaleY;
extern std::atomic<float> gScaleZ;

extern std::atomic<float> gTranslateX;
extern std::atomic<float> gTranslateY;
extern std::atomic<float> gTranslateZ;

extern std::atomic<float> gSize;

extern std::atomic<float> gX1;
extern std::atomic<float> gY1;

extern std::atomic<float> gX2;
extern std::atomic<float> gY2;

extern std::atomic<float> gX3;
extern std::atomic<float> gY3;

extern std::atomic<float> gX4;
extern std::atomic<float> gY4;

extern std::atomic<bool> gChanged;

namespace Rendering
{
RTTI_DEFINITIONS(SettingsWindow)

class SliderModel : public eps::ui::slider_model
{
private:
	float mValue;
	const float mMin;
	const float mDelta;
private:
	static const float sDefaultMin;
	static const float sDefaultMax;
public:
	SliderModel() :
		slider_model(),
		mValue(sDefaultMin),
		mMin(sDefaultMin),
		mDelta(sDefaultMax)
	{
	}

	SliderModel(float aMin, float aMax) :
		slider_model(),
		mValue(sDefaultMin),
		mMin(aMin),
		mDelta(aMax - aMin)
	{
		assert(aMin < aMax);
	}

	float get_value() const override
	{
		return mValue;
	}

	void set_value(float aValue) override
	{
		mValue = aValue;
	}

	float getRealValue() const
	{
		return mMin + (mDelta * mValue) / sDefaultMax;
	}

	void setRealValue(float aValue)
	{
		mValue = (sDefaultMax * (aValue - mMin)) / mDelta;
	}
};

const float SliderModel::sDefaultMin = 0.0f;
const float SliderModel::sDefaultMax = 1.0f;

class CustomSliderModel : public SliderModel
{
private:
	std::atomic<float>* mModelValue;
public:
	CustomSliderModel(float aMin, float aMax, std::atomic<float>* aModelValue) :
		SliderModel(aMin, aMax),
		mModelValue(aModelValue)
	{
		setRealValue(mModelValue->load());
	}

	float get_value() const override
	{
		float value = getRealValue();

		if (std::abs(value - mModelValue->load()) > 100 * std::numeric_limits<float>::epsilon())
		{
			mModelValue->store(value);
			gChanged.store(true);
		}

		return SliderModel::get_value();
	}
};

SettingsWindow::SettingsWindow(Library::Game& aGame) :
	GameComponent(aGame),
	mWindow(nullptr),
	mWindowThread(nullptr),
	mTouchDown(false),
	mTransformTouch(),
	mUiSystem(nullptr)
{
}

SettingsWindow::~SettingsWindow()
{
}

void ProcessWindow(GLFWwindow* aWindow, SettingsWindow* aSettingsWindow);

void SettingsWindow::Initialize()
{
	if (mGame->IsFullScreen())
	{
		throw std::runtime_error("Setting window can not be created for full screen main window");
	}

	mWindow = glfwCreateWindow(560, 600, "Matrix Elements", nullptr, mGame->GetWindow());
	assert(mWindow);
	//
	glm::ivec2 windowPos;
	glfwGetWindowPos(mGame->GetWindow(), &windowPos.x, &windowPos.y);
	windowPos.x += mGame->GetScreenWidth();
	glfwSetWindowPos(mWindow, windowPos.x, windowPos.y);
	//
	mWindowThread = std::make_unique<std::thread>(ProcessWindow, mWindow, this);
}

void SettingsWindow::Update(const Library::GameTime&)
{
	if (glfwWindowShouldClose(mWindow))
	{
		mWindowThread->join();
		glfwDestroyWindow(mWindow);
		mWindow = nullptr;
		mGame->Exit();
	}
}

void SettingsWindow::Release()
{
	if (mWindow)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
		mWindowThread->join();
		glfwDestroyWindow(mWindow);
		mWindow = nullptr;
	}
}

GLFWwindow* SettingsWindow::GetWindow() const
{
	return mWindow;
}

void Initialize(SettingsWindow* aSettingsWindow)
{
	int width = 0;
	int height = 0;
	glfwGetWindowSize(aSettingsWindow->GetWindow(), &width, &height);
	const eps::math::uvec2 size(width, height);
	//
	aSettingsWindow->mUiSystem = std::make_unique<eps::ui::system>();

	if (!aSettingsWindow->mUiSystem->construct(size))
	{
		throw std::runtime_error("mUiSystem->construct() failed");
	}

	using namespace eps::metric_literals;
	eps::utils::link<eps::ui::label> labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 580_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("X Shear:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 550_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Y Shear:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 520_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Z Shear:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 490_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("X Scale:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 460_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Y Scale:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 430_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Z Scale:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 400_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("X Translate:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 370_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Y Translate:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 340_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Z Translate:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(5_dp, 310_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Size:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 580_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X1:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 550_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y1");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 520_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X2:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 490_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y2:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 460_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X3:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 430_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y3:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 400_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex X4:");
	}

	labelControl = aSettingsWindow->mUiSystem->add<eps::ui::label>();

	if (auto label = labelControl.lock())
	{
		label->set_size(128_dp, 18_dp);
		label->set_position(300_dp, 370_dp);
		label->set_font("assets/ui/fonts/OpenSans-Regular.ttf", std::floor(18_dp));
		label->set_color(eps::math::vec4(0.9f, 0.25f, 0.2f, 1.0f));
		label->set_text("Vertex Y4:");
	}

	CustomSliderModel* model = new CustomSliderModel(-10.0f, 10.0f, &gShearX);
	eps::utils::link<eps::ui::slider> sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 580_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gShearY);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 550_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gShearZ);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 520_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gScaleX);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 490_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gScaleY);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 460_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gScaleZ);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 430_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gTranslateX);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 400_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gTranslateY);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 370_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gTranslateZ);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 340_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(0.1f, 100.0f, &gSize);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(125_dp, 310_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gX1);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 580_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gY1);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 550_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gX2);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 520_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gY2);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 490_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gX3);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 460_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gY3);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 430_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gX4);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 400_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	model = new CustomSliderModel(-10.0f, 10.0f, &gY4);
	sliderControl = aSettingsWindow->mUiSystem->add<eps::ui::slider>(model);

	if (auto slider = sliderControl.lock())
	{
		slider->set_size(150_dp, 16_dp);
		slider->set_position(400_dp, 370_dp);
		slider->set_color_tracker(eps::math::vec4(0.0f, 0.65f, 0.95f, 1.0f));
	}

	aSettingsWindow->mTransformTouch = eps::math::translate(0.0f, size.y, 0.0f) * eps::math::scale(1.0f, -1.0f,
									   1.0f);
}

void Update(SettingsWindow* aSettingsWindow)
{
	glm::dvec2 screenPos;
	glfwGetCursorPos(aSettingsWindow->GetWindow(), &screenPos.x, &screenPos.y);
	//
	const eps::math::vec4 posTouch = aSettingsWindow->mTransformTouch * eps::math::vec4(screenPos.x, screenPos.y,
									 1.0f, 1.0f);

	if (glfwGetMouseButton(aSettingsWindow->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		if (!aSettingsWindow->mTouchDown)
		{
			aSettingsWindow->mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::DOWN);
			aSettingsWindow->mTouchDown = true;
		}

		aSettingsWindow->mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::MOVE);
	}
	else if (aSettingsWindow->mTouchDown)
	{
		aSettingsWindow->mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::MOVE);
		aSettingsWindow->mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::UP);
		aSettingsWindow->mTouchDown = false;
	}
}

void Draw(SettingsWindow* aSettingsWindow)
{
	aSettingsWindow->mUiSystem->draw();
}

void ProcessWindow(GLFWwindow* aWindow, SettingsWindow* aSettingsWindow)
{
	glfwMakeContextCurrent(aWindow);
	//
	Initialize(aSettingsWindow);

	while (!glfwWindowShouldClose(aWindow))
	{
		glClearBufferfv(GL_COLOR, 0, &gCornflowerBlue[0]);
		//
		Update(aSettingsWindow);
		Draw(aSettingsWindow);
		//
		glfwSwapBuffers(aWindow);
	}
}

}
#endif
