#include "ParticlesUi.h"
#include "ParticlesControls.h"
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
RTTI_DEFINITIONS(ParticlesUi)

ParticlesUi::ParticlesUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_color_speed_down(),
	m_u_color_speed_up(),
	mVertices(
{
	ParticlesVertex(),
					ParticlesVertex(),
					ParticlesVertex(),
					ParticlesVertex()
})
{
}

ParticlesUi::~ParticlesUi() = default;

bool ParticlesUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_COLOR_SPEED_DOWN_BUTTON_4)
	IS_CONTROL_EXIST(U_COLOR_SPEED_UP_BUTTON_10)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_15)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_20)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_25)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_30)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_COLOR_SPEED_DOWN_PANEL_5)
	IS_CONTROL_EXIST(U_COLOR_SPEED_UP_PANEL_11)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_16)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_21)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_26)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_31)
	//
	IS_CONTROL_EXIST(U_COLOR_SPEED_DOWN_LABEL_1)
	IS_CONTROL_EXIST(U_COLOR_SPEED_DOWN_LABEL_2)
	IS_CONTROL_EXIST(U_COLOR_SPEED_DOWN_LABEL_3)
	IS_CONTROL_EXIST(U_COLOR_SPEED_DOWN_LABEL_6)
	IS_CONTROL_EXIST(U_COLOR_SPEED_UP_LABEL_7)
	IS_CONTROL_EXIST(U_COLOR_SPEED_UP_LABEL_8)
	IS_CONTROL_EXIST(U_COLOR_SPEED_UP_LABEL_9)
	IS_CONTROL_EXIST(U_COLOR_SPEED_UP_LABEL_12)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_13)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_14)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_17)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_18)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_27)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_32)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_COLOR_SPEED_DOWN_BUTTON_4].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_SPEED_DOWN_PANEL_5].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_SPEED_DOWN_PANEL_5)
				SET_VISIBLE(false, U_COLOR_SPEED_UP_PANEL_11)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_COLOR_SPEED_UP_BUTTON_10].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_SPEED_UP_PANEL_11].lock())
			{
				SET_VISIBLE(false, U_COLOR_SPEED_DOWN_PANEL_5)
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_SPEED_UP_PANEL_11)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_15].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_16].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_16)
				SET_VISIBLE(false, VERTEX_1_PANEL_21)
				SET_VISIBLE(false, VERTEX_2_PANEL_26)
				SET_VISIBLE(false, VERTEX_3_PANEL_31)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_20].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_21].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_16)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_21)
				SET_VISIBLE(false, VERTEX_2_PANEL_26)
				SET_VISIBLE(false, VERTEX_3_PANEL_31)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_25].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_26].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_16)
				SET_VISIBLE(false, VERTEX_1_PANEL_21)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_26)
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
				SET_VISIBLE(false, VERTEX_0_PANEL_16)
				SET_VISIBLE(false, VERTEX_1_PANEL_21)
				SET_VISIBLE(false, VERTEX_2_PANEL_26)
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

void ParticlesUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_COLOR_SPEED_DOWN_PANEL_5].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_speed_down[0], U_COLOR_SPEED_DOWN_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_speed_down[1], U_COLOR_SPEED_DOWN_LABEL_2)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_speed_down[2], U_COLOR_SPEED_DOWN_LABEL_3)
		}
	}

	if (auto directPanel = mControls[U_COLOR_SPEED_UP_PANEL_11].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_speed_up[0], U_COLOR_SPEED_UP_LABEL_7)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_speed_up[1], U_COLOR_SPEED_UP_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_speed_up[2], U_COLOR_SPEED_UP_LABEL_9)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_16].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_product_uv.x, VERTEX_0_LABEL_13)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_product_uv.y, VERTEX_0_LABEL_14)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_21].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_product_uv.x, VERTEX_1_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_product_uv.y, VERTEX_1_LABEL_19)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_26].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_product_uv.x, VERTEX_2_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_product_uv.y, VERTEX_2_LABEL_24)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_31].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_product_uv.x, VERTEX_3_LABEL_28)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_product_uv.y, VERTEX_3_LABEL_29)
		}
	}
}

void ParticlesUi::Set_u_color_speed_down(const eps::math::vec3& a_u_color_speed_down)
{
	m_u_color_speed_down = a_u_color_speed_down;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_speed_down[0], U_COLOR_SPEED_DOWN_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_speed_down[1], U_COLOR_SPEED_DOWN_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_speed_down[2], U_COLOR_SPEED_DOWN_SLIDER_3)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& ParticlesUi::Get_u_color_speed_down() const
{
	return m_u_color_speed_down;
}

void ParticlesUi::Set_u_color_speed_up(const eps::math::vec3& a_u_color_speed_up)
{
	m_u_color_speed_up = a_u_color_speed_up;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_speed_up[0], U_COLOR_SPEED_UP_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_speed_up[1], U_COLOR_SPEED_UP_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_speed_up[2], U_COLOR_SPEED_UP_SLIDER_9)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& ParticlesUi::Get_u_color_speed_up() const
{
	return m_u_color_speed_up;
}

void ParticlesUi::SetVertices(const std::vector<ParticlesVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_product_uv.x, VERTEX_0_SLIDER_13)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_product_uv.y, VERTEX_0_SLIDER_14)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_product_uv.x, VERTEX_1_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_product_uv.y, VERTEX_1_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_product_uv.x, VERTEX_2_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_product_uv.y, VERTEX_2_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_product_uv.x, VERTEX_3_SLIDER_28)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_product_uv.y, VERTEX_3_SLIDER_29)
	//
	mIsRestoreNeed = false;
}

const std::vector<ParticlesVertex>& ParticlesUi::GetVertices() const
{
	return mVertices;
}

bool ParticlesUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& ParticlesUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_COLOR_SPEED_DOWN_SLIDER_1:
			return m_u_color_speed_down[0];

		case U_COLOR_SPEED_DOWN_SLIDER_2:
			return m_u_color_speed_down[1];

		case U_COLOR_SPEED_DOWN_SLIDER_3:
			return m_u_color_speed_down[2];

		case U_COLOR_SPEED_UP_SLIDER_7:
			return m_u_color_speed_up[0];

		case U_COLOR_SPEED_UP_SLIDER_8:
			return m_u_color_speed_up[1];

		case U_COLOR_SPEED_UP_SLIDER_9:
			return m_u_color_speed_up[2];

		case VERTEX_0_SLIDER_13:
			return mVertices[0].a_product_uv.x;

		case VERTEX_0_SLIDER_14:
			return mVertices[0].a_product_uv.y;

		case VERTEX_1_SLIDER_18:
			return mVertices[1].a_product_uv.x;

		case VERTEX_1_SLIDER_19:
			return mVertices[1].a_product_uv.y;

		case VERTEX_2_SLIDER_23:
			return mVertices[2].a_product_uv.x;

		case VERTEX_2_SLIDER_24:
			return mVertices[2].a_product_uv.y;

		case VERTEX_3_SLIDER_28:
			return mVertices[3].a_product_uv.x;

		case VERTEX_3_SLIDER_29:
			return mVertices[3].a_product_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
