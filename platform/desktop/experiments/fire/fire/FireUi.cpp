#include "FireUi.h"
#include "FireControls.h"
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
RTTI_DEFINITIONS(FireUi)

FireUi::FireUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_texel(),
	mVertices(
{
	FireVertex(),
			   FireVertex(),
			   FireVertex(),
			   FireVertex()
})
{
}

FireUi::~FireUi() = default;

bool FireUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_TEXEL_BUTTON_3)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_10)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_17)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_24)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_31)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_TEXEL_PANEL_4)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_11)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_18)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_25)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_32)
	//
	IS_CONTROL_EXIST(U_TEXEL_LABEL_1)
	IS_CONTROL_EXIST(U_TEXEL_LABEL_2)
	IS_CONTROL_EXIST(U_TEXEL_LABEL_5)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_6)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_7)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_8)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_9)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_12)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_13)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_14)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_20)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_27)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_33)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_TEXEL_BUTTON_3].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_TEXEL_PANEL_4].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_TEXEL_PANEL_4)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_10].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_11].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_11)
				SET_VISIBLE(false, VERTEX_1_PANEL_18)
				SET_VISIBLE(false, VERTEX_2_PANEL_25)
				SET_VISIBLE(false, VERTEX_3_PANEL_32)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_17].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_18].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_11)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_18)
				SET_VISIBLE(false, VERTEX_2_PANEL_25)
				SET_VISIBLE(false, VERTEX_3_PANEL_32)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_24].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_25].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_11)
				SET_VISIBLE(false, VERTEX_1_PANEL_18)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_25)
				SET_VISIBLE(false, VERTEX_3_PANEL_32)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_31].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_32].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_11)
				SET_VISIBLE(false, VERTEX_1_PANEL_18)
				SET_VISIBLE(false, VERTEX_2_PANEL_25)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_32)
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

void FireUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_TEXEL_PANEL_4].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_texel[0], U_TEXEL_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_texel[1], U_TEXEL_LABEL_2)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_11].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_6)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_7)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_9)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_18].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_13)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_14)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_15)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_16)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_25].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_21)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_23)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_32].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_27)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_28)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_29)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_30)
		}
	}
}

void FireUi::Set_u_texel(const eps::math::vec2& a_u_texel)
{
	m_u_texel = a_u_texel;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_texel[0], U_TEXEL_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_texel[1], U_TEXEL_SLIDER_2)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec2& FireUi::Get_u_texel() const
{
	return m_u_texel;
}

void FireUi::SetVertices(const std::vector<FireVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_6)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_9)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_13)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_14)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_15)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_21)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_27)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_28)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_29)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_30)
	//
	mIsRestoreNeed = false;
}

const std::vector<FireVertex>& FireUi::GetVertices() const
{
	return mVertices;
}

bool FireUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& FireUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_TEXEL_SLIDER_1:
			return m_u_texel[0];

		case U_TEXEL_SLIDER_2:
			return m_u_texel[1];

		case VERTEX_0_SLIDER_6:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_7:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_0_SLIDER_8:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_9:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_13:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_14:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_1_SLIDER_15:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_16:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_20:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_21:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_2_SLIDER_22:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_23:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_27:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_28:
			return mVertices[3].a_vertex_xy.y;

		case VERTEX_3_SLIDER_29:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_30:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
