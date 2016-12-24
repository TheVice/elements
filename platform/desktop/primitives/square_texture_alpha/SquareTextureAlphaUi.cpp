#include "SquareTextureAlphaUi.h"
#include "SquareTextureAlphaControls.h"
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
RTTI_DEFINITIONS(SquareTextureAlphaUi)

SquareTextureAlphaUi::SquareTextureAlphaUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_transform(),
	m_u_color(),
	mVertices(
{
	SquareTextureAlphaVertex(),
							 SquareTextureAlphaVertex(),
							 SquareTextureAlphaVertex(),
							 SquareTextureAlphaVertex()
})
{
}

SquareTextureAlphaUi::~SquareTextureAlphaUi() = default;

bool SquareTextureAlphaUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_TRANSFORM_BUTTON_13)
	IS_CONTROL_EXIST(U_COLOR_BUTTON_20)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_27)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_34)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_41)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_48)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	IS_CONTROL_EXIST(U_TRANSFORM_PANEL_14)
	IS_CONTROL_EXIST(U_COLOR_PANEL_21)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_28)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_35)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_42)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_49)
	//
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_1)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_2)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_3)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_4)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_5)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_6)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_7)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_8)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_9)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_10)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_11)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_12)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_15)
	IS_CONTROL_EXIST(U_COLOR_LABEL_16)
	IS_CONTROL_EXIST(U_COLOR_LABEL_17)
	IS_CONTROL_EXIST(U_COLOR_LABEL_18)
	IS_CONTROL_EXIST(U_COLOR_LABEL_19)
	IS_CONTROL_EXIST(U_COLOR_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_36)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_37)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_38)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_39)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_40)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_43)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_44)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_47)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_50)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_TRANSFORM_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_TRANSFORM_PANEL_14].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_TRANSFORM_PANEL_14)
				SET_VISIBLE(false, U_COLOR_PANEL_21)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_COLOR_BUTTON_20].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_PANEL_21].lock())
			{
				SET_VISIBLE(false, U_TRANSFORM_PANEL_14)
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_PANEL_21)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_27].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_28].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_28)
				SET_VISIBLE(false, VERTEX_1_PANEL_35)
				SET_VISIBLE(false, VERTEX_2_PANEL_42)
				SET_VISIBLE(false, VERTEX_3_PANEL_49)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_34].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_35].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_28)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_35)
				SET_VISIBLE(false, VERTEX_2_PANEL_42)
				SET_VISIBLE(false, VERTEX_3_PANEL_49)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_41].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_42].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_28)
				SET_VISIBLE(false, VERTEX_1_PANEL_35)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_42)
				SET_VISIBLE(false, VERTEX_3_PANEL_49)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_48].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_49].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_28)
				SET_VISIBLE(false, VERTEX_1_PANEL_35)
				SET_VISIBLE(false, VERTEX_2_PANEL_42)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_49)
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

void SquareTextureAlphaUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_TRANSFORM_PANEL_14].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[0][0], U_TRANSFORM_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[0][1], U_TRANSFORM_LABEL_2)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[0][2], U_TRANSFORM_LABEL_3)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[1][0], U_TRANSFORM_LABEL_4)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[1][1], U_TRANSFORM_LABEL_5)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[1][2], U_TRANSFORM_LABEL_6)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[2][0], U_TRANSFORM_LABEL_7)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[2][1], U_TRANSFORM_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[2][2], U_TRANSFORM_LABEL_9)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[3][0], U_TRANSFORM_LABEL_10)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[3][1], U_TRANSFORM_LABEL_11)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[3][2], U_TRANSFORM_LABEL_12)
		}
	}

	if (auto directPanel = mControls[U_COLOR_PANEL_21].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color[0], U_COLOR_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color[1], U_COLOR_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color[2], U_COLOR_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color[3], U_COLOR_LABEL_19)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_28].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_26)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_35].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_31)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_33)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_42].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_37)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_38)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_39)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_40)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_49].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_44)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_45)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_46)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_47)
		}
	}
}

void SquareTextureAlphaUi::Set_u_transform(const eps::math::mat4& a_u_transform)
{
	m_u_transform = a_u_transform;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[0][0], U_TRANSFORM_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[0][1], U_TRANSFORM_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[0][2], U_TRANSFORM_SLIDER_3)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[1][0], U_TRANSFORM_SLIDER_4)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[1][1], U_TRANSFORM_SLIDER_5)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[1][2], U_TRANSFORM_SLIDER_6)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[2][0], U_TRANSFORM_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[2][1], U_TRANSFORM_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[2][2], U_TRANSFORM_SLIDER_9)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[3][0], U_TRANSFORM_SLIDER_10)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[3][1], U_TRANSFORM_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[3][2], U_TRANSFORM_SLIDER_12)
	//
	mIsRestoreNeed = false;
}

const eps::math::mat4& SquareTextureAlphaUi::Get_u_transform() const
{
	return m_u_transform;
}

void SquareTextureAlphaUi::Set_u_color(const eps::math::vec4& a_u_color)
{
	m_u_color = a_u_color;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color[0], U_COLOR_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(m_u_color[1], U_COLOR_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(m_u_color[2], U_COLOR_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(m_u_color[3], U_COLOR_SLIDER_19)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec4& SquareTextureAlphaUi::Get_u_color() const
{
	return m_u_color;
}

void SquareTextureAlphaUi::SetVertices(const std::vector<SquareTextureAlphaVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_26)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_33)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_37)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_38)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_39)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_40)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_44)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_45)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_46)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_47)
	//
	mIsRestoreNeed = false;
}

const std::vector<SquareTextureAlphaVertex>& SquareTextureAlphaUi::GetVertices() const
{
	return mVertices;
}

bool SquareTextureAlphaUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& SquareTextureAlphaUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_TRANSFORM_SLIDER_1:
			return m_u_transform[0][0];

		case U_TRANSFORM_SLIDER_2:
			return m_u_transform[0][1];

		case U_TRANSFORM_SLIDER_3:
			return m_u_transform[0][2];

		case U_TRANSFORM_SLIDER_4:
			return m_u_transform[1][0];

		case U_TRANSFORM_SLIDER_5:
			return m_u_transform[1][1];

		case U_TRANSFORM_SLIDER_6:
			return m_u_transform[1][2];

		case U_TRANSFORM_SLIDER_7:
			return m_u_transform[2][0];

		case U_TRANSFORM_SLIDER_8:
			return m_u_transform[2][1];

		case U_TRANSFORM_SLIDER_9:
			return m_u_transform[2][2];

		case U_TRANSFORM_SLIDER_10:
			return m_u_transform[3][0];

		case U_TRANSFORM_SLIDER_11:
			return m_u_transform[3][1];

		case U_TRANSFORM_SLIDER_12:
			return m_u_transform[3][2];

		case U_COLOR_SLIDER_16:
			return m_u_color[0];

		case U_COLOR_SLIDER_17:
			return m_u_color[1];

		case U_COLOR_SLIDER_18:
			return m_u_color[2];

		case U_COLOR_SLIDER_19:
			return m_u_color[3];

		case VERTEX_0_SLIDER_23:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_24:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_0_SLIDER_25:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_26:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_30:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_31:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_1_SLIDER_32:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_33:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_37:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_38:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_2_SLIDER_39:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_40:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_44:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_45:
			return mVertices[3].a_vertex_xy.y;

		case VERTEX_3_SLIDER_46:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_47:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
