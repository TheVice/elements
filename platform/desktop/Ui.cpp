
#include "Ui.h"
#include "metrics/metrics.h"
#include "math/transform.h"
#include "ui/controls/button.h"
#include "ui/controls/label.h"
#include "ui/controls/panel.h"
#include "assets/assets_storage.h"
#include "SliderModel.h"
#include "UiReader.h"
#include "Game.h"

namespace Desktop
{
RTTI_DEFINITIONS(Ui)

Ui::Ui(Library::Game& aGame, const std::string& aAssetPath) :
	DrawableGameComponent(aGame),
	mAssetPath(aAssetPath),
	mTouchDown(false),
	mTransformTouch(),
	mUiSystem(nullptr),
	mControls()
{
}

Ui::~Ui()
{
}

#define SET_CONTROL(C)																			\
	if (auto directControl = C.lock())															\
	{																							\
		const auto density = eps::metrics::instance().density();								\
		auto search = std::get<1>(controlInfo).find("position_x");								\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			auto x = search->second;															\
			search = std::get<1>(controlInfo).find("position_y");								\
			\
			if (search != std::get<1>(controlInfo).end())										\
			{																					\
				auto y = search->second;														\
				directControl->set_position(density * std::stoi(x), density * std::stoi(y));	\
			}																					\
		}																						\
		\
		search = std::get<1>(controlInfo).find("size_w");										\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			auto w = search->second;															\
			search = std::get<1>(controlInfo).find("size_h");									\
			\
			if (search != std::get<1>(controlInfo).end())										\
			{																					\
				auto h = search->second;														\
				directControl->set_size(density * std::stoi(w), density * std::stoi(h));		\
			}																					\
		}																						\
		\
		search = std::get<1>(controlInfo).find("visible");										\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			if (search->second == "true")														\
			{																					\
				directControl->set_visible(true);												\
			}																					\
			else																				\
			{																					\
				directControl->set_visible(false);												\
			}																					\
		}																						\
	}

#define SET_BUTTON(B)																			\
	if (auto directButton = std::static_pointer_cast<eps::ui::button>(B.lock()))				\
	{																							\
		auto search = std::get<1>(controlInfo).find("asset_path");								\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			directButton->set_asset(search->second.c_str());									\
		}																						\
	}

#define SET_LABEL(L)																			\
	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(L.lock()))					\
	{																							\
		const auto density = eps::metrics::instance().density();								\
		auto search = std::get<1>(controlInfo).find("font_path");								\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			auto fontPath = search->second;														\
			search = std::get<1>(controlInfo).find("font_height");								\
			\
			if (search != std::get<1>(controlInfo).end())										\
			{																					\
				auto font_height = std::stoi(search->second);									\
				directLabel->set_font(fontPath, std::floor(density * font_height));				\
			}																					\
		}																						\
		\
		search = std::get<1>(controlInfo).find("text");											\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			directLabel->set_text(search->second);												\
		}																						\
		\
		search = std::get<1>(controlInfo).find("color_r");										\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			auto r = std::stof(search->second);													\
			search = std::get<1>(controlInfo).find("color_g");									\
			\
			if (search != std::get<1>(controlInfo).end())										\
			{																					\
				auto g = std::stof(search->second);												\
				search = std::get<1>(controlInfo).find("color_b");								\
				\
				if (search != std::get<1>(controlInfo).end())									\
				{																				\
					auto b = std::stof(search->second);											\
					search = std::get<1>(controlInfo).find("color_a");							\
					\
					if (search != std::get<1>(controlInfo).end())								\
					{																			\
						auto a = std::stof(search->second);										\
						directLabel->set_color(eps::math::vec4(r, g, b, a));					\
					}																			\
				}																				\
			}																					\
		}																						\
		directLabel->set_alignment(eps::ui::halignment::LEFT, eps::ui::valignment::TOP);		\
	}

#define SET_PANEL(P)																			\
	if (auto directPanel = std::static_pointer_cast<eps::ui::panel>(P.lock()))					\
	{																							\
		auto search = std::get<1>(controlInfo).find("color_r");									\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			auto r = std::stof(search->second);													\
			search = std::get<1>(controlInfo).find("color_g");									\
			\
			if (search != std::get<1>(controlInfo).end())										\
			{																					\
				auto g = std::stof(search->second);												\
				search = std::get<1>(controlInfo).find("color_b");								\
				\
				if (search != std::get<1>(controlInfo).end())									\
				{																				\
					auto b = std::stof(search->second);											\
					search = std::get<1>(controlInfo).find("color_a");							\
					\
					if (search != std::get<1>(controlInfo).end())								\
					{																			\
						auto a = std::stof(search->second);										\
						directPanel->set_color(eps::math::vec4(r, g, b, a));					\
					}																			\
				}																				\
			}																					\
		}																						\
	}

#define SET_SLIDER(S)																			\
	if (auto directSlider = std::static_pointer_cast<eps::ui::slider>(S.lock()))				\
	{																							\
		auto search = std::get<1>(controlInfo).find("color_slider_r");							\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			auto r = std::stof(search->second);													\
			search = std::get<1>(controlInfo).find("color_slider_g");							\
			\
			if (search != std::get<1>(controlInfo).end())										\
			{																					\
				auto g = std::stof(search->second);												\
				search = std::get<1>(controlInfo).find("color_slider_b");						\
				\
				if (search != std::get<1>(controlInfo).end())									\
				{																				\
					auto b = std::stof(search->second);											\
					search = std::get<1>(controlInfo).find("color_slider_a");					\
					\
					if (search != std::get<1>(controlInfo).end())								\
					{																			\
						auto a = std::stof(search->second);										\
						directSlider->set_color_slider(eps::math::vec4(r, g, b, a));			\
					}																			\
				}																				\
			}																					\
		}																						\
		\
		search = std::get<1>(controlInfo).find("color_tracker_r");								\
		\
		if (search != std::get<1>(controlInfo).end())											\
		{																						\
			auto r = std::stof(search->second);													\
			search = std::get<1>(controlInfo).find("color_tracker_g");							\
			\
			if (search != std::get<1>(controlInfo).end())										\
			{																					\
				auto g = std::stof(search->second);												\
				search = std::get<1>(controlInfo).find("color_tracker_b");						\
				\
				if (search != std::get<1>(controlInfo).end())									\
				{																				\
					auto b = std::stof(search->second);											\
					search = std::get<1>(controlInfo).find("color_tracker_a");					\
					\
					if (search != std::get<1>(controlInfo).end())								\
					{																			\
						auto a = std::stof(search->second);										\
						directSlider->set_color_tracker(eps::math::vec4(r, g, b, a));			\
					}																			\
				}																				\
			}																					\
		}																						\
	}

void Ui::Initialize()
{
	const eps::math::uvec2 size(mGame->GetScreenWidth(), mGame->GetScreenHeight());
	mUiSystem = std::make_shared<eps::ui::system>();

	if (!std::static_pointer_cast<eps::ui::system>(mUiSystem)->construct(size))
	{
		throw std::runtime_error("mUiSystem->construct() failed");
	}

	auto data =
		eps::assets_storage::instance().read<UiReader>(mAssetPath);

	if (!data || data->mIsEmpty)
	{
		throw std::runtime_error("Failed to load UI asset");
	}

	for (const auto& controlInfo : data->mControlsInfo)
	{
		std::weak_ptr<eps::ui::control> control;
		auto parentControl = mUiSystem;
		auto search = std::get<1>(controlInfo).find("parent");

		if (search != std::get<1>(controlInfo).end())
		{
			parentControl = mControls[search->second].lock();
		}

		if (std::get<0>(controlInfo) == "button")
		{
			control = parentControl->add<eps::ui::button>();
			SET_BUTTON(control)
		}
		else if (std::get<0>(controlInfo) == "label")
		{
			control = parentControl->add<eps::ui::label>();
			SET_LABEL(control)
		}
		else if (std::get<0>(controlInfo) == "panel")
		{
			control = parentControl->add<eps::ui::panel>();
			SET_PANEL(control)
		}
		else if (std::get<0>(controlInfo) == "slider")
		{
			auto sliderId = 0;
			auto search = std::get<1>(controlInfo).find("id");

			if (search != std::get<1>(controlInfo).end())
			{
				sliderId = std::stoi(search->second);
			}

			SliderModel* sliderModel = nullptr;
			search = std::get<1>(controlInfo).find("min");

			if (search != std::get<1>(controlInfo).end())
			{
				auto minValue = std::stof(search->second);
				search = std::get<1>(controlInfo).find("max");

				if (search != std::get<1>(controlInfo).end())
				{
					auto maxValue = std::stof(search->second);
					sliderModel = GetSliderModel(sliderId, minValue, maxValue);
				}
				else
				{
					sliderModel = GetSliderModel(sliderId);
				}
			}
			else
			{
				sliderModel = GetSliderModel(sliderId);
			}

			if (sliderModel)
			{
				control = parentControl->add<eps::ui::slider>(sliderModel);
				SET_SLIDER(control)
			}
		}

		if (!control.expired())
		{
			SET_CONTROL(control)
			const auto controlName = std::get<1>(controlInfo).find("control_name")->second;
			mControls[controlName] = control;
		}
	}

	mTransformTouch = eps::math::translate(0.0f, size.y, 0.0f) * eps::math::scale(1.0f, -1.0f, 1.0f);
}

void Ui::Update(const Library::GameTime&)
{
	glm::dvec2 screenPos;
	glfwGetCursorPos(mGame->GetWindow(), &screenPos.x, &screenPos.y);
	//
	const auto posTouch = mTransformTouch * eps::math::vec4(screenPos.x, screenPos.y, 1.0f, 1.0f);

	if (glfwGetMouseButton(mGame->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		if (!mTouchDown)
		{
			mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::DOWN);
			mTouchDown = true;
		}

		mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::MOVE);
	}
	else if (mTouchDown)
	{
		mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::MOVE);
		mUiSystem->touch(posTouch.x, posTouch.y, eps::ui::touch_action::UP);
		mTouchDown = false;
	}
}

void Ui::Draw(const Library::GameTime&)
{
	mUiSystem->draw();
}

SliderModel* Ui::GetSliderModel(int aSliderId)
{
	(void)aSliderId;
	return new SliderModel();
}

SliderModel* Ui::GetSliderModel(int aSliderId, float aMin, float aMax)
{
	(void)aSliderId;
	return new SliderModel(aMin, aMax);
}

}
