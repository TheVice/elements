#include "PositionsProcessUi.h"
#include "PositionsProcessControls.h"
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
RTTI_DEFINITIONS(PositionsProcessUi)

PositionsProcessUi::PositionsProcessUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_dt(),
	mVertices(
{
	PositionsProcessVertex(),
						   PositionsProcessVertex(),
						   PositionsProcessVertex(),
						   PositionsProcessVertex()
})
{
}

PositionsProcessUi::~PositionsProcessUi() = default;

bool PositionsProcessUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_DT_BUTTON_2)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_7)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_12)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_17)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_22)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_DT_PANEL_3)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_8)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_13)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_18)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_23)
	//
	IS_CONTROL_EXIST(U_DT_LABEL_1)
	IS_CONTROL_EXIST(U_DT_LABEL_4)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_5)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_6)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_9)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_10)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_11)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_14)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_20)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_24)
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

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_7].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_8].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_8)
				SET_VISIBLE(false, VERTEX_1_PANEL_13)
				SET_VISIBLE(false, VERTEX_2_PANEL_18)
				SET_VISIBLE(false, VERTEX_3_PANEL_23)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_12].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_13].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_8)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_13)
				SET_VISIBLE(false, VERTEX_2_PANEL_18)
				SET_VISIBLE(false, VERTEX_3_PANEL_23)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_17].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_18].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_8)
				SET_VISIBLE(false, VERTEX_1_PANEL_13)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_18)
				SET_VISIBLE(false, VERTEX_3_PANEL_23)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_22].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_23].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_8)
				SET_VISIBLE(false, VERTEX_1_PANEL_13)
				SET_VISIBLE(false, VERTEX_2_PANEL_18)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_23)
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

void PositionsProcessUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_DT_PANEL_3].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_dt, U_DT_LABEL_1)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_8].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_5)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_6)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_13].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_10)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_11)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_18].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_15)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_16)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_23].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_21)
		}
	}
}

void PositionsProcessUi::Set_u_dt(const float& a_u_dt)
{
	m_u_dt = a_u_dt;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_dt, U_DT_SLIDER_1)
	//
	mIsRestoreNeed = false;
}

const float& PositionsProcessUi::Get_u_dt() const
{
	return m_u_dt;
}

void PositionsProcessUi::SetVertices(const std::vector<PositionsProcessVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_5)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_6)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_10)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_15)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_21)
	//
	mIsRestoreNeed = false;
}

const std::vector<PositionsProcessVertex>& PositionsProcessUi::GetVertices() const
{
	return mVertices;
}

bool PositionsProcessUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& PositionsProcessUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_DT_SLIDER_1:
			return m_u_dt;

		case VERTEX_0_SLIDER_5:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_6:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_1_SLIDER_10:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_11:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_2_SLIDER_15:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_16:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_3_SLIDER_20:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_21:
			return mVertices[3].a_vertex_xy.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
