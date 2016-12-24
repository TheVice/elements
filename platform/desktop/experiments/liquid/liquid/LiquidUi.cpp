
#include "LiquidUi.h"
#include "LiquidControls.h"
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
RTTI_DEFINITIONS(LiquidUi)

LiquidUi::LiquidUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_surface_color(),
	m_u_surface_texel(),
	mVertices(
{
	LiquidVertex(),
				 LiquidVertex(),
				 LiquidVertex(),
				 LiquidVertex()
})
{
}

LiquidUi::~LiquidUi() = default;

bool LiquidUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_SURFACE_COLOR_BUTTON_5)
	IS_CONTROL_EXIST(U_SURFACE_TEXEL_BUTTON_10)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_17)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_24)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_31)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_38)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_SURFACE_COLOR_PANEL_6)
	IS_CONTROL_EXIST(U_SURFACE_TEXEL_PANEL_11)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_18)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_25)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_32)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_39)
	//
	IS_CONTROL_EXIST(U_SURFACE_COLOR_LABEL_1)
	IS_CONTROL_EXIST(U_SURFACE_COLOR_LABEL_2)
	IS_CONTROL_EXIST(U_SURFACE_COLOR_LABEL_3)
	IS_CONTROL_EXIST(U_SURFACE_COLOR_LABEL_4)
	IS_CONTROL_EXIST(U_SURFACE_COLOR_LABEL_7)
	IS_CONTROL_EXIST(U_SURFACE_TEXEL_LABEL_8)
	IS_CONTROL_EXIST(U_SURFACE_TEXEL_LABEL_9)
	IS_CONTROL_EXIST(U_SURFACE_TEXEL_LABEL_12)
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

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_SURFACE_COLOR_BUTTON_5].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_SURFACE_COLOR_PANEL_6].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_SURFACE_COLOR_PANEL_6)
				SET_VISIBLE(false, U_SURFACE_TEXEL_PANEL_11)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_SURFACE_TEXEL_BUTTON_10].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_SURFACE_TEXEL_PANEL_11].lock())
			{
				SET_VISIBLE(false, U_SURFACE_COLOR_PANEL_6)
				SET_VISIBLE(!directPanel->get_visible(), U_SURFACE_TEXEL_PANEL_11)
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

void LiquidUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_SURFACE_COLOR_PANEL_6].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_surface_color[0], U_SURFACE_COLOR_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_surface_color[1], U_SURFACE_COLOR_LABEL_2)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_surface_color[2], U_SURFACE_COLOR_LABEL_3)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_surface_color[3], U_SURFACE_COLOR_LABEL_4)
		}
	}

	if (auto directPanel = mControls[U_SURFACE_TEXEL_PANEL_11].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_surface_texel[0], U_SURFACE_TEXEL_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_surface_texel[1], U_SURFACE_TEXEL_LABEL_9)
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

void LiquidUi::Set_u_surface_color(const eps::math::vec4& a_u_surface_color)
{
	m_u_surface_color = a_u_surface_color;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_surface_color[0], U_SURFACE_COLOR_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_surface_color[1], U_SURFACE_COLOR_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(m_u_surface_color[2], U_SURFACE_COLOR_SLIDER_3)
	SET_REAL_VALUE_AT_SLIDER(m_u_surface_color[3], U_SURFACE_COLOR_SLIDER_4)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec4& LiquidUi::Get_u_surface_color() const
{
	return m_u_surface_color;
}

void LiquidUi::Set_u_surface_texel(const eps::math::vec2& a_u_surface_texel)
{
	m_u_surface_texel = a_u_surface_texel;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_surface_texel[0], U_SURFACE_TEXEL_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(m_u_surface_texel[1], U_SURFACE_TEXEL_SLIDER_9)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec2& LiquidUi::Get_u_surface_texel() const
{
	return m_u_surface_texel;
}

void LiquidUi::SetVertices(const std::vector<LiquidVertex>& aVertices)
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

const std::vector<LiquidVertex>& LiquidUi::GetVertices() const
{
	return mVertices;
}

bool LiquidUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& LiquidUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_SURFACE_COLOR_SLIDER_1:
			return m_u_surface_color[0];

		case U_SURFACE_COLOR_SLIDER_2:
			return m_u_surface_color[1];

		case U_SURFACE_COLOR_SLIDER_3:
			return m_u_surface_color[2];

		case U_SURFACE_COLOR_SLIDER_4:
			return m_u_surface_color[3];

		case U_SURFACE_TEXEL_SLIDER_8:
			return m_u_surface_texel[0];

		case U_SURFACE_TEXEL_SLIDER_9:
			return m_u_surface_texel[1];

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
