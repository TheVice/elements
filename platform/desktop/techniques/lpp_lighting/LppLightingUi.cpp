#include "LppLightingUi.h"
#include "LppLightingControls.h"
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
RTTI_DEFINITIONS(LppLightingUi)

LppLightingUi::LppLightingUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_matrix_mvp(),
	m_u_camera_view_param(),
	m_u_camera_near(),
	m_u_camera_far(),
	m_u_light_pos(),
	m_u_light_intensity(),
	m_u_light_inv_range_square(),
	mVertices(
{
	LppLightingVertex(),
					  LppLightingVertex(),
					  LppLightingVertex(),
					  LppLightingVertex()
})
{
}

LppLightingUi::~LppLightingUi() = default;

bool LppLightingUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_MATRIX_MVP_BUTTON_13)
	IS_CONTROL_EXIST(U_CAMERA_VIEW_PARAM_BUTTON_18)
	IS_CONTROL_EXIST(U_CAMERA_NEAR_BUTTON_22)
	IS_CONTROL_EXIST(U_CAMERA_FAR_BUTTON_26)
	IS_CONTROL_EXIST(U_LIGHT_POS_BUTTON_32)
	IS_CONTROL_EXIST(U_LIGHT_INTENSITY_BUTTON_38)
	IS_CONTROL_EXIST(U_LIGHT_INV_RANGE_SQUARE_BUTTON_42)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_48)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_54)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_60)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_66)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_PANEL_14)
	IS_CONTROL_EXIST(U_CAMERA_VIEW_PARAM_PANEL_19)
	IS_CONTROL_EXIST(U_CAMERA_NEAR_PANEL_23)
	IS_CONTROL_EXIST(U_CAMERA_FAR_PANEL_27)
	IS_CONTROL_EXIST(U_LIGHT_POS_PANEL_33)
	IS_CONTROL_EXIST(U_LIGHT_INTENSITY_PANEL_39)
	IS_CONTROL_EXIST(U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_49)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_55)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_61)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_67)
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
	IS_CONTROL_EXIST(U_CAMERA_VIEW_PARAM_LABEL_16)
	IS_CONTROL_EXIST(U_CAMERA_VIEW_PARAM_LABEL_17)
	IS_CONTROL_EXIST(U_CAMERA_VIEW_PARAM_LABEL_20)
	IS_CONTROL_EXIST(U_CAMERA_NEAR_LABEL_21)
	IS_CONTROL_EXIST(U_CAMERA_NEAR_LABEL_24)
	IS_CONTROL_EXIST(U_CAMERA_FAR_LABEL_25)
	IS_CONTROL_EXIST(U_CAMERA_FAR_LABEL_28)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_29)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_30)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_31)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_34)
	IS_CONTROL_EXIST(U_LIGHT_INTENSITY_LABEL_35)
	IS_CONTROL_EXIST(U_LIGHT_INTENSITY_LABEL_36)
	IS_CONTROL_EXIST(U_LIGHT_INTENSITY_LABEL_37)
	IS_CONTROL_EXIST(U_LIGHT_INTENSITY_LABEL_40)
	IS_CONTROL_EXIST(U_LIGHT_INV_RANGE_SQUARE_LABEL_41)
	IS_CONTROL_EXIST(U_LIGHT_INV_RANGE_SQUARE_LABEL_44)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_47)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_50)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_51)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_52)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_53)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_56)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_57)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_58)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_59)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_62)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_63)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_64)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_65)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_68)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_MVP_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_MATRIX_MVP_PANEL_14].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_CAMERA_VIEW_PARAM_PANEL_19)
				SET_VISIBLE(false, U_CAMERA_NEAR_PANEL_23)
				SET_VISIBLE(false, U_CAMERA_FAR_PANEL_27)
				SET_VISIBLE(false, U_LIGHT_POS_PANEL_33)
				SET_VISIBLE(false, U_LIGHT_INTENSITY_PANEL_39)
				SET_VISIBLE(false, U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_CAMERA_VIEW_PARAM_BUTTON_18].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_CAMERA_VIEW_PARAM_PANEL_19].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(!directPanel->get_visible(), U_CAMERA_VIEW_PARAM_PANEL_19)
				SET_VISIBLE(false, U_CAMERA_NEAR_PANEL_23)
				SET_VISIBLE(false, U_CAMERA_FAR_PANEL_27)
				SET_VISIBLE(false, U_LIGHT_POS_PANEL_33)
				SET_VISIBLE(false, U_LIGHT_INTENSITY_PANEL_39)
				SET_VISIBLE(false, U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_CAMERA_NEAR_BUTTON_22].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_CAMERA_NEAR_PANEL_23].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_CAMERA_VIEW_PARAM_PANEL_19)
				SET_VISIBLE(!directPanel->get_visible(), U_CAMERA_NEAR_PANEL_23)
				SET_VISIBLE(false, U_CAMERA_FAR_PANEL_27)
				SET_VISIBLE(false, U_LIGHT_POS_PANEL_33)
				SET_VISIBLE(false, U_LIGHT_INTENSITY_PANEL_39)
				SET_VISIBLE(false, U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_CAMERA_FAR_BUTTON_26].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_CAMERA_FAR_PANEL_27].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_CAMERA_VIEW_PARAM_PANEL_19)
				SET_VISIBLE(false, U_CAMERA_NEAR_PANEL_23)
				SET_VISIBLE(!directPanel->get_visible(), U_CAMERA_FAR_PANEL_27)
				SET_VISIBLE(false, U_LIGHT_POS_PANEL_33)
				SET_VISIBLE(false, U_LIGHT_INTENSITY_PANEL_39)
				SET_VISIBLE(false, U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_LIGHT_POS_BUTTON_32].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_LIGHT_POS_PANEL_33].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_CAMERA_VIEW_PARAM_PANEL_19)
				SET_VISIBLE(false, U_CAMERA_NEAR_PANEL_23)
				SET_VISIBLE(false, U_CAMERA_FAR_PANEL_27)
				SET_VISIBLE(!directPanel->get_visible(), U_LIGHT_POS_PANEL_33)
				SET_VISIBLE(false, U_LIGHT_INTENSITY_PANEL_39)
				SET_VISIBLE(false, U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_LIGHT_INTENSITY_BUTTON_38].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_LIGHT_INTENSITY_PANEL_39].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_CAMERA_VIEW_PARAM_PANEL_19)
				SET_VISIBLE(false, U_CAMERA_NEAR_PANEL_23)
				SET_VISIBLE(false, U_CAMERA_FAR_PANEL_27)
				SET_VISIBLE(false, U_LIGHT_POS_PANEL_33)
				SET_VISIBLE(!directPanel->get_visible(), U_LIGHT_INTENSITY_PANEL_39)
				SET_VISIBLE(false, U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_LIGHT_INV_RANGE_SQUARE_BUTTON_42].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_LIGHT_INV_RANGE_SQUARE_PANEL_43].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_CAMERA_VIEW_PARAM_PANEL_19)
				SET_VISIBLE(false, U_CAMERA_NEAR_PANEL_23)
				SET_VISIBLE(false, U_CAMERA_FAR_PANEL_27)
				SET_VISIBLE(false, U_LIGHT_POS_PANEL_33)
				SET_VISIBLE(false, U_LIGHT_INTENSITY_PANEL_39)
				SET_VISIBLE(!directPanel->get_visible(), U_LIGHT_INV_RANGE_SQUARE_PANEL_43)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_48].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_49].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_49)
				SET_VISIBLE(false, VERTEX_1_PANEL_55)
				SET_VISIBLE(false, VERTEX_2_PANEL_61)
				SET_VISIBLE(false, VERTEX_3_PANEL_67)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_54].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_55].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_49)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_55)
				SET_VISIBLE(false, VERTEX_2_PANEL_61)
				SET_VISIBLE(false, VERTEX_3_PANEL_67)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_60].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_61].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_49)
				SET_VISIBLE(false, VERTEX_1_PANEL_55)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_61)
				SET_VISIBLE(false, VERTEX_3_PANEL_67)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_66].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_67].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_49)
				SET_VISIBLE(false, VERTEX_1_PANEL_55)
				SET_VISIBLE(false, VERTEX_2_PANEL_61)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_67)
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

void LppLightingUi::Update()
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

	if (auto directPanel = mControls[U_CAMERA_VIEW_PARAM_PANEL_19].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_camera_view_param[0], U_CAMERA_VIEW_PARAM_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_camera_view_param[1], U_CAMERA_VIEW_PARAM_LABEL_17)
		}
	}

	if (auto directPanel = mControls[U_CAMERA_NEAR_PANEL_23].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_camera_near, U_CAMERA_NEAR_LABEL_21)
		}
	}

	if (auto directPanel = mControls[U_CAMERA_FAR_PANEL_27].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_camera_far, U_CAMERA_FAR_LABEL_25)
		}
	}

	if (auto directPanel = mControls[U_LIGHT_POS_PANEL_33].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_pos[0], U_LIGHT_POS_LABEL_29)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_pos[1], U_LIGHT_POS_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_pos[2], U_LIGHT_POS_LABEL_31)
		}
	}

	if (auto directPanel = mControls[U_LIGHT_INTENSITY_PANEL_39].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_intensity[0], U_LIGHT_INTENSITY_LABEL_35)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_intensity[1], U_LIGHT_INTENSITY_LABEL_36)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_intensity[2], U_LIGHT_INTENSITY_LABEL_37)
		}
	}

	if (auto directPanel = mControls[U_LIGHT_INV_RANGE_SQUARE_PANEL_43].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_light_inv_range_square, U_LIGHT_INV_RANGE_SQUARE_LABEL_41)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_49].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VERTEX_0_LABEL_45)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VERTEX_0_LABEL_46)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VERTEX_0_LABEL_47)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_55].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VERTEX_1_LABEL_51)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VERTEX_1_LABEL_52)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VERTEX_1_LABEL_53)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_61].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VERTEX_2_LABEL_57)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VERTEX_2_LABEL_58)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VERTEX_2_LABEL_59)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_67].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VERTEX_3_LABEL_63)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VERTEX_3_LABEL_64)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VERTEX_3_LABEL_65)
		}
	}
}

void LppLightingUi::Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp)
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

const eps::math::mat4& LppLightingUi::Get_u_matrix_mvp() const
{
	return m_u_matrix_mvp;
}

void LppLightingUi::Set_u_camera_view_param(const eps::math::vec2& a_u_camera_view_param)
{
	m_u_camera_view_param = a_u_camera_view_param;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_camera_view_param[0], U_CAMERA_VIEW_PARAM_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(m_u_camera_view_param[1], U_CAMERA_VIEW_PARAM_SLIDER_17)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec2& LppLightingUi::Get_u_camera_view_param() const
{
	return m_u_camera_view_param;
}

void LppLightingUi::Set_u_camera_near(const float& a_u_camera_near)
{
	m_u_camera_near = a_u_camera_near;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_camera_near, U_CAMERA_NEAR_SLIDER_21)
	//
	mIsRestoreNeed = false;
}

const float& LppLightingUi::Get_u_camera_near() const
{
	return m_u_camera_near;
}

void LppLightingUi::Set_u_camera_far(const float& a_u_camera_far)
{
	m_u_camera_far = a_u_camera_far;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_camera_far, U_CAMERA_FAR_SLIDER_25)
	//
	mIsRestoreNeed = false;
}

const float& LppLightingUi::Get_u_camera_far() const
{
	return m_u_camera_far;
}

void LppLightingUi::Set_u_light_pos(const eps::math::vec3& a_u_light_pos)
{
	m_u_light_pos = a_u_light_pos;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_light_pos[0], U_LIGHT_POS_SLIDER_29)
	SET_REAL_VALUE_AT_SLIDER(m_u_light_pos[1], U_LIGHT_POS_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(m_u_light_pos[2], U_LIGHT_POS_SLIDER_31)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& LppLightingUi::Get_u_light_pos() const
{
	return m_u_light_pos;
}

void LppLightingUi::Set_u_light_intensity(const eps::math::vec3& a_u_light_intensity)
{
	m_u_light_intensity = a_u_light_intensity;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_light_intensity[0], U_LIGHT_INTENSITY_SLIDER_35)
	SET_REAL_VALUE_AT_SLIDER(m_u_light_intensity[1], U_LIGHT_INTENSITY_SLIDER_36)
	SET_REAL_VALUE_AT_SLIDER(m_u_light_intensity[2], U_LIGHT_INTENSITY_SLIDER_37)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& LppLightingUi::Get_u_light_intensity() const
{
	return m_u_light_intensity;
}

void LppLightingUi::Set_u_light_inv_range_square(const float& a_u_light_inv_range_square)
{
	m_u_light_inv_range_square = a_u_light_inv_range_square;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_light_inv_range_square, U_LIGHT_INV_RANGE_SQUARE_SLIDER_41)
	//
	mIsRestoreNeed = false;
}

const float& LppLightingUi::Get_u_light_inv_range_square() const
{
	return m_u_light_inv_range_square;
}

void LppLightingUi::SetVertices(const std::vector<LppLightingVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.x, VERTEX_0_SLIDER_45)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.y, VERTEX_0_SLIDER_46)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.z, VERTEX_0_SLIDER_47)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.x, VERTEX_1_SLIDER_51)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.y, VERTEX_1_SLIDER_52)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.z, VERTEX_1_SLIDER_53)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.x, VERTEX_2_SLIDER_57)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.y, VERTEX_2_SLIDER_58)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.z, VERTEX_2_SLIDER_59)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.x, VERTEX_3_SLIDER_63)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.y, VERTEX_3_SLIDER_64)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.z, VERTEX_3_SLIDER_65)
	//
	mIsRestoreNeed = false;
}

const std::vector<LppLightingVertex>& LppLightingUi::GetVertices() const
{
	return mVertices;
}

bool LppLightingUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& LppLightingUi::GetValueBySliderId(int aSliderId)
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

		case U_CAMERA_VIEW_PARAM_SLIDER_16:
			return m_u_camera_view_param[0];

		case U_CAMERA_VIEW_PARAM_SLIDER_17:
			return m_u_camera_view_param[1];

		case U_CAMERA_NEAR_SLIDER_21:
			return m_u_camera_near;

		case U_CAMERA_FAR_SLIDER_25:
			return m_u_camera_far;

		case U_LIGHT_POS_SLIDER_29:
			return m_u_light_pos[0];

		case U_LIGHT_POS_SLIDER_30:
			return m_u_light_pos[1];

		case U_LIGHT_POS_SLIDER_31:
			return m_u_light_pos[2];

		case U_LIGHT_INTENSITY_SLIDER_35:
			return m_u_light_intensity[0];

		case U_LIGHT_INTENSITY_SLIDER_36:
			return m_u_light_intensity[1];

		case U_LIGHT_INTENSITY_SLIDER_37:
			return m_u_light_intensity[2];

		case U_LIGHT_INV_RANGE_SQUARE_SLIDER_41:
			return m_u_light_inv_range_square;

		case VERTEX_0_SLIDER_45:
			return mVertices[0].a_vertex_pos.x;

		case VERTEX_0_SLIDER_46:
			return mVertices[0].a_vertex_pos.y;

		case VERTEX_0_SLIDER_47:
			return mVertices[0].a_vertex_pos.z;

		case VERTEX_1_SLIDER_51:
			return mVertices[1].a_vertex_pos.x;

		case VERTEX_1_SLIDER_52:
			return mVertices[1].a_vertex_pos.y;

		case VERTEX_1_SLIDER_53:
			return mVertices[1].a_vertex_pos.z;

		case VERTEX_2_SLIDER_57:
			return mVertices[2].a_vertex_pos.x;

		case VERTEX_2_SLIDER_58:
			return mVertices[2].a_vertex_pos.y;

		case VERTEX_2_SLIDER_59:
			return mVertices[2].a_vertex_pos.z;

		case VERTEX_3_SLIDER_63:
			return mVertices[3].a_vertex_pos.x;

		case VERTEX_3_SLIDER_64:
			return mVertices[3].a_vertex_pos.y;

		case VERTEX_3_SLIDER_65:
			return mVertices[3].a_vertex_pos.z;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
