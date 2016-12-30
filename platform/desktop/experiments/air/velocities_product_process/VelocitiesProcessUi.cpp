#include "VelocitiesProcessUi.h"
#include "VelocitiesProcessControls.h"
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
RTTI_DEFINITIONS(VelocitiesProcessUi)

VelocitiesProcessUi::VelocitiesProcessUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_dt(),
	mVertices(
{
	VelocitiesProcessVertex(),
							VelocitiesProcessVertex(),
							VelocitiesProcessVertex(),
							VelocitiesProcessVertex()
})
{
}

VelocitiesProcessUi::~VelocitiesProcessUi() = default;

bool VelocitiesProcessUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_DT_BUTTON_2)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_9)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_16)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_23)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_30)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_DT_PANEL_3)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_10)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_17)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_24)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_31)
	//
	IS_CONTROL_EXIST(U_DT_LABEL_1)
	IS_CONTROL_EXIST(U_DT_LABEL_4)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_5)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_6)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_7)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_8)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_11)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_12)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_13)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_14)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_18)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_20)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_27)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_32)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_DT_BUTTON_2].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_DT_PANEL_3].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_DT_PANEL_3)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_9].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_10].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_10)
				SET_VISIBLE(false, VERTEX_1_PANEL_17)
				SET_VISIBLE(false, VERTEX_2_PANEL_24)
				SET_VISIBLE(false, VERTEX_3_PANEL_31)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_16].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_17].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_10)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_17)
				SET_VISIBLE(false, VERTEX_2_PANEL_24)
				SET_VISIBLE(false, VERTEX_3_PANEL_31)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_23].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_24].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_10)
				SET_VISIBLE(false, VERTEX_1_PANEL_17)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_24)
				SET_VISIBLE(false, VERTEX_3_PANEL_31)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_30].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_31].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_10)
				SET_VISIBLE(false, VERTEX_1_PANEL_17)
				SET_VISIBLE(false, VERTEX_2_PANEL_24)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_31)
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

void VelocitiesProcessUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_DT_PANEL_3].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_dt, U_DT_LABEL_1)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_10].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_field_uv.x, VERTEX_0_LABEL_5)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_field_uv.y, VERTEX_0_LABEL_6)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_field_data.x, VERTEX_0_LABEL_7)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_field_data.y, VERTEX_0_LABEL_8)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_17].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_field_uv.x, VERTEX_1_LABEL_12)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_field_uv.y, VERTEX_1_LABEL_13)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_field_data.x, VERTEX_1_LABEL_14)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_field_data.y, VERTEX_1_LABEL_15)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_24].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_field_uv.x, VERTEX_2_LABEL_19)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_field_uv.y, VERTEX_2_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_field_data.x, VERTEX_2_LABEL_21)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_field_data.y, VERTEX_2_LABEL_22)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_31].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_field_uv.x, VERTEX_3_LABEL_26)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_field_uv.y, VERTEX_3_LABEL_27)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_field_data.x, VERTEX_3_LABEL_28)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_field_data.y, VERTEX_3_LABEL_29)
		}
	}
}

void VelocitiesProcessUi::Set_u_dt(const float& a_u_dt)
{
	m_u_dt = a_u_dt;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_dt, U_DT_SLIDER_1)
	//
	mIsRestoreNeed = false;
}

const float& VelocitiesProcessUi::Get_u_dt() const
{
	return m_u_dt;
}

void VelocitiesProcessUi::SetVertices(const std::vector<VelocitiesProcessVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_field_uv.x, VERTEX_0_SLIDER_5)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_field_uv.y, VERTEX_0_SLIDER_6)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_field_data.x, VERTEX_0_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_field_data.y, VERTEX_0_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_field_uv.x, VERTEX_1_SLIDER_12)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_field_uv.y, VERTEX_1_SLIDER_13)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_field_data.x, VERTEX_1_SLIDER_14)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_field_data.y, VERTEX_1_SLIDER_15)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_field_uv.x, VERTEX_2_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_field_uv.y, VERTEX_2_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_field_data.x, VERTEX_2_SLIDER_21)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_field_data.y, VERTEX_2_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_field_uv.x, VERTEX_3_SLIDER_26)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_field_uv.y, VERTEX_3_SLIDER_27)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_field_data.x, VERTEX_3_SLIDER_28)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_field_data.y, VERTEX_3_SLIDER_29)
	//
	mIsRestoreNeed = false;
}

const std::vector<VelocitiesProcessVertex>& VelocitiesProcessUi::GetVertices() const
{
	return mVertices;
}

bool VelocitiesProcessUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& VelocitiesProcessUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_DT_SLIDER_1:
			return m_u_dt;

		case VERTEX_0_SLIDER_5:
			return mVertices[0].a_field_uv.x;

		case VERTEX_0_SLIDER_6:
			return mVertices[0].a_field_uv.y;

		case VERTEX_0_SLIDER_7:
			return mVertices[0].a_field_data.x;

		case VERTEX_0_SLIDER_8:
			return mVertices[0].a_field_data.y;

		case VERTEX_1_SLIDER_12:
			return mVertices[1].a_field_uv.x;

		case VERTEX_1_SLIDER_13:
			return mVertices[1].a_field_uv.y;

		case VERTEX_1_SLIDER_14:
			return mVertices[1].a_field_data.x;

		case VERTEX_1_SLIDER_15:
			return mVertices[1].a_field_data.y;

		case VERTEX_2_SLIDER_19:
			return mVertices[2].a_field_uv.x;

		case VERTEX_2_SLIDER_20:
			return mVertices[2].a_field_uv.y;

		case VERTEX_2_SLIDER_21:
			return mVertices[2].a_field_data.x;

		case VERTEX_2_SLIDER_22:
			return mVertices[2].a_field_data.y;

		case VERTEX_3_SLIDER_26:
			return mVertices[3].a_field_uv.x;

		case VERTEX_3_SLIDER_27:
			return mVertices[3].a_field_uv.y;

		case VERTEX_3_SLIDER_28:
			return mVertices[3].a_field_data.x;

		case VERTEX_3_SLIDER_29:
			return mVertices[3].a_field_data.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
