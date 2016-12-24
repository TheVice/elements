
#include "LightScatteredUi.h"
#include "LightScatteredControls.h"
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
RTTI_DEFINITIONS(LightScatteredUi)

LightScatteredUi::LightScatteredUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_exposure(),
	m_u_decay(),
	m_u_density(),
	m_u_weight(),
	m_u_light_position(),
	mVertices(
{
	LightScatteredVertex(),
						 LightScatteredVertex(),
						 LightScatteredVertex(),
						 LightScatteredVertex()
})
{
}

LightScatteredUi::~LightScatteredUi() = default;

bool LightScatteredUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_EXPOSURE_BUTTON_2)
	IS_CONTROL_EXIST(U_DECAY_BUTTON_6)
	IS_CONTROL_EXIST(U_DENSITY_BUTTON_10)
	IS_CONTROL_EXIST(U_WEIGHT_BUTTON_14)
	IS_CONTROL_EXIST(U_LIGHT_POSITION_BUTTON_19)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_26)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_33)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_40)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_47)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	IS_CONTROL_EXIST(U_EXPOSURE_PANEL_3)
	IS_CONTROL_EXIST(U_DECAY_PANEL_7)
	IS_CONTROL_EXIST(U_DENSITY_PANEL_11)
	IS_CONTROL_EXIST(U_WEIGHT_PANEL_15)
	IS_CONTROL_EXIST(U_LIGHT_POSITION_PANEL_20)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_27)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_34)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_41)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_48)
	//
	IS_CONTROL_EXIST(U_EXPOSURE_LABEL_1)
	IS_CONTROL_EXIST(U_EXPOSURE_LABEL_4)
	IS_CONTROL_EXIST(U_DECAY_LABEL_5)
	IS_CONTROL_EXIST(U_DECAY_LABEL_8)
	IS_CONTROL_EXIST(U_DENSITY_LABEL_9)
	IS_CONTROL_EXIST(U_DENSITY_LABEL_12)
	IS_CONTROL_EXIST(U_WEIGHT_LABEL_13)
	IS_CONTROL_EXIST(U_WEIGHT_LABEL_16)
	IS_CONTROL_EXIST(U_LIGHT_POSITION_LABEL_17)
	IS_CONTROL_EXIST(U_LIGHT_POSITION_LABEL_18)
	IS_CONTROL_EXIST(U_LIGHT_POSITION_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_35)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_36)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_37)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_38)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_39)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_42)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_43)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_44)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_49)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_EXPOSURE_BUTTON_2].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_EXPOSURE_PANEL_3].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_EXPOSURE_PANEL_3)
				SET_VISIBLE(false, U_DECAY_PANEL_7)
				SET_VISIBLE(false, U_DENSITY_PANEL_11)
				SET_VISIBLE(false, U_WEIGHT_PANEL_15)
				SET_VISIBLE(false, U_LIGHT_POSITION_PANEL_20)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_DECAY_BUTTON_6].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_DECAY_PANEL_7].lock())
			{
				SET_VISIBLE(false, U_EXPOSURE_PANEL_3)
				SET_VISIBLE(!directPanel->get_visible(), U_DECAY_PANEL_7)
				SET_VISIBLE(false, U_DENSITY_PANEL_11)
				SET_VISIBLE(false, U_WEIGHT_PANEL_15)
				SET_VISIBLE(false, U_LIGHT_POSITION_PANEL_20)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_DENSITY_BUTTON_10].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_DENSITY_PANEL_11].lock())
			{
				SET_VISIBLE(false, U_EXPOSURE_PANEL_3)
				SET_VISIBLE(false, U_DECAY_PANEL_7)
				SET_VISIBLE(!directPanel->get_visible(), U_DENSITY_PANEL_11)
				SET_VISIBLE(false, U_WEIGHT_PANEL_15)
				SET_VISIBLE(false, U_LIGHT_POSITION_PANEL_20)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_WEIGHT_BUTTON_14].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_WEIGHT_PANEL_15].lock())
			{
				SET_VISIBLE(false, U_EXPOSURE_PANEL_3)
				SET_VISIBLE(false, U_DECAY_PANEL_7)
				SET_VISIBLE(false, U_DENSITY_PANEL_11)
				SET_VISIBLE(!directPanel->get_visible(), U_WEIGHT_PANEL_15)
				SET_VISIBLE(false, U_LIGHT_POSITION_PANEL_20)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_LIGHT_POSITION_BUTTON_19].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_LIGHT_POSITION_PANEL_20].lock())
			{
				SET_VISIBLE(false, U_EXPOSURE_PANEL_3)
				SET_VISIBLE(false, U_DECAY_PANEL_7)
				SET_VISIBLE(false, U_DENSITY_PANEL_11)
				SET_VISIBLE(false, U_WEIGHT_PANEL_15)
				SET_VISIBLE(!directPanel->get_visible(), U_LIGHT_POSITION_PANEL_20)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_26].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_27].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_27)
				SET_VISIBLE(false, VERTEX_1_PANEL_34)
				SET_VISIBLE(false, VERTEX_2_PANEL_41)
				SET_VISIBLE(false, VERTEX_3_PANEL_48)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_33].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_34].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_27)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_34)
				SET_VISIBLE(false, VERTEX_2_PANEL_41)
				SET_VISIBLE(false, VERTEX_3_PANEL_48)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_40].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_41].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_27)
				SET_VISIBLE(false, VERTEX_1_PANEL_34)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_41)
				SET_VISIBLE(false, VERTEX_3_PANEL_48)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_47].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_48].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_27)
				SET_VISIBLE(false, VERTEX_1_PANEL_34)
				SET_VISIBLE(false, VERTEX_2_PANEL_41)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_48)
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

void LightScatteredUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_EXPOSURE_PANEL_3].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_exposure, U_EXPOSURE_LABEL_1)
		}
	}

	if (auto directPanel = mControls[U_DECAY_PANEL_7].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_decay, U_DECAY_LABEL_5)
		}
	}

	if (auto directPanel = mControls[U_DENSITY_PANEL_11].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_density, U_DENSITY_LABEL_9)
		}
	}

	if (auto directPanel = mControls[U_WEIGHT_PANEL_15].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_weight, U_WEIGHT_LABEL_13)
		}
	}

	if (auto directPanel = mControls[U_LIGHT_POSITION_PANEL_20].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_position[0], U_LIGHT_POSITION_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_position[1], U_LIGHT_POSITION_LABEL_18)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_27].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_25)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_34].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_29)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_31)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_32)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_41].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_36)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_37)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_38)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_39)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_48].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_43)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_44)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_45)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_46)
		}
	}
}

void LightScatteredUi::Set_u_exposure(const float& a_u_exposure)
{
	m_u_exposure = a_u_exposure;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_exposure, U_EXPOSURE_SLIDER_1)
	//
	mIsRestoreNeed = false;
}

const float& LightScatteredUi::Get_u_exposure() const
{
	return m_u_exposure;
}

void LightScatteredUi::Set_u_decay(const float& a_u_decay)
{
	m_u_decay = a_u_decay;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_decay, U_DECAY_SLIDER_5)
	//
	mIsRestoreNeed = false;
}

const float& LightScatteredUi::Get_u_decay() const
{
	return m_u_decay;
}

void LightScatteredUi::Set_u_density(const float& a_u_density)
{
	m_u_density = a_u_density;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_density, U_DENSITY_SLIDER_9)
	//
	mIsRestoreNeed = false;
}

const float& LightScatteredUi::Get_u_density() const
{
	return m_u_density;
}

void LightScatteredUi::Set_u_weight(const float& a_u_weight)
{
	m_u_weight = a_u_weight;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_weight, U_WEIGHT_SLIDER_13)
	//
	mIsRestoreNeed = false;
}

const float& LightScatteredUi::Get_u_weight() const
{
	return m_u_weight;
}

void LightScatteredUi::Set_u_light_position(const eps::math::vec2& a_u_light_position)
{
	m_u_light_position = a_u_light_position;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_light_position[0], U_LIGHT_POSITION_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(m_u_light_position[1], U_LIGHT_POSITION_SLIDER_18)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec2& LightScatteredUi::Get_u_light_position() const
{
	return m_u_light_position;
}

void LightScatteredUi::SetVertices(const std::vector<LightScatteredVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_29)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_36)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_37)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_38)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_39)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_43)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_44)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_45)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_46)
	//
	mIsRestoreNeed = false;
}

const std::vector<LightScatteredVertex>& LightScatteredUi::GetVertices() const
{
	return mVertices;
}

bool LightScatteredUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& LightScatteredUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_EXPOSURE_SLIDER_1:
			return m_u_exposure;

		case U_DECAY_SLIDER_5:
			return m_u_decay;

		case U_DENSITY_SLIDER_9:
			return m_u_density;

		case U_WEIGHT_SLIDER_13:
			return m_u_weight;

		case U_LIGHT_POSITION_SLIDER_17:
			return m_u_light_position[0];

		case U_LIGHT_POSITION_SLIDER_18:
			return m_u_light_position[1];

		case VERTEX_0_SLIDER_22:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_23:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_0_SLIDER_24:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_25:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_29:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_30:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_1_SLIDER_31:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_32:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_36:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_37:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_2_SLIDER_38:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_39:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_43:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_44:
			return mVertices[3].a_vertex_xy.y;

		case VERTEX_3_SLIDER_45:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_46:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
