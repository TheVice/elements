#include "ToneUi.h"
#include "ToneControls.h"
#include <checkbox.h>
#include <SliderModel.h>
#include <elements/ui/controls/button.h>
#include <elements/ui/controls/check.h>
#include <elements/ui/controls/label.h>
#include <elements/ui/controls/panel.h>
#include <elements/ui/controls/slider.h>
#include <cassert>

namespace Rendering
{
RTTI_DEFINITIONS(ToneUi)

ToneUi::ToneUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_exposure(),
	m_u_gamma(),
	mVertices(
{
	ToneVertex(),
			   ToneVertex(),
			   ToneVertex(),
			   ToneVertex()
})
{
}

ToneUi::~ToneUi() = default;

bool ToneUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_EXPOSURE_BUTTON_2)
	IS_CONTROL_EXIST(U_GAMMA_BUTTON_6)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_13)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_20)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_27)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_34)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_EXPOSURE_PANEL_3)
	IS_CONTROL_EXIST(U_GAMMA_PANEL_7)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_14)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_21)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_28)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_35)
	//
	IS_CONTROL_EXIST(U_EXPOSURE_LABEL_1)
	IS_CONTROL_EXIST(U_EXPOSURE_LABEL_4)
	IS_CONTROL_EXIST(U_GAMMA_LABEL_5)
	IS_CONTROL_EXIST(U_GAMMA_LABEL_8)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_9)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_10)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_11)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_12)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_17)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_18)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_36)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_EXPOSURE_BUTTON_2].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_EXPOSURE_PANEL_3].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_EXPOSURE_PANEL_3)
				SET_VISIBLE(false, U_GAMMA_PANEL_7)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_GAMMA_BUTTON_6].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_GAMMA_PANEL_7].lock())
			{
				SET_VISIBLE(false, U_EXPOSURE_PANEL_3)
				SET_VISIBLE(!directPanel->get_visible(), U_GAMMA_PANEL_7)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_14].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_14)
				SET_VISIBLE(false, VERTEX_1_PANEL_21)
				SET_VISIBLE(false, VERTEX_2_PANEL_28)
				SET_VISIBLE(false, VERTEX_3_PANEL_35)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_20].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_21].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_14)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_21)
				SET_VISIBLE(false, VERTEX_2_PANEL_28)
				SET_VISIBLE(false, VERTEX_3_PANEL_35)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_27].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_28].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_14)
				SET_VISIBLE(false, VERTEX_1_PANEL_21)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_28)
				SET_VISIBLE(false, VERTEX_3_PANEL_35)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_34].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_35].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_14)
				SET_VISIBLE(false, VERTEX_1_PANEL_21)
				SET_VISIBLE(false, VERTEX_2_PANEL_28)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_35)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[RESTORE_BUTTON].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			mIsRestoreNeed = !mIsRestoreNeed;
		});
	}

	return true;
}

void ToneUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_EXPOSURE_PANEL_3].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_exposure, U_EXPOSURE_LABEL_1)
		}
	}

	if (auto directPanel = mControls[U_GAMMA_PANEL_7].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_gamma, U_GAMMA_LABEL_5)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_14].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_9)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_10)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_11)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_12)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_21].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_19)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_28].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_26)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_35].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_31)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_33)
		}
	}
}

void ToneUi::Set_u_exposure(const float& a_u_exposure)
{
	m_u_exposure = a_u_exposure;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_exposure, U_EXPOSURE_SLIDER_1)
	//
	mIsRestoreNeed = false;
}

const float& ToneUi::Get_u_exposure() const
{
	return m_u_exposure;
}

void ToneUi::Set_u_gamma(const float& a_u_gamma)
{
	m_u_gamma = a_u_gamma;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_gamma, U_GAMMA_SLIDER_5)
	//
	mIsRestoreNeed = false;
}

const float& ToneUi::Get_u_gamma() const
{
	return m_u_gamma;
}

void ToneUi::SetVertices(const std::vector<ToneVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_9)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_10)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_12)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_26)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_33)
	//
	mIsRestoreNeed = false;
}

const std::vector<ToneVertex>& ToneUi::GetVertices() const
{
	return mVertices;
}

bool ToneUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& ToneUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_EXPOSURE_SLIDER_1:
			return m_u_exposure;

		case U_GAMMA_SLIDER_5:
			return m_u_gamma;

		case VERTEX_0_SLIDER_9:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_10:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_0_SLIDER_11:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_12:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_16:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_17:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_1_SLIDER_18:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_19:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_23:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_24:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_2_SLIDER_25:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_26:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_30:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_31:
			return mVertices[3].a_vertex_xy.y;

		case VERTEX_3_SLIDER_32:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_33:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
