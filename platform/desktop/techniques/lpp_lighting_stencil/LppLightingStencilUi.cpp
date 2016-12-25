#include "LppLightingStencilUi.h"
#include "LppLightingStencilControls.h"
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
RTTI_DEFINITIONS(LppLightingStencilUi)

LppLightingStencilUi::LppLightingStencilUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_matrix_mvp(),
	mVertices(
{
	LppLightingStencilVertex(),
							 LppLightingStencilVertex(),
							 LppLightingStencilVertex(),
							 LppLightingStencilVertex()
})
{
}

LppLightingStencilUi::~LppLightingStencilUi() = default;

bool LppLightingStencilUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_MATRIX_MVP_BUTTON_13)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_19)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_25)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_31)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_37)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_PANEL_14)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_20)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_26)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_32)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_38)
	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_1)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_2)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_3)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_4)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_5)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_6)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_7)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_8)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_9)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_10)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_11)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_12)
	IS_CONTROL_EXIST(U_MATRIX_MVP_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_17)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_18)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_27)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_34)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_35)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_36)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_39)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_MVP_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_MATRIX_MVP_PANEL_14].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_MATRIX_MVP_PANEL_14)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_19].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_20].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_20)
				SET_VISIBLE(false, VERTEX_1_PANEL_26)
				SET_VISIBLE(false, VERTEX_2_PANEL_32)
				SET_VISIBLE(false, VERTEX_3_PANEL_38)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_25].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_26].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_20)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_26)
				SET_VISIBLE(false, VERTEX_2_PANEL_32)
				SET_VISIBLE(false, VERTEX_3_PANEL_38)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_31].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_32].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_20)
				SET_VISIBLE(false, VERTEX_1_PANEL_26)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_32)
				SET_VISIBLE(false, VERTEX_3_PANEL_38)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_37].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_38].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_20)
				SET_VISIBLE(false, VERTEX_1_PANEL_26)
				SET_VISIBLE(false, VERTEX_2_PANEL_32)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_38)
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

void LppLightingStencilUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_MATRIX_MVP_PANEL_14].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[0][0], U_MATRIX_MVP_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[0][1], U_MATRIX_MVP_LABEL_2)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[0][2], U_MATRIX_MVP_LABEL_3)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[1][0], U_MATRIX_MVP_LABEL_4)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[1][1], U_MATRIX_MVP_LABEL_5)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[1][2], U_MATRIX_MVP_LABEL_6)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[2][0], U_MATRIX_MVP_LABEL_7)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[2][1], U_MATRIX_MVP_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[2][2], U_MATRIX_MVP_LABEL_9)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[3][0], U_MATRIX_MVP_LABEL_10)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[3][1], U_MATRIX_MVP_LABEL_11)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_mvp[3][2], U_MATRIX_MVP_LABEL_12)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_20].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VERTEX_0_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VERTEX_0_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VERTEX_0_LABEL_18)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_26].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VERTEX_1_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VERTEX_1_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VERTEX_1_LABEL_24)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_32].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VERTEX_2_LABEL_28)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VERTEX_2_LABEL_29)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VERTEX_2_LABEL_30)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_38].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VERTEX_3_LABEL_34)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VERTEX_3_LABEL_35)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VERTEX_3_LABEL_36)
		}
	}
}

void LppLightingStencilUi::Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp)
{
	m_u_matrix_mvp = a_u_matrix_mvp;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[0][0], U_MATRIX_MVP_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[0][1], U_MATRIX_MVP_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[0][2], U_MATRIX_MVP_SLIDER_3)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[1][0], U_MATRIX_MVP_SLIDER_4)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[1][1], U_MATRIX_MVP_SLIDER_5)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[1][2], U_MATRIX_MVP_SLIDER_6)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[2][0], U_MATRIX_MVP_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[2][1], U_MATRIX_MVP_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[2][2], U_MATRIX_MVP_SLIDER_9)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[3][0], U_MATRIX_MVP_SLIDER_10)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[3][1], U_MATRIX_MVP_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_mvp[3][2], U_MATRIX_MVP_SLIDER_12)
	//
	mIsRestoreNeed = false;
}

const eps::math::mat4& LppLightingStencilUi::Get_u_matrix_mvp() const
{
	return m_u_matrix_mvp;
}

void LppLightingStencilUi::SetVertices(const std::vector<LppLightingStencilVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.x, VERTEX_0_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.y, VERTEX_0_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.z, VERTEX_0_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.x, VERTEX_1_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.y, VERTEX_1_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.z, VERTEX_1_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.x, VERTEX_2_SLIDER_28)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.y, VERTEX_2_SLIDER_29)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.z, VERTEX_2_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.x, VERTEX_3_SLIDER_34)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.y, VERTEX_3_SLIDER_35)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.z, VERTEX_3_SLIDER_36)
	//
	mIsRestoreNeed = false;
}

const std::vector<LppLightingStencilVertex>& LppLightingStencilUi::GetVertices() const
{
	return mVertices;
}

bool LppLightingStencilUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& LppLightingStencilUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_MATRIX_MVP_SLIDER_1:
			return m_u_matrix_mvp[0][0];

		case U_MATRIX_MVP_SLIDER_2:
			return m_u_matrix_mvp[0][1];

		case U_MATRIX_MVP_SLIDER_3:
			return m_u_matrix_mvp[0][2];

		case U_MATRIX_MVP_SLIDER_4:
			return m_u_matrix_mvp[1][0];

		case U_MATRIX_MVP_SLIDER_5:
			return m_u_matrix_mvp[1][1];

		case U_MATRIX_MVP_SLIDER_6:
			return m_u_matrix_mvp[1][2];

		case U_MATRIX_MVP_SLIDER_7:
			return m_u_matrix_mvp[2][0];

		case U_MATRIX_MVP_SLIDER_8:
			return m_u_matrix_mvp[2][1];

		case U_MATRIX_MVP_SLIDER_9:
			return m_u_matrix_mvp[2][2];

		case U_MATRIX_MVP_SLIDER_10:
			return m_u_matrix_mvp[3][0];

		case U_MATRIX_MVP_SLIDER_11:
			return m_u_matrix_mvp[3][1];

		case U_MATRIX_MVP_SLIDER_12:
			return m_u_matrix_mvp[3][2];

		case VERTEX_0_SLIDER_16:
			return mVertices[0].a_vertex_pos.x;

		case VERTEX_0_SLIDER_17:
			return mVertices[0].a_vertex_pos.y;

		case VERTEX_0_SLIDER_18:
			return mVertices[0].a_vertex_pos.z;

		case VERTEX_1_SLIDER_22:
			return mVertices[1].a_vertex_pos.x;

		case VERTEX_1_SLIDER_23:
			return mVertices[1].a_vertex_pos.y;

		case VERTEX_1_SLIDER_24:
			return mVertices[1].a_vertex_pos.z;

		case VERTEX_2_SLIDER_28:
			return mVertices[2].a_vertex_pos.x;

		case VERTEX_2_SLIDER_29:
			return mVertices[2].a_vertex_pos.y;

		case VERTEX_2_SLIDER_30:
			return mVertices[2].a_vertex_pos.z;

		case VERTEX_3_SLIDER_34:
			return mVertices[3].a_vertex_pos.x;

		case VERTEX_3_SLIDER_35:
			return mVertices[3].a_vertex_pos.y;

		case VERTEX_3_SLIDER_36:
			return mVertices[3].a_vertex_pos.z;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
