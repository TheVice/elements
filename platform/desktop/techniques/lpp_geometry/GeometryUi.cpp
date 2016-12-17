
#include "GeometryUi.h"
#include "GeometryControls.h"
#include <checkbox.h>
#include <SliderModel.h>
#include <elements/ui/controls/button.h>
#include <elements/ui/controls/check.h>
#include <elements/ui/controls/label.h>
#include <elements/ui/controls/panel.h>
#include <elements/ui/controls/slider.h>

namespace Rendering
{
RTTI_DEFINITIONS(GeometryUi)

GeometryUi::GeometryUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_matrix_mvp(),
	m_u_matrix_model_view(),
	m_u_has_map_normal(false),
	mVertices(
{
	GeometryVertex(),
				   GeometryVertex(),
				   GeometryVertex(),
				   GeometryVertex()
})
{
}

GeometryUi::~GeometryUi()
{
}

bool GeometryUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(RESTORE_BUTTON)
	IS_CONTROL_EXIST(U_MATRIX_MVP_BUTTON_13)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_BUTTON_28)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_43)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_57)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_71)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_85)
	//
	IS_CONTROL_EXIST(U_HAS_MAP_NORMAL_CHECK_31)
	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_PANEL_14)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_PANEL_29)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_44)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_58)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_72)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_86)
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
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_16)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_17)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_18)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_19)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_20)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_21)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_22)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_23)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_24)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_25)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_26)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_27)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_34)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_35)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_36)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_37)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_38)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_39)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_40)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_41)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_42)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_47)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_48)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_49)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_50)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_51)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_52)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_53)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_54)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_55)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_56)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_59)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_60)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_61)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_62)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_63)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_64)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_65)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_66)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_67)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_68)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_69)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_70)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_73)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_74)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_75)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_76)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_77)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_78)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_79)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_80)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_81)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_82)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_83)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_84)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_87)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[RESTORE_BUTTON].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			this->mIsRestoreNeed = !this->mIsRestoreNeed;
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_MVP_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_MATRIX_MVP_PANEL_14].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_MATRIX_MODEL_VIEW_PANEL_29)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_MATRIX_MODEL_VIEW_BUTTON_28].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_MATRIX_MODEL_VIEW_PANEL_29].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(!directPanel->get_visible(), U_MATRIX_MODEL_VIEW_PANEL_29)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_43].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_44].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_44)
				SET_VISIBLE(false, VERTEX_1_PANEL_58)
				SET_VISIBLE(false, VERTEX_2_PANEL_72)
				SET_VISIBLE(false, VERTEX_3_PANEL_86)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_57].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_58].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_44)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_58)
				SET_VISIBLE(false, VERTEX_2_PANEL_72)
				SET_VISIBLE(false, VERTEX_3_PANEL_86)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_71].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_72].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_44)
				SET_VISIBLE(false, VERTEX_1_PANEL_58)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_72)
				SET_VISIBLE(false, VERTEX_3_PANEL_86)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_85].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_86].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_44)
				SET_VISIBLE(false, VERTEX_1_PANEL_58)
				SET_VISIBLE(false, VERTEX_2_PANEL_72)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_86)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_HAS_MAP_NORMAL_CHECK_31].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			m_u_has_map_normal = !m_u_has_map_normal;
		});
	}

	return true;
}

void GeometryUi::Update()
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

	if (auto directPanel = mControls[U_MATRIX_MODEL_VIEW_PANEL_29].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[0][0], U_MATRIX_MODEL_VIEW_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[0][1], U_MATRIX_MODEL_VIEW_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[0][2], U_MATRIX_MODEL_VIEW_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[1][0], U_MATRIX_MODEL_VIEW_LABEL_19)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[1][1], U_MATRIX_MODEL_VIEW_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[1][2], U_MATRIX_MODEL_VIEW_LABEL_21)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[2][0], U_MATRIX_MODEL_VIEW_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[2][1], U_MATRIX_MODEL_VIEW_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[2][2], U_MATRIX_MODEL_VIEW_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[3][0], U_MATRIX_MODEL_VIEW_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[3][1], U_MATRIX_MODEL_VIEW_LABEL_26)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model_view[3][2], U_MATRIX_MODEL_VIEW_LABEL_27)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_44].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VERTEX_0_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VERTEX_0_LABEL_33)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VERTEX_0_LABEL_34)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.x, VERTEX_0_LABEL_35)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.y, VERTEX_0_LABEL_36)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.z, VERTEX_0_LABEL_37)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.x, VERTEX_0_LABEL_38)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.y, VERTEX_0_LABEL_39)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.z, VERTEX_0_LABEL_40)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_41)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_42)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_58].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VERTEX_1_LABEL_46)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VERTEX_1_LABEL_47)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VERTEX_1_LABEL_48)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.x, VERTEX_1_LABEL_49)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.y, VERTEX_1_LABEL_50)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.z, VERTEX_1_LABEL_51)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.x, VERTEX_1_LABEL_52)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.y, VERTEX_1_LABEL_53)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.z, VERTEX_1_LABEL_54)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_55)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_56)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_72].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VERTEX_2_LABEL_60)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VERTEX_2_LABEL_61)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VERTEX_2_LABEL_62)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.x, VERTEX_2_LABEL_63)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.y, VERTEX_2_LABEL_64)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.z, VERTEX_2_LABEL_65)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.x, VERTEX_2_LABEL_66)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.y, VERTEX_2_LABEL_67)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.z, VERTEX_2_LABEL_68)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_69)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_70)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_86].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VERTEX_3_LABEL_74)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VERTEX_3_LABEL_75)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VERTEX_3_LABEL_76)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.x, VERTEX_3_LABEL_77)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.y, VERTEX_3_LABEL_78)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.z, VERTEX_3_LABEL_79)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.x, VERTEX_3_LABEL_80)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.y, VERTEX_3_LABEL_81)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.z, VERTEX_3_LABEL_82)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_83)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_84)
		}
	}
}

void GeometryUi::Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp)
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

const eps::math::mat4& GeometryUi::Get_u_matrix_mvp() const
{
	return m_u_matrix_mvp;
}

void GeometryUi::Set_u_matrix_model_view(const eps::math::mat4& a_u_matrix_model_view)
{
	m_u_matrix_model_view = a_u_matrix_model_view;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[0][0], U_MATRIX_MODEL_VIEW_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[0][1], U_MATRIX_MODEL_VIEW_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[0][2], U_MATRIX_MODEL_VIEW_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[1][0], U_MATRIX_MODEL_VIEW_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[1][1], U_MATRIX_MODEL_VIEW_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[1][2], U_MATRIX_MODEL_VIEW_SLIDER_21)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[2][0], U_MATRIX_MODEL_VIEW_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[2][1], U_MATRIX_MODEL_VIEW_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[2][2], U_MATRIX_MODEL_VIEW_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[3][0], U_MATRIX_MODEL_VIEW_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[3][1], U_MATRIX_MODEL_VIEW_SLIDER_26)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model_view[3][2], U_MATRIX_MODEL_VIEW_SLIDER_27)
	//
	mIsRestoreNeed = false;
}

const eps::math::mat4& GeometryUi::Get_u_matrix_model_view() const
{
	return m_u_matrix_model_view;
}

/*void GeometryUi::Set_u_has_map_normal(bool a_u_has_map_normal)
{
	//m_u_has_map_normal = a_u_has_map_normal;
	//
	mIsRestoreNeed = false;
}*/

bool GeometryUi::Get_u_has_map_normal() const
{
	return m_u_has_map_normal;
}

void GeometryUi::SetVertices(const std::vector<GeometryVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.x, VERTEX_0_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.y, VERTEX_0_SLIDER_33)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.z, VERTEX_0_SLIDER_34)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_normal.x, VERTEX_0_SLIDER_35)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_normal.y, VERTEX_0_SLIDER_36)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_normal.z, VERTEX_0_SLIDER_37)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_tangent.x, VERTEX_0_SLIDER_38)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_tangent.y, VERTEX_0_SLIDER_39)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_tangent.z, VERTEX_0_SLIDER_40)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_41)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_42)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.x, VERTEX_1_SLIDER_46)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.y, VERTEX_1_SLIDER_47)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.z, VERTEX_1_SLIDER_48)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_normal.x, VERTEX_1_SLIDER_49)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_normal.y, VERTEX_1_SLIDER_50)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_normal.z, VERTEX_1_SLIDER_51)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_tangent.x, VERTEX_1_SLIDER_52)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_tangent.y, VERTEX_1_SLIDER_53)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_tangent.z, VERTEX_1_SLIDER_54)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_55)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_56)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.x, VERTEX_2_SLIDER_60)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.y, VERTEX_2_SLIDER_61)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.z, VERTEX_2_SLIDER_62)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_normal.x, VERTEX_2_SLIDER_63)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_normal.y, VERTEX_2_SLIDER_64)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_normal.z, VERTEX_2_SLIDER_65)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_tangent.x, VERTEX_2_SLIDER_66)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_tangent.y, VERTEX_2_SLIDER_67)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_tangent.z, VERTEX_2_SLIDER_68)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_69)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_70)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.x, VERTEX_3_SLIDER_74)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.y, VERTEX_3_SLIDER_75)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.z, VERTEX_3_SLIDER_76)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_normal.x, VERTEX_3_SLIDER_77)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_normal.y, VERTEX_3_SLIDER_78)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_normal.z, VERTEX_3_SLIDER_79)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_tangent.x, VERTEX_3_SLIDER_80)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_tangent.y, VERTEX_3_SLIDER_81)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_tangent.z, VERTEX_3_SLIDER_82)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_83)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_84)
	//
	mIsRestoreNeed = false;
}

const std::vector<GeometryVertex>& GeometryUi::GetVertices() const
{
	return mVertices;
}

bool GeometryUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& GeometryUi::GetValueBySliderId(int aSliderId)
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

		case U_MATRIX_MODEL_VIEW_SLIDER_16:
			return m_u_matrix_model_view[0][0];

		case U_MATRIX_MODEL_VIEW_SLIDER_17:
			return m_u_matrix_model_view[0][1];

		case U_MATRIX_MODEL_VIEW_SLIDER_18:
			return m_u_matrix_model_view[0][2];

		case U_MATRIX_MODEL_VIEW_SLIDER_19:
			return m_u_matrix_model_view[1][0];

		case U_MATRIX_MODEL_VIEW_SLIDER_20:
			return m_u_matrix_model_view[1][1];

		case U_MATRIX_MODEL_VIEW_SLIDER_21:
			return m_u_matrix_model_view[1][2];

		case U_MATRIX_MODEL_VIEW_SLIDER_22:
			return m_u_matrix_model_view[2][0];

		case U_MATRIX_MODEL_VIEW_SLIDER_23:
			return m_u_matrix_model_view[2][1];

		case U_MATRIX_MODEL_VIEW_SLIDER_24:
			return m_u_matrix_model_view[2][2];

		case U_MATRIX_MODEL_VIEW_SLIDER_25:
			return m_u_matrix_model_view[3][0];

		case U_MATRIX_MODEL_VIEW_SLIDER_26:
			return m_u_matrix_model_view[3][1];

		case U_MATRIX_MODEL_VIEW_SLIDER_27:
			return m_u_matrix_model_view[3][2];

		case VERTEX_0_SLIDER_32:
			return mVertices[0].a_vertex_pos.x;

		case VERTEX_0_SLIDER_33:
			return mVertices[0].a_vertex_pos.y;

		case VERTEX_0_SLIDER_34:
			return mVertices[0].a_vertex_pos.z;

		case VERTEX_0_SLIDER_35:
			return mVertices[0].a_vertex_normal.x;

		case VERTEX_0_SLIDER_36:
			return mVertices[0].a_vertex_normal.y;

		case VERTEX_0_SLIDER_37:
			return mVertices[0].a_vertex_normal.z;

		case VERTEX_0_SLIDER_38:
			return mVertices[0].a_vertex_tangent.x;

		case VERTEX_0_SLIDER_39:
			return mVertices[0].a_vertex_tangent.y;

		case VERTEX_0_SLIDER_40:
			return mVertices[0].a_vertex_tangent.z;

		case VERTEX_0_SLIDER_41:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_42:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_46:
			return mVertices[1].a_vertex_pos.x;

		case VERTEX_1_SLIDER_47:
			return mVertices[1].a_vertex_pos.y;

		case VERTEX_1_SLIDER_48:
			return mVertices[1].a_vertex_pos.z;

		case VERTEX_1_SLIDER_49:
			return mVertices[1].a_vertex_normal.x;

		case VERTEX_1_SLIDER_50:
			return mVertices[1].a_vertex_normal.y;

		case VERTEX_1_SLIDER_51:
			return mVertices[1].a_vertex_normal.z;

		case VERTEX_1_SLIDER_52:
			return mVertices[1].a_vertex_tangent.x;

		case VERTEX_1_SLIDER_53:
			return mVertices[1].a_vertex_tangent.y;

		case VERTEX_1_SLIDER_54:
			return mVertices[1].a_vertex_tangent.z;

		case VERTEX_1_SLIDER_55:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_56:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_60:
			return mVertices[2].a_vertex_pos.x;

		case VERTEX_2_SLIDER_61:
			return mVertices[2].a_vertex_pos.y;

		case VERTEX_2_SLIDER_62:
			return mVertices[2].a_vertex_pos.z;

		case VERTEX_2_SLIDER_63:
			return mVertices[2].a_vertex_normal.x;

		case VERTEX_2_SLIDER_64:
			return mVertices[2].a_vertex_normal.y;

		case VERTEX_2_SLIDER_65:
			return mVertices[2].a_vertex_normal.z;

		case VERTEX_2_SLIDER_66:
			return mVertices[2].a_vertex_tangent.x;

		case VERTEX_2_SLIDER_67:
			return mVertices[2].a_vertex_tangent.y;

		case VERTEX_2_SLIDER_68:
			return mVertices[2].a_vertex_tangent.z;

		case VERTEX_2_SLIDER_69:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_70:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_74:
			return mVertices[3].a_vertex_pos.x;

		case VERTEX_3_SLIDER_75:
			return mVertices[3].a_vertex_pos.y;

		case VERTEX_3_SLIDER_76:
			return mVertices[3].a_vertex_pos.z;

		case VERTEX_3_SLIDER_77:
			return mVertices[3].a_vertex_normal.x;

		case VERTEX_3_SLIDER_78:
			return mVertices[3].a_vertex_normal.y;

		case VERTEX_3_SLIDER_79:
			return mVertices[3].a_vertex_normal.z;

		case VERTEX_3_SLIDER_80:
			return mVertices[3].a_vertex_tangent.x;

		case VERTEX_3_SLIDER_81:
			return mVertices[3].a_vertex_tangent.y;

		case VERTEX_3_SLIDER_82:
			return mVertices[3].a_vertex_tangent.z;

		case VERTEX_3_SLIDER_83:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_84:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
