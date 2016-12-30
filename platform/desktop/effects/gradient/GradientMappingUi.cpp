#include "GradientMappingUi.h"
#include "GradientMappingControls.h"
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
RTTI_DEFINITIONS(GradientMappingUi)

GradientMappingUi::GradientMappingUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_color_1(),
	m_u_color_2(),
	mVertices(
{
	GradientMappingVertex(),
						  GradientMappingVertex(),
						  GradientMappingVertex(),
						  GradientMappingVertex()
})
{
}

GradientMappingUi::~GradientMappingUi() = default;

bool GradientMappingUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_COLOR_1_BUTTON_4)
	IS_CONTROL_EXIST(U_COLOR_2_BUTTON_10)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_17)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_24)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_31)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_38)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_COLOR_1_PANEL_5)
	IS_CONTROL_EXIST(U_COLOR_2_PANEL_11)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_18)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_25)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_32)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_39)
	//
	IS_CONTROL_EXIST(U_COLOR_1_LABEL_1)
	IS_CONTROL_EXIST(U_COLOR_1_LABEL_2)
	IS_CONTROL_EXIST(U_COLOR_1_LABEL_3)
	IS_CONTROL_EXIST(U_COLOR_1_LABEL_6)
	IS_CONTROL_EXIST(U_COLOR_2_LABEL_7)
	IS_CONTROL_EXIST(U_COLOR_2_LABEL_8)
	IS_CONTROL_EXIST(U_COLOR_2_LABEL_9)
	IS_CONTROL_EXIST(U_COLOR_2_LABEL_12)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_13)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_14)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_20)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_27)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_34)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_35)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_36)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_37)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_40)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_COLOR_1_BUTTON_4].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_1_PANEL_5].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_1_PANEL_5)
				SET_VISIBLE(false, U_COLOR_2_PANEL_11)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_COLOR_2_BUTTON_10].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_2_PANEL_11].lock())
			{
				SET_VISIBLE(false, U_COLOR_1_PANEL_5)
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_2_PANEL_11)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_17].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_18].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_18)
				SET_VISIBLE(false, VERTEX_1_PANEL_25)
				SET_VISIBLE(false, VERTEX_2_PANEL_32)
				SET_VISIBLE(false, VERTEX_3_PANEL_39)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_24].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_25].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_18)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_25)
				SET_VISIBLE(false, VERTEX_2_PANEL_32)
				SET_VISIBLE(false, VERTEX_3_PANEL_39)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_31].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_32].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_18)
				SET_VISIBLE(false, VERTEX_1_PANEL_25)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_32)
				SET_VISIBLE(false, VERTEX_3_PANEL_39)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_38].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_39].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_18)
				SET_VISIBLE(false, VERTEX_1_PANEL_25)
				SET_VISIBLE(false, VERTEX_2_PANEL_32)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_39)
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

void GradientMappingUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_COLOR_1_PANEL_5].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_1[0], U_COLOR_1_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_1[1], U_COLOR_1_LABEL_2)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_1[2], U_COLOR_1_LABEL_3)
		}
	}

	if (auto directPanel = mControls[U_COLOR_2_PANEL_11].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_2[0], U_COLOR_2_LABEL_7)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_2[1], U_COLOR_2_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_2[2], U_COLOR_2_LABEL_9)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_18].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_13)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_14)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_15)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_16)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_25].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_21)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_23)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_32].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_27)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_28)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_29)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_30)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_39].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_34)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_35)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_36)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_37)
		}
	}
}

void GradientMappingUi::Set_u_color_1(const eps::math::vec3& a_u_color_1)
{
	m_u_color_1 = a_u_color_1;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_1[0], U_COLOR_1_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_1[1], U_COLOR_1_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_1[2], U_COLOR_1_SLIDER_3)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& GradientMappingUi::Get_u_color_1() const
{
	return m_u_color_1;
}

void GradientMappingUi::Set_u_color_2(const eps::math::vec3& a_u_color_2)
{
	m_u_color_2 = a_u_color_2;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_2[0], U_COLOR_2_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_2[1], U_COLOR_2_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_2[2], U_COLOR_2_SLIDER_9)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& GradientMappingUi::Get_u_color_2() const
{
	return m_u_color_2;
}

void GradientMappingUi::SetVertices(const std::vector<GradientMappingVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_13)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_14)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_15)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_21)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_27)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_28)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_29)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_34)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_35)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_36)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_37)
	//
	mIsRestoreNeed = false;
}

const std::vector<GradientMappingVertex>& GradientMappingUi::GetVertices() const
{
	return mVertices;
}

bool GradientMappingUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& GradientMappingUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_COLOR_1_SLIDER_1:
			return m_u_color_1[0];

		case U_COLOR_1_SLIDER_2:
			return m_u_color_1[1];

		case U_COLOR_1_SLIDER_3:
			return m_u_color_1[2];

		case U_COLOR_2_SLIDER_7:
			return m_u_color_2[0];

		case U_COLOR_2_SLIDER_8:
			return m_u_color_2[1];

		case U_COLOR_2_SLIDER_9:
			return m_u_color_2[2];

		case VERTEX_0_SLIDER_13:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_14:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_0_SLIDER_15:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_16:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_20:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_21:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_1_SLIDER_22:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_23:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_27:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_28:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_2_SLIDER_29:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_30:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_34:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_35:
			return mVertices[3].a_vertex_xy.y;

		case VERTEX_3_SLIDER_36:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_37:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
