#include "FireRaymarchingUi.h"
#include "FireRaymarchingControls.h"
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
RTTI_DEFINITIONS(FireRaymarchingUi)

FireRaymarchingUi::FireRaymarchingUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_dt(),
	m_u_intensity(),
	m_u_covering(),
	m_u_texel(),
	m_u_color_hot(),
	m_u_color_cold(),
	mVertices(
{
	FireRaymarchingVertex(),
						  FireRaymarchingVertex(),
						  FireRaymarchingVertex(),
						  FireRaymarchingVertex()
})
{
}

FireRaymarchingUi::~FireRaymarchingUi() = default;

bool FireRaymarchingUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_DT_BUTTON_2)
	IS_CONTROL_EXIST(U_INTENSITY_BUTTON_6)
	IS_CONTROL_EXIST(U_COVERING_BUTTON_10)
	IS_CONTROL_EXIST(U_TEXEL_BUTTON_15)
	IS_CONTROL_EXIST(U_COLOR_HOT_BUTTON_21)
	IS_CONTROL_EXIST(U_COLOR_COLD_BUTTON_27)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_34)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_41)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_48)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_55)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_DT_PANEL_3)
	IS_CONTROL_EXIST(U_INTENSITY_PANEL_7)
	IS_CONTROL_EXIST(U_COVERING_PANEL_11)
	IS_CONTROL_EXIST(U_TEXEL_PANEL_16)
	IS_CONTROL_EXIST(U_COLOR_HOT_PANEL_22)
	IS_CONTROL_EXIST(U_COLOR_COLD_PANEL_28)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_35)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_42)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_49)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_56)
	//
	IS_CONTROL_EXIST(U_DT_LABEL_1)
	IS_CONTROL_EXIST(U_DT_LABEL_4)
	IS_CONTROL_EXIST(U_INTENSITY_LABEL_5)
	IS_CONTROL_EXIST(U_INTENSITY_LABEL_8)
	IS_CONTROL_EXIST(U_COVERING_LABEL_9)
	IS_CONTROL_EXIST(U_COVERING_LABEL_12)
	IS_CONTROL_EXIST(U_TEXEL_LABEL_13)
	IS_CONTROL_EXIST(U_TEXEL_LABEL_14)
	IS_CONTROL_EXIST(U_TEXEL_LABEL_17)
	IS_CONTROL_EXIST(U_COLOR_HOT_LABEL_18)
	IS_CONTROL_EXIST(U_COLOR_HOT_LABEL_19)
	IS_CONTROL_EXIST(U_COLOR_HOT_LABEL_20)
	IS_CONTROL_EXIST(U_COLOR_HOT_LABEL_23)
	IS_CONTROL_EXIST(U_COLOR_COLD_LABEL_24)
	IS_CONTROL_EXIST(U_COLOR_COLD_LABEL_25)
	IS_CONTROL_EXIST(U_COLOR_COLD_LABEL_26)
	IS_CONTROL_EXIST(U_COLOR_COLD_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_36)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_37)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_38)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_39)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_40)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_43)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_44)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_47)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_50)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_51)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_52)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_53)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_54)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_57)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_DT_BUTTON_2].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_DT_PANEL_3].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_DT_PANEL_3)
				SET_VISIBLE(false, U_INTENSITY_PANEL_7)
				SET_VISIBLE(false, U_COVERING_PANEL_11)
				SET_VISIBLE(false, U_TEXEL_PANEL_16)
				SET_VISIBLE(false, U_COLOR_HOT_PANEL_22)
				SET_VISIBLE(false, U_COLOR_COLD_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_INTENSITY_BUTTON_6].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_INTENSITY_PANEL_7].lock())
			{
				SET_VISIBLE(false, U_DT_PANEL_3)
				SET_VISIBLE(!directPanel->get_visible(), U_INTENSITY_PANEL_7)
				SET_VISIBLE(false, U_COVERING_PANEL_11)
				SET_VISIBLE(false, U_TEXEL_PANEL_16)
				SET_VISIBLE(false, U_COLOR_HOT_PANEL_22)
				SET_VISIBLE(false, U_COLOR_COLD_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_COVERING_BUTTON_10].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COVERING_PANEL_11].lock())
			{
				SET_VISIBLE(false, U_DT_PANEL_3)
				SET_VISIBLE(false, U_INTENSITY_PANEL_7)
				SET_VISIBLE(!directPanel->get_visible(), U_COVERING_PANEL_11)
				SET_VISIBLE(false, U_TEXEL_PANEL_16)
				SET_VISIBLE(false, U_COLOR_HOT_PANEL_22)
				SET_VISIBLE(false, U_COLOR_COLD_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_TEXEL_BUTTON_15].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_TEXEL_PANEL_16].lock())
			{
				SET_VISIBLE(false, U_DT_PANEL_3)
				SET_VISIBLE(false, U_INTENSITY_PANEL_7)
				SET_VISIBLE(false, U_COVERING_PANEL_11)
				SET_VISIBLE(!directPanel->get_visible(), U_TEXEL_PANEL_16)
				SET_VISIBLE(false, U_COLOR_HOT_PANEL_22)
				SET_VISIBLE(false, U_COLOR_COLD_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_COLOR_HOT_BUTTON_21].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_HOT_PANEL_22].lock())
			{
				SET_VISIBLE(false, U_DT_PANEL_3)
				SET_VISIBLE(false, U_INTENSITY_PANEL_7)
				SET_VISIBLE(false, U_COVERING_PANEL_11)
				SET_VISIBLE(false, U_TEXEL_PANEL_16)
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_HOT_PANEL_22)
				SET_VISIBLE(false, U_COLOR_COLD_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_COLOR_COLD_BUTTON_27].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_COLD_PANEL_28].lock())
			{
				SET_VISIBLE(false, U_DT_PANEL_3)
				SET_VISIBLE(false, U_INTENSITY_PANEL_7)
				SET_VISIBLE(false, U_COVERING_PANEL_11)
				SET_VISIBLE(false, U_TEXEL_PANEL_16)
				SET_VISIBLE(false, U_COLOR_HOT_PANEL_22)
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_COLD_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_34].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_35].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_35)
				SET_VISIBLE(false, VERTEX_1_PANEL_42)
				SET_VISIBLE(false, VERTEX_2_PANEL_49)
				SET_VISIBLE(false, VERTEX_3_PANEL_56)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_41].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_42].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_35)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_42)
				SET_VISIBLE(false, VERTEX_2_PANEL_49)
				SET_VISIBLE(false, VERTEX_3_PANEL_56)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_48].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_49].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_35)
				SET_VISIBLE(false, VERTEX_1_PANEL_42)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_49)
				SET_VISIBLE(false, VERTEX_3_PANEL_56)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_55].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_56].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_35)
				SET_VISIBLE(false, VERTEX_1_PANEL_42)
				SET_VISIBLE(false, VERTEX_2_PANEL_49)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_56)
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

void FireRaymarchingUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_DT_PANEL_3].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_dt, U_DT_LABEL_1)
		}
	}

	if (auto directPanel = mControls[U_INTENSITY_PANEL_7].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_intensity, U_INTENSITY_LABEL_5)
		}
	}

	if (auto directPanel = mControls[U_COVERING_PANEL_11].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_covering, U_COVERING_LABEL_9)
		}
	}

	if (auto directPanel = mControls[U_TEXEL_PANEL_16].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_texel[0], U_TEXEL_LABEL_13)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_texel[1], U_TEXEL_LABEL_14)
		}
	}

	if (auto directPanel = mControls[U_COLOR_HOT_PANEL_22].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_hot[0], U_COLOR_HOT_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_hot[1], U_COLOR_HOT_LABEL_19)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_hot[2], U_COLOR_HOT_LABEL_20)
		}
	}

	if (auto directPanel = mControls[U_COLOR_COLD_PANEL_28].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_cold[0], U_COLOR_COLD_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_cold[1], U_COLOR_COLD_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_cold[2], U_COLOR_COLD_LABEL_26)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_35].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_31)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_33)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_42].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_37)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_38)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_39)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_40)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_49].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_44)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_45)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_46)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_47)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_56].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_51)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_52)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_53)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_54)
		}
	}
}

void FireRaymarchingUi::Set_u_dt(const float& a_u_dt)
{
	m_u_dt = a_u_dt;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_dt, U_DT_SLIDER_1)
	//
	mIsRestoreNeed = false;
}

const float& FireRaymarchingUi::Get_u_dt() const
{
	return m_u_dt;
}

void FireRaymarchingUi::Set_u_intensity(const float& a_u_intensity)
{
	m_u_intensity = a_u_intensity;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_intensity, U_INTENSITY_SLIDER_5)
	//
	mIsRestoreNeed = false;
}

const float& FireRaymarchingUi::Get_u_intensity() const
{
	return m_u_intensity;
}

void FireRaymarchingUi::Set_u_covering(const float& a_u_covering)
{
	m_u_covering = a_u_covering;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_covering, U_COVERING_SLIDER_9)
	//
	mIsRestoreNeed = false;
}

const float& FireRaymarchingUi::Get_u_covering() const
{
	return m_u_covering;
}

void FireRaymarchingUi::Set_u_texel(const eps::math::vec2& a_u_texel)
{
	m_u_texel = a_u_texel;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_texel[0], U_TEXEL_SLIDER_13)
	SET_REAL_VALUE_AT_SLIDER(m_u_texel[1], U_TEXEL_SLIDER_14)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec2& FireRaymarchingUi::Get_u_texel() const
{
	return m_u_texel;
}

void FireRaymarchingUi::Set_u_color_hot(const eps::math::vec3& a_u_color_hot)
{
	m_u_color_hot = a_u_color_hot;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_hot[0], U_COLOR_HOT_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_hot[1], U_COLOR_HOT_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_hot[2], U_COLOR_HOT_SLIDER_20)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& FireRaymarchingUi::Get_u_color_hot() const
{
	return m_u_color_hot;
}

void FireRaymarchingUi::Set_u_color_cold(const eps::math::vec3& a_u_color_cold)
{
	m_u_color_cold = a_u_color_cold;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_cold[0], U_COLOR_COLD_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_cold[1], U_COLOR_COLD_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_cold[2], U_COLOR_COLD_SLIDER_26)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& FireRaymarchingUi::Get_u_color_cold() const
{
	return m_u_color_cold;
}

void FireRaymarchingUi::SetVertices(const std::vector<FireRaymarchingVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_33)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_37)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_38)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_39)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_40)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_44)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_45)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_46)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_47)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_51)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_52)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_53)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_54)
	//
	mIsRestoreNeed = false;
}

const std::vector<FireRaymarchingVertex>& FireRaymarchingUi::GetVertices() const
{
	return mVertices;
}

bool FireRaymarchingUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& FireRaymarchingUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_DT_SLIDER_1:
			return m_u_dt;

		case U_INTENSITY_SLIDER_5:
			return m_u_intensity;

		case U_COVERING_SLIDER_9:
			return m_u_covering;

		case U_TEXEL_SLIDER_13:
			return m_u_texel[0];

		case U_TEXEL_SLIDER_14:
			return m_u_texel[1];

		case U_COLOR_HOT_SLIDER_18:
			return m_u_color_hot[0];

		case U_COLOR_HOT_SLIDER_19:
			return m_u_color_hot[1];

		case U_COLOR_HOT_SLIDER_20:
			return m_u_color_hot[2];

		case U_COLOR_COLD_SLIDER_24:
			return m_u_color_cold[0];

		case U_COLOR_COLD_SLIDER_25:
			return m_u_color_cold[1];

		case U_COLOR_COLD_SLIDER_26:
			return m_u_color_cold[2];

		case VERTEX_0_SLIDER_30:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_31:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_0_SLIDER_32:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_33:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_37:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_38:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_1_SLIDER_39:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_40:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_44:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_45:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_2_SLIDER_46:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_47:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_51:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_52:
			return mVertices[3].a_vertex_xy.y;

		case VERTEX_3_SLIDER_53:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_54:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
