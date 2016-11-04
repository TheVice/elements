
#include "CustomUi.h"
#include "ui/controls/button.h"
#include "ui/controls/label.h"
#include "ui/controls/panel.h"
#include "SliderModel.h"
#include "Controls.h"
#include <sstream>
#include <iomanip>

namespace Rendering
{
RTTI_DEFINITIONS(CustomUi)

CustomUi::CustomUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	m_u_matrix_mvp(),
	m_u_matrix_model_view(),
	m_u_matrix_normal(),
	m_u_matrix_view(),
	m_u_camera_pos(),
	m_u_light_pos(),
	mVertices(
{
	VertexStructure(),
					VertexStructure(),
					VertexStructure(),
					VertexStructure()
}),
mSliderModels(SLIDER_MODEL_COUNT)
{
}

CustomUi::~CustomUi()
{
}

bool CustomUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_BUTTON_13)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_BUTTON_28)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_BUTTON_37)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_BUTTON_52)
	IS_CONTROL_EXIST(U_CAMERA_POS_BUTTON_58)
	IS_CONTROL_EXIST(U_LIGHT_POS_BUTTON_64)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_78)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_92)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_106)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_120)
	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_PANEL_14)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_VIEW_PANEL_29)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_PANEL_38)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_PANEL_53)
	IS_CONTROL_EXIST(U_CAMERA_POS_PANEL_59)
	IS_CONTROL_EXIST(U_LIGHT_POS_PANEL_65)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_79)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_93)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_107)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_121)
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
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_31)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_32)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_33)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_34)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_35)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_36)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_39)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_40)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_41)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_42)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_43)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_44)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_45)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_46)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_47)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_48)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_49)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_50)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_51)
	IS_CONTROL_EXIST(U_MATRIX_VIEW_LABEL_54)
	IS_CONTROL_EXIST(U_CAMERA_POS_LABEL_55)
	IS_CONTROL_EXIST(U_CAMERA_POS_LABEL_56)
	IS_CONTROL_EXIST(U_CAMERA_POS_LABEL_57)
	IS_CONTROL_EXIST(U_CAMERA_POS_LABEL_60)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_61)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_62)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_63)
	IS_CONTROL_EXIST(U_LIGHT_POS_LABEL_66)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_67)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_68)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_69)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_70)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_71)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_72)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_73)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_74)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_75)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_76)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_77)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_80)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_81)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_82)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_83)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_84)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_85)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_86)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_87)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_88)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_89)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_90)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_91)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_94)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_95)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_96)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_97)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_98)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_99)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_100)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_101)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_102)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_103)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_104)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_105)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_108)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_109)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_110)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_111)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_112)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_113)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_114)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_115)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_116)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_117)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_118)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_119)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_122)
	//
	IS_ALL_SLIDER_MODELS_SET(mSliderModels)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_MVP_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_MATRIX_MODEL_VIEW_BUTTON_28].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_MATRIX_NORMAL_BUTTON_37].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_VIEW_BUTTON_52].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_CAMERA_POS_BUTTON_58].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_LIGHT_POS_BUTTON_64].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_78].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_92].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_106].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_120].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			// TODO:
		});
	}

	return true;
}

void CustomUi::Update()
{
	UiAsset::Update();
	//
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[0][0], U_MATRIX_MVP_LABEL_1)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[0][1], U_MATRIX_MVP_LABEL_2)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[0][2], U_MATRIX_MVP_LABEL_3)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[1][0], U_MATRIX_MVP_LABEL_4)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[1][1], U_MATRIX_MVP_LABEL_5)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[1][2], U_MATRIX_MVP_LABEL_6)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[2][0], U_MATRIX_MVP_LABEL_7)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[2][1], U_MATRIX_MVP_LABEL_8)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[2][2], U_MATRIX_MVP_LABEL_9)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[3][0], U_MATRIX_MVP_LABEL_10)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[3][1], U_MATRIX_MVP_LABEL_11)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_mvp[3][2], U_MATRIX_MVP_LABEL_12)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[0][0], U_MATRIX_MODEL_VIEW_LABEL_16)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[0][1], U_MATRIX_MODEL_VIEW_LABEL_17)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[0][2], U_MATRIX_MODEL_VIEW_LABEL_18)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[1][0], U_MATRIX_MODEL_VIEW_LABEL_19)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[1][1], U_MATRIX_MODEL_VIEW_LABEL_20)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[1][2], U_MATRIX_MODEL_VIEW_LABEL_21)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[2][0], U_MATRIX_MODEL_VIEW_LABEL_22)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[2][1], U_MATRIX_MODEL_VIEW_LABEL_23)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[2][2], U_MATRIX_MODEL_VIEW_LABEL_24)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[3][0], U_MATRIX_MODEL_VIEW_LABEL_25)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[3][1], U_MATRIX_MODEL_VIEW_LABEL_26)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_model_view[3][2], U_MATRIX_MODEL_VIEW_LABEL_27)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_normal[0][0], U_MATRIX_NORMAL_LABEL_31)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_normal[0][1], U_MATRIX_NORMAL_LABEL_32)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_normal[1][0], U_MATRIX_NORMAL_LABEL_33)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_normal[1][1], U_MATRIX_NORMAL_LABEL_34)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_normal[2][0], U_MATRIX_NORMAL_LABEL_35)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_normal[2][1], U_MATRIX_NORMAL_LABEL_36)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[0][0], U_MATRIX_VIEW_LABEL_40)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[0][1], U_MATRIX_VIEW_LABEL_41)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[0][2], U_MATRIX_VIEW_LABEL_42)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[1][0], U_MATRIX_VIEW_LABEL_43)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[1][1], U_MATRIX_VIEW_LABEL_44)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[1][2], U_MATRIX_VIEW_LABEL_45)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[2][0], U_MATRIX_VIEW_LABEL_46)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[2][1], U_MATRIX_VIEW_LABEL_47)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[2][2], U_MATRIX_VIEW_LABEL_48)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[3][0], U_MATRIX_VIEW_LABEL_49)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[3][1], U_MATRIX_VIEW_LABEL_50)
	DISPLAY_VALUE_AT_LABEL(m_u_matrix_view[3][2], U_MATRIX_VIEW_LABEL_51)
	DISPLAY_VALUE_AT_LABEL(m_u_camera_pos[0], U_CAMERA_POS_LABEL_55)
	DISPLAY_VALUE_AT_LABEL(m_u_camera_pos[1], U_CAMERA_POS_LABEL_56)
	DISPLAY_VALUE_AT_LABEL(m_u_camera_pos[2], U_CAMERA_POS_LABEL_57)
	DISPLAY_VALUE_AT_LABEL(m_u_light_pos[0], U_LIGHT_POS_LABEL_61)
	DISPLAY_VALUE_AT_LABEL(m_u_light_pos[1], U_LIGHT_POS_LABEL_62)
	DISPLAY_VALUE_AT_LABEL(m_u_light_pos[2], U_LIGHT_POS_LABEL_63)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VERTEX_0_LABEL_67)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VERTEX_0_LABEL_68)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VERTEX_0_LABEL_69)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.x, VERTEX_0_LABEL_70)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.y, VERTEX_0_LABEL_71)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.z, VERTEX_0_LABEL_72)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.x, VERTEX_0_LABEL_73)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.y, VERTEX_0_LABEL_74)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.z, VERTEX_0_LABEL_75)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_76)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_77)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VERTEX_1_LABEL_81)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VERTEX_1_LABEL_82)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VERTEX_1_LABEL_83)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.x, VERTEX_1_LABEL_84)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.y, VERTEX_1_LABEL_85)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.z, VERTEX_1_LABEL_86)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.x, VERTEX_1_LABEL_87)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.y, VERTEX_1_LABEL_88)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.z, VERTEX_1_LABEL_89)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_90)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_91)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VERTEX_2_LABEL_95)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VERTEX_2_LABEL_96)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VERTEX_2_LABEL_97)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.x, VERTEX_2_LABEL_98)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.y, VERTEX_2_LABEL_99)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.z, VERTEX_2_LABEL_100)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.x, VERTEX_2_LABEL_101)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.y, VERTEX_2_LABEL_102)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.z, VERTEX_2_LABEL_103)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_104)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_105)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VERTEX_3_LABEL_109)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VERTEX_3_LABEL_110)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VERTEX_3_LABEL_111)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.x, VERTEX_3_LABEL_112)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.y, VERTEX_3_LABEL_113)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.z, VERTEX_3_LABEL_114)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.x, VERTEX_3_LABEL_115)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.y, VERTEX_3_LABEL_116)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.z, VERTEX_3_LABEL_117)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_118)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_119)
}

void CustomUi::Set_u_matrix_mvp(const glm::mat4& a_u_matrix_mvp)
{
	m_u_matrix_mvp = a_u_matrix_mvp;
	//
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[0][0], U_MATRIX_MVP_SLIDER_1)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[0][1], U_MATRIX_MVP_SLIDER_2)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[0][2], U_MATRIX_MVP_SLIDER_3)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[1][0], U_MATRIX_MVP_SLIDER_4)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[1][1], U_MATRIX_MVP_SLIDER_5)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[1][2], U_MATRIX_MVP_SLIDER_6)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[2][0], U_MATRIX_MVP_SLIDER_7)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[2][1], U_MATRIX_MVP_SLIDER_8)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[2][2], U_MATRIX_MVP_SLIDER_9)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[3][0], U_MATRIX_MVP_SLIDER_10)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[3][1], U_MATRIX_MVP_SLIDER_11)
	SET_REAL_SLIDER_VALUE(m_u_matrix_mvp[3][2], U_MATRIX_MVP_SLIDER_12)
}

const glm::mat4& CustomUi::Get_u_matrix_mvp() const
{
	return m_u_matrix_mvp;
}

void CustomUi::Set_u_matrix_model_view(const glm::mat4& a_u_matrix_model_view)
{
	m_u_matrix_model_view = a_u_matrix_model_view;
	//
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[0][0], U_MATRIX_MODEL_VIEW_SLIDER_16)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[0][1], U_MATRIX_MODEL_VIEW_SLIDER_17)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[0][2], U_MATRIX_MODEL_VIEW_SLIDER_18)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[1][0], U_MATRIX_MODEL_VIEW_SLIDER_19)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[1][1], U_MATRIX_MODEL_VIEW_SLIDER_20)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[1][2], U_MATRIX_MODEL_VIEW_SLIDER_21)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[2][0], U_MATRIX_MODEL_VIEW_SLIDER_22)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[2][1], U_MATRIX_MODEL_VIEW_SLIDER_23)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[2][2], U_MATRIX_MODEL_VIEW_SLIDER_24)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[3][0], U_MATRIX_MODEL_VIEW_SLIDER_25)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[3][1], U_MATRIX_MODEL_VIEW_SLIDER_26)
	SET_REAL_SLIDER_VALUE(m_u_matrix_model_view[3][2], U_MATRIX_MODEL_VIEW_SLIDER_27)
}

const glm::mat4& CustomUi::Get_u_matrix_model_view() const
{
	return m_u_matrix_model_view;
}

void CustomUi::Set_u_matrix_normal(const glm::mat3& a_u_matrix_normal)
{
	m_u_matrix_normal = a_u_matrix_normal;
	//
	SET_REAL_SLIDER_VALUE(m_u_matrix_normal[0][0], U_MATRIX_NORMAL_SLIDER_31)
	SET_REAL_SLIDER_VALUE(m_u_matrix_normal[0][1], U_MATRIX_NORMAL_SLIDER_32)
	SET_REAL_SLIDER_VALUE(m_u_matrix_normal[1][0], U_MATRIX_NORMAL_SLIDER_33)
	SET_REAL_SLIDER_VALUE(m_u_matrix_normal[1][1], U_MATRIX_NORMAL_SLIDER_34)
	SET_REAL_SLIDER_VALUE(m_u_matrix_normal[2][0], U_MATRIX_NORMAL_SLIDER_35)
	SET_REAL_SLIDER_VALUE(m_u_matrix_normal[2][1], U_MATRIX_NORMAL_SLIDER_36)
}

const glm::mat3& CustomUi::Get_u_matrix_normal() const
{
	return m_u_matrix_normal;
}

void CustomUi::Set_u_matrix_view(const glm::mat4& a_u_matrix_view)
{
	m_u_matrix_view = a_u_matrix_view;
	//
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[0][0], U_MATRIX_VIEW_SLIDER_40)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[0][1], U_MATRIX_VIEW_SLIDER_41)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[0][2], U_MATRIX_VIEW_SLIDER_42)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[1][0], U_MATRIX_VIEW_SLIDER_43)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[1][1], U_MATRIX_VIEW_SLIDER_44)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[1][2], U_MATRIX_VIEW_SLIDER_45)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[2][0], U_MATRIX_VIEW_SLIDER_46)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[2][1], U_MATRIX_VIEW_SLIDER_47)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[2][2], U_MATRIX_VIEW_SLIDER_48)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[3][0], U_MATRIX_VIEW_SLIDER_49)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[3][1], U_MATRIX_VIEW_SLIDER_50)
	SET_REAL_SLIDER_VALUE(m_u_matrix_view[3][2], U_MATRIX_VIEW_SLIDER_51)
}

const glm::mat4& CustomUi::Get_u_matrix_view() const
{
	return m_u_matrix_view;
}

void CustomUi::Set_u_camera_pos(const glm::vec3& a_u_camera_pos)
{
	m_u_camera_pos = a_u_camera_pos;
	//
	SET_REAL_SLIDER_VALUE(m_u_camera_pos[0], U_CAMERA_POS_SLIDER_55)
	SET_REAL_SLIDER_VALUE(m_u_camera_pos[1], U_CAMERA_POS_SLIDER_56)
	SET_REAL_SLIDER_VALUE(m_u_camera_pos[2], U_CAMERA_POS_SLIDER_57)
}

const glm::vec3& CustomUi::Get_u_camera_pos() const
{
	return m_u_camera_pos;
}

void CustomUi::Set_u_light_pos(const glm::vec3& a_u_light_pos)
{
	m_u_light_pos = a_u_light_pos;
	//
	SET_REAL_SLIDER_VALUE(m_u_light_pos[0], U_LIGHT_POS_SLIDER_61)
	SET_REAL_SLIDER_VALUE(m_u_light_pos[1], U_LIGHT_POS_SLIDER_62)
	SET_REAL_SLIDER_VALUE(m_u_light_pos[2], U_LIGHT_POS_SLIDER_63)
}

const glm::vec3& CustomUi::Get_u_light_pos() const
{
	return m_u_light_pos;
}

void CustomUi::SetVertices(const std::vector<VertexStructure>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_pos.x, VERTEX_0_SLIDER_67)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_pos.y, VERTEX_0_SLIDER_68)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_pos.z, VERTEX_0_SLIDER_69)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_normal.x, VERTEX_0_SLIDER_70)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_normal.y, VERTEX_0_SLIDER_71)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_normal.z, VERTEX_0_SLIDER_72)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_tangent.x, VERTEX_0_SLIDER_73)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_tangent.y, VERTEX_0_SLIDER_74)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_tangent.z, VERTEX_0_SLIDER_75)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_76)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_77)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_pos.x, VERTEX_1_SLIDER_81)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_pos.y, VERTEX_1_SLIDER_82)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_pos.z, VERTEX_1_SLIDER_83)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_normal.x, VERTEX_1_SLIDER_84)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_normal.y, VERTEX_1_SLIDER_85)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_normal.z, VERTEX_1_SLIDER_86)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_tangent.x, VERTEX_1_SLIDER_87)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_tangent.y, VERTEX_1_SLIDER_88)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_tangent.z, VERTEX_1_SLIDER_89)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_90)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_91)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_pos.x, VERTEX_2_SLIDER_95)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_pos.y, VERTEX_2_SLIDER_96)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_pos.z, VERTEX_2_SLIDER_97)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_normal.x, VERTEX_2_SLIDER_98)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_normal.y, VERTEX_2_SLIDER_99)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_normal.z, VERTEX_2_SLIDER_100)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_tangent.x, VERTEX_2_SLIDER_101)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_tangent.y, VERTEX_2_SLIDER_102)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_tangent.z, VERTEX_2_SLIDER_103)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_104)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_105)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_pos.x, VERTEX_3_SLIDER_109)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_pos.y, VERTEX_3_SLIDER_110)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_pos.z, VERTEX_3_SLIDER_111)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_normal.x, VERTEX_3_SLIDER_112)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_normal.y, VERTEX_3_SLIDER_113)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_normal.z, VERTEX_3_SLIDER_114)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_tangent.x, VERTEX_3_SLIDER_115)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_tangent.y, VERTEX_3_SLIDER_116)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_tangent.z, VERTEX_3_SLIDER_117)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_118)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_119)
}

const std::vector<VertexStructure>& CustomUi::GetVertices() const
{
	return mVertices;
}

Library::SliderModel* CustomUi::GetSliderModel(int aSliderId, float aMin, float aMax)
{
	Library::SliderModel* sliderModel = nullptr;

	if (aSliderId > (SLIDER_MODEL_COUNT - 1) || mSliderModels[aSliderId])
	{
		return sliderModel;
	}

	float* modelValue = nullptr;

	switch (aSliderId)
	{
		case U_MATRIX_MVP_SLIDER_1:
			modelValue = &m_u_matrix_mvp[0][0];
			break;

		case U_MATRIX_MVP_SLIDER_2:
			modelValue = &m_u_matrix_mvp[0][1];
			break;

		case U_MATRIX_MVP_SLIDER_3:
			modelValue = &m_u_matrix_mvp[0][2];
			break;

		case U_MATRIX_MVP_SLIDER_4:
			modelValue = &m_u_matrix_mvp[1][0];
			break;

		case U_MATRIX_MVP_SLIDER_5:
			modelValue = &m_u_matrix_mvp[1][1];
			break;

		case U_MATRIX_MVP_SLIDER_6:
			modelValue = &m_u_matrix_mvp[1][2];
			break;

		case U_MATRIX_MVP_SLIDER_7:
			modelValue = &m_u_matrix_mvp[2][0];
			break;

		case U_MATRIX_MVP_SLIDER_8:
			modelValue = &m_u_matrix_mvp[2][1];
			break;

		case U_MATRIX_MVP_SLIDER_9:
			modelValue = &m_u_matrix_mvp[2][2];
			break;

		case U_MATRIX_MVP_SLIDER_10:
			modelValue = &m_u_matrix_mvp[3][0];
			break;

		case U_MATRIX_MVP_SLIDER_11:
			modelValue = &m_u_matrix_mvp[3][1];
			break;

		case U_MATRIX_MVP_SLIDER_12:
			modelValue = &m_u_matrix_mvp[3][2];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_16:
			modelValue = &m_u_matrix_model_view[0][0];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_17:
			modelValue = &m_u_matrix_model_view[0][1];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_18:
			modelValue = &m_u_matrix_model_view[0][2];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_19:
			modelValue = &m_u_matrix_model_view[1][0];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_20:
			modelValue = &m_u_matrix_model_view[1][1];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_21:
			modelValue = &m_u_matrix_model_view[1][2];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_22:
			modelValue = &m_u_matrix_model_view[2][0];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_23:
			modelValue = &m_u_matrix_model_view[2][1];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_24:
			modelValue = &m_u_matrix_model_view[2][2];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_25:
			modelValue = &m_u_matrix_model_view[3][0];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_26:
			modelValue = &m_u_matrix_model_view[3][1];
			break;

		case U_MATRIX_MODEL_VIEW_SLIDER_27:
			modelValue = &m_u_matrix_model_view[3][2];
			break;

		case U_MATRIX_NORMAL_SLIDER_31:
			modelValue = &m_u_matrix_normal[0][0];
			break;

		case U_MATRIX_NORMAL_SLIDER_32:
			modelValue = &m_u_matrix_normal[0][1];
			break;

		case U_MATRIX_NORMAL_SLIDER_33:
			modelValue = &m_u_matrix_normal[1][0];
			break;

		case U_MATRIX_NORMAL_SLIDER_34:
			modelValue = &m_u_matrix_normal[1][1];
			break;

		case U_MATRIX_NORMAL_SLIDER_35:
			modelValue = &m_u_matrix_normal[2][0];
			break;

		case U_MATRIX_NORMAL_SLIDER_36:
			modelValue = &m_u_matrix_normal[2][1];
			break;

		case U_MATRIX_VIEW_SLIDER_40:
			modelValue = &m_u_matrix_view[0][0];
			break;

		case U_MATRIX_VIEW_SLIDER_41:
			modelValue = &m_u_matrix_view[0][1];
			break;

		case U_MATRIX_VIEW_SLIDER_42:
			modelValue = &m_u_matrix_view[0][2];
			break;

		case U_MATRIX_VIEW_SLIDER_43:
			modelValue = &m_u_matrix_view[1][0];
			break;

		case U_MATRIX_VIEW_SLIDER_44:
			modelValue = &m_u_matrix_view[1][1];
			break;

		case U_MATRIX_VIEW_SLIDER_45:
			modelValue = &m_u_matrix_view[1][2];
			break;

		case U_MATRIX_VIEW_SLIDER_46:
			modelValue = &m_u_matrix_view[2][0];
			break;

		case U_MATRIX_VIEW_SLIDER_47:
			modelValue = &m_u_matrix_view[2][1];
			break;

		case U_MATRIX_VIEW_SLIDER_48:
			modelValue = &m_u_matrix_view[2][2];
			break;

		case U_MATRIX_VIEW_SLIDER_49:
			modelValue = &m_u_matrix_view[3][0];
			break;

		case U_MATRIX_VIEW_SLIDER_50:
			modelValue = &m_u_matrix_view[3][1];
			break;

		case U_MATRIX_VIEW_SLIDER_51:
			modelValue = &m_u_matrix_view[3][2];
			break;

		case U_CAMERA_POS_SLIDER_55:
			modelValue = &m_u_camera_pos[0];
			break;

		case U_CAMERA_POS_SLIDER_56:
			modelValue = &m_u_camera_pos[1];
			break;

		case U_CAMERA_POS_SLIDER_57:
			modelValue = &m_u_camera_pos[2];
			break;

		case U_LIGHT_POS_SLIDER_61:
			modelValue = &m_u_light_pos[0];
			break;

		case U_LIGHT_POS_SLIDER_62:
			modelValue = &m_u_light_pos[1];
			break;

		case U_LIGHT_POS_SLIDER_63:
			modelValue = &m_u_light_pos[2];
			break;

		case VERTEX_0_SLIDER_67:
			modelValue = &mVertices[0].a_vertex_pos.x;
			break;

		case VERTEX_0_SLIDER_68:
			modelValue = &mVertices[0].a_vertex_pos.y;
			break;

		case VERTEX_0_SLIDER_69:
			modelValue = &mVertices[0].a_vertex_pos.z;
			break;

		case VERTEX_0_SLIDER_70:
			modelValue = &mVertices[0].a_vertex_normal.x;
			break;

		case VERTEX_0_SLIDER_71:
			modelValue = &mVertices[0].a_vertex_normal.y;
			break;

		case VERTEX_0_SLIDER_72:
			modelValue = &mVertices[0].a_vertex_normal.z;
			break;

		case VERTEX_0_SLIDER_73:
			modelValue = &mVertices[0].a_vertex_tangent.x;
			break;

		case VERTEX_0_SLIDER_74:
			modelValue = &mVertices[0].a_vertex_tangent.y;
			break;

		case VERTEX_0_SLIDER_75:
			modelValue = &mVertices[0].a_vertex_tangent.z;
			break;

		case VERTEX_0_SLIDER_76:
			modelValue = &mVertices[0].a_vertex_uv.x;
			break;

		case VERTEX_0_SLIDER_77:
			modelValue = &mVertices[0].a_vertex_uv.y;
			break;

		case VERTEX_1_SLIDER_81:
			modelValue = &mVertices[1].a_vertex_pos.x;
			break;

		case VERTEX_1_SLIDER_82:
			modelValue = &mVertices[1].a_vertex_pos.y;
			break;

		case VERTEX_1_SLIDER_83:
			modelValue = &mVertices[1].a_vertex_pos.z;
			break;

		case VERTEX_1_SLIDER_84:
			modelValue = &mVertices[1].a_vertex_normal.x;
			break;

		case VERTEX_1_SLIDER_85:
			modelValue = &mVertices[1].a_vertex_normal.y;
			break;

		case VERTEX_1_SLIDER_86:
			modelValue = &mVertices[1].a_vertex_normal.z;
			break;

		case VERTEX_1_SLIDER_87:
			modelValue = &mVertices[1].a_vertex_tangent.x;
			break;

		case VERTEX_1_SLIDER_88:
			modelValue = &mVertices[1].a_vertex_tangent.y;
			break;

		case VERTEX_1_SLIDER_89:
			modelValue = &mVertices[1].a_vertex_tangent.z;
			break;

		case VERTEX_1_SLIDER_90:
			modelValue = &mVertices[1].a_vertex_uv.x;
			break;

		case VERTEX_1_SLIDER_91:
			modelValue = &mVertices[1].a_vertex_uv.y;
			break;

		case VERTEX_2_SLIDER_95:
			modelValue = &mVertices[2].a_vertex_pos.x;
			break;

		case VERTEX_2_SLIDER_96:
			modelValue = &mVertices[2].a_vertex_pos.y;
			break;

		case VERTEX_2_SLIDER_97:
			modelValue = &mVertices[2].a_vertex_pos.z;
			break;

		case VERTEX_2_SLIDER_98:
			modelValue = &mVertices[2].a_vertex_normal.x;
			break;

		case VERTEX_2_SLIDER_99:
			modelValue = &mVertices[2].a_vertex_normal.y;
			break;

		case VERTEX_2_SLIDER_100:
			modelValue = &mVertices[2].a_vertex_normal.z;
			break;

		case VERTEX_2_SLIDER_101:
			modelValue = &mVertices[2].a_vertex_tangent.x;
			break;

		case VERTEX_2_SLIDER_102:
			modelValue = &mVertices[2].a_vertex_tangent.y;
			break;

		case VERTEX_2_SLIDER_103:
			modelValue = &mVertices[2].a_vertex_tangent.z;
			break;

		case VERTEX_2_SLIDER_104:
			modelValue = &mVertices[2].a_vertex_uv.x;
			break;

		case VERTEX_2_SLIDER_105:
			modelValue = &mVertices[2].a_vertex_uv.y;
			break;

		case VERTEX_3_SLIDER_109:
			modelValue = &mVertices[3].a_vertex_pos.x;
			break;

		case VERTEX_3_SLIDER_110:
			modelValue = &mVertices[3].a_vertex_pos.y;
			break;

		case VERTEX_3_SLIDER_111:
			modelValue = &mVertices[3].a_vertex_pos.z;
			break;

		case VERTEX_3_SLIDER_112:
			modelValue = &mVertices[3].a_vertex_normal.x;
			break;

		case VERTEX_3_SLIDER_113:
			modelValue = &mVertices[3].a_vertex_normal.y;
			break;

		case VERTEX_3_SLIDER_114:
			modelValue = &mVertices[3].a_vertex_normal.z;
			break;

		case VERTEX_3_SLIDER_115:
			modelValue = &mVertices[3].a_vertex_tangent.x;
			break;

		case VERTEX_3_SLIDER_116:
			modelValue = &mVertices[3].a_vertex_tangent.y;
			break;

		case VERTEX_3_SLIDER_117:
			modelValue = &mVertices[3].a_vertex_tangent.z;
			break;

		case VERTEX_3_SLIDER_118:
			modelValue = &mVertices[3].a_vertex_uv.x;
			break;

		case VERTEX_3_SLIDER_119:
			modelValue = &mVertices[3].a_vertex_uv.y;
			break;

		default:
			return sliderModel;
	}

	assert(modelValue);
	sliderModel = new Library::CustomSliderModel(*modelValue, aMin, aMax);
	mSliderModels[aSliderId] = sliderModel;
	return sliderModel;
}

}
