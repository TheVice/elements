
#include "CustomUi.h"
#include "Controls.h"
#include <checkbox.h>
#include <SliderModel.h>
#include <elements/ui/controls/button.h>
#include <elements/ui/controls/check.h>
#include <elements/ui/controls/label.h>
#include <elements/ui/controls/panel.h>
#include <elements/ui/controls/slider.h>

namespace Rendering
{
RTTI_DEFINITIONS(CustomUi)

CustomUi::CustomUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(false),
	mIsEncodeNormal(true),
	m_u_matrix_mvp(),
	m_u_matrix_normal(),
	mVertices(
{
	VertexStructure(),
					VertexStructure(),
					VertexStructure(),
					VertexStructure()
})
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

	IS_CONTROL_EXIST(RESTORE_BUTTON)
	IS_CONTROL_EXIST(U_MATRIX_MVP_BUTTON_13)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_BUTTON_22)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_36)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_50)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_64)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_78)
	IS_CONTROL_EXIST(U_MATRIX_MVP_PANEL_14)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_PANEL_23)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_37)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_51)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_65)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_79)
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
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_16)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_17)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_18)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_19)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_20)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_21)
	IS_CONTROL_EXIST(U_MATRIX_NORMAL_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_27)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_34)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_35)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_38)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_39)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_40)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_41)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_42)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_43)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_44)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_47)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_48)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_49)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_52)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_53)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_54)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_55)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_56)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_57)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_58)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_59)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_60)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_61)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_62)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_63)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_66)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_67)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_68)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_69)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_70)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_71)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_72)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_73)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_74)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_75)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_76)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_77)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_80)
	IS_CONTROL_EXIST(ENCODE_NORMAL_LABEL)
	IS_CONTROL_EXIST(ENCODE_NORMAL_CHECKBOX)
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
			if (auto mvpPanel = this->mControls[U_MATRIX_MVP_PANEL_14].lock())
			{
				mvpPanel->set_visible(!mvpPanel->get_visible());
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_MATRIX_NORMAL_BUTTON_22].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto normalPanel = this->mControls[U_MATRIX_NORMAL_PANEL_23].lock())
			{
				normalPanel->set_visible(!normalPanel->get_visible());
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_36].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_37].lock())
			{
				ltPanel->set_visible(!ltPanel->get_visible());
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_51].lock())
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_65].lock())
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_79].lock())
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_50].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_37].lock())
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_51].lock())
			{
				rtPanel->set_visible(!rtPanel->get_visible());
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_65].lock())
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_79].lock())
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_64].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_37].lock())
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_51].lock())
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_65].lock())
			{
				rbPanel->set_visible(!rbPanel->get_visible());
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_79].lock())
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_78].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_37].lock())
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_51].lock())
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_65].lock())
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_79].lock())
			{
				lbPanel->set_visible(!lbPanel->get_visible());
			}
		});
	}

	return true;
}

void CustomUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = this->mControls[U_MATRIX_MVP_PANEL_14].lock())
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

	if (auto directPanel = this->mControls[U_MATRIX_NORMAL_PANEL_23].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_normal[0][0], U_MATRIX_NORMAL_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_normal[0][1], U_MATRIX_NORMAL_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_normal[1][0], U_MATRIX_NORMAL_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_normal[1][1], U_MATRIX_NORMAL_LABEL_19)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_normal[2][0], U_MATRIX_NORMAL_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_normal[2][1], U_MATRIX_NORMAL_LABEL_21)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_0_PANEL_37].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VERTEX_0_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VERTEX_0_LABEL_26)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VERTEX_0_LABEL_27)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.x, VERTEX_0_LABEL_28)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.y, VERTEX_0_LABEL_29)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_normal.z, VERTEX_0_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.x, VERTEX_0_LABEL_31)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.y, VERTEX_0_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_tangent.z, VERTEX_0_LABEL_33)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_34)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_35)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_1_PANEL_51].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VERTEX_1_LABEL_39)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VERTEX_1_LABEL_40)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VERTEX_1_LABEL_41)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.x, VERTEX_1_LABEL_42)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.y, VERTEX_1_LABEL_43)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_normal.z, VERTEX_1_LABEL_44)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.x, VERTEX_1_LABEL_45)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.y, VERTEX_1_LABEL_46)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_tangent.z, VERTEX_1_LABEL_47)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_48)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_49)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_2_PANEL_65].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VERTEX_2_LABEL_53)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VERTEX_2_LABEL_54)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VERTEX_2_LABEL_55)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.x, VERTEX_2_LABEL_56)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.y, VERTEX_2_LABEL_57)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_normal.z, VERTEX_2_LABEL_58)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.x, VERTEX_2_LABEL_59)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.y, VERTEX_2_LABEL_60)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_tangent.z, VERTEX_2_LABEL_61)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_62)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_63)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_3_PANEL_79].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VERTEX_3_LABEL_67)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VERTEX_3_LABEL_68)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VERTEX_3_LABEL_69)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.x, VERTEX_3_LABEL_70)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.y, VERTEX_3_LABEL_71)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_normal.z, VERTEX_3_LABEL_72)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.x, VERTEX_3_LABEL_73)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.y, VERTEX_3_LABEL_74)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_tangent.z, VERTEX_3_LABEL_75)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_76)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_77)
		}
	}

	if (auto directCheckbox = std::static_pointer_cast<Library::checkbox>
							  (mControls[ENCODE_NORMAL_CHECKBOX].lock()))
	{
		mIsEncodeNormal = (Library::checkbox::state::CHECKED == directCheckbox->get_state());
	}
}

void CustomUi::Set_u_matrix_mvp(const glm::mat4& a_u_matrix_mvp)
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

const glm::mat4& CustomUi::Get_u_matrix_mvp() const
{
	return m_u_matrix_mvp;
}

void CustomUi::Set_u_matrix_normal(const glm::mat3& a_u_matrix_normal)
{
	m_u_matrix_normal = a_u_matrix_normal;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_normal[0][0], U_MATRIX_NORMAL_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_normal[0][1], U_MATRIX_NORMAL_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_normal[1][0], U_MATRIX_NORMAL_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_normal[1][1], U_MATRIX_NORMAL_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_normal[2][0], U_MATRIX_NORMAL_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_normal[2][1], U_MATRIX_NORMAL_SLIDER_21)
	//
	mIsRestoreNeed = false;
}

const glm::mat3& CustomUi::Get_u_matrix_normal() const
{
	return m_u_matrix_normal;
}

void CustomUi::SetVertices(const std::vector<VertexStructure>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.x, VERTEX_0_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.y, VERTEX_0_SLIDER_26)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.z, VERTEX_0_SLIDER_27)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_normal.x, VERTEX_0_SLIDER_28)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_normal.y, VERTEX_0_SLIDER_29)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_normal.z, VERTEX_0_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_tangent.x, VERTEX_0_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_tangent.y, VERTEX_0_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_tangent.z, VERTEX_0_SLIDER_33)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_34)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_35)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.x, VERTEX_1_SLIDER_39)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.y, VERTEX_1_SLIDER_40)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.z, VERTEX_1_SLIDER_41)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_normal.x, VERTEX_1_SLIDER_42)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_normal.y, VERTEX_1_SLIDER_43)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_normal.z, VERTEX_1_SLIDER_44)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_tangent.x, VERTEX_1_SLIDER_45)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_tangent.y, VERTEX_1_SLIDER_46)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_tangent.z, VERTEX_1_SLIDER_47)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_48)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_49)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.x, VERTEX_2_SLIDER_53)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.y, VERTEX_2_SLIDER_54)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.z, VERTEX_2_SLIDER_55)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_normal.x, VERTEX_2_SLIDER_56)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_normal.y, VERTEX_2_SLIDER_57)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_normal.z, VERTEX_2_SLIDER_58)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_tangent.x, VERTEX_2_SLIDER_59)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_tangent.y, VERTEX_2_SLIDER_60)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_tangent.z, VERTEX_2_SLIDER_61)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_62)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_63)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.x, VERTEX_3_SLIDER_67)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.y, VERTEX_3_SLIDER_68)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.z, VERTEX_3_SLIDER_69)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_normal.x, VERTEX_3_SLIDER_70)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_normal.y, VERTEX_3_SLIDER_71)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_normal.z, VERTEX_3_SLIDER_72)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_tangent.x, VERTEX_3_SLIDER_73)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_tangent.y, VERTEX_3_SLIDER_74)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_tangent.z, VERTEX_3_SLIDER_75)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_76)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_77)
	//
	mIsRestoreNeed = false;
}

const std::vector<VertexStructure>& CustomUi::GetVertices() const
{
	return mVertices;
}

bool CustomUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

bool CustomUi::IsEncodeNormal() const
{
	return mIsEncodeNormal;
}

void CustomUi::SetEncodeNormalControlsVisible(bool aVisible)
{
	SET_VISIBLE(aVisible, ENCODE_NORMAL_CHECKBOX)
	SET_VISIBLE(aVisible, ENCODE_NORMAL_LABEL)
}

float& CustomUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_MATRIX_MVP_SLIDER_1:
			return m_u_matrix_mvp[0][0];
			break;

		case U_MATRIX_MVP_SLIDER_2:
			return m_u_matrix_mvp[0][1];
			break;

		case U_MATRIX_MVP_SLIDER_3:
			return m_u_matrix_mvp[0][2];
			break;

		case U_MATRIX_MVP_SLIDER_4:
			return m_u_matrix_mvp[1][0];
			break;

		case U_MATRIX_MVP_SLIDER_5:
			return m_u_matrix_mvp[1][1];
			break;

		case U_MATRIX_MVP_SLIDER_6:
			return m_u_matrix_mvp[1][2];
			break;

		case U_MATRIX_MVP_SLIDER_7:
			return m_u_matrix_mvp[2][0];
			break;

		case U_MATRIX_MVP_SLIDER_8:
			return m_u_matrix_mvp[2][1];
			break;

		case U_MATRIX_MVP_SLIDER_9:
			return m_u_matrix_mvp[2][2];
			break;

		case U_MATRIX_MVP_SLIDER_10:
			return m_u_matrix_mvp[3][0];
			break;

		case U_MATRIX_MVP_SLIDER_11:
			return m_u_matrix_mvp[3][1];
			break;

		case U_MATRIX_MVP_SLIDER_12:
			return m_u_matrix_mvp[3][2];
			break;

		case U_MATRIX_NORMAL_SLIDER_16:
			return m_u_matrix_normal[0][0];
			break;

		case U_MATRIX_NORMAL_SLIDER_17:
			return m_u_matrix_normal[0][1];
			break;

		case U_MATRIX_NORMAL_SLIDER_18:
			return m_u_matrix_normal[1][0];
			break;

		case U_MATRIX_NORMAL_SLIDER_19:
			return m_u_matrix_normal[1][1];
			break;

		case U_MATRIX_NORMAL_SLIDER_20:
			return m_u_matrix_normal[2][0];
			break;

		case U_MATRIX_NORMAL_SLIDER_21:
			return m_u_matrix_normal[2][1];
			break;

		case VERTEX_0_SLIDER_25:
			return mVertices[0].a_vertex_pos.x;
			break;

		case VERTEX_0_SLIDER_26:
			return mVertices[0].a_vertex_pos.y;
			break;

		case VERTEX_0_SLIDER_27:
			return mVertices[0].a_vertex_pos.z;
			break;

		case VERTEX_0_SLIDER_28:
			return mVertices[0].a_vertex_normal.x;
			break;

		case VERTEX_0_SLIDER_29:
			return mVertices[0].a_vertex_normal.y;
			break;

		case VERTEX_0_SLIDER_30:
			return mVertices[0].a_vertex_normal.z;
			break;

		case VERTEX_0_SLIDER_31:
			return mVertices[0].a_vertex_tangent.x;
			break;

		case VERTEX_0_SLIDER_32:
			return mVertices[0].a_vertex_tangent.y;
			break;

		case VERTEX_0_SLIDER_33:
			return mVertices[0].a_vertex_tangent.z;
			break;

		case VERTEX_0_SLIDER_34:
			return mVertices[0].a_vertex_uv.x;
			break;

		case VERTEX_0_SLIDER_35:
			return mVertices[0].a_vertex_uv.y;
			break;

		case VERTEX_1_SLIDER_39:
			return mVertices[1].a_vertex_pos.x;
			break;

		case VERTEX_1_SLIDER_40:
			return mVertices[1].a_vertex_pos.y;
			break;

		case VERTEX_1_SLIDER_41:
			return mVertices[1].a_vertex_pos.z;
			break;

		case VERTEX_1_SLIDER_42:
			return mVertices[1].a_vertex_normal.x;
			break;

		case VERTEX_1_SLIDER_43:
			return mVertices[1].a_vertex_normal.y;
			break;

		case VERTEX_1_SLIDER_44:
			return mVertices[1].a_vertex_normal.z;
			break;

		case VERTEX_1_SLIDER_45:
			return mVertices[1].a_vertex_tangent.x;
			break;

		case VERTEX_1_SLIDER_46:
			return mVertices[1].a_vertex_tangent.y;
			break;

		case VERTEX_1_SLIDER_47:
			return mVertices[1].a_vertex_tangent.z;
			break;

		case VERTEX_1_SLIDER_48:
			return mVertices[1].a_vertex_uv.x;
			break;

		case VERTEX_1_SLIDER_49:
			return mVertices[1].a_vertex_uv.y;
			break;

		case VERTEX_2_SLIDER_53:
			return mVertices[2].a_vertex_pos.x;
			break;

		case VERTEX_2_SLIDER_54:
			return mVertices[2].a_vertex_pos.y;
			break;

		case VERTEX_2_SLIDER_55:
			return mVertices[2].a_vertex_pos.z;
			break;

		case VERTEX_2_SLIDER_56:
			return mVertices[2].a_vertex_normal.x;
			break;

		case VERTEX_2_SLIDER_57:
			return mVertices[2].a_vertex_normal.y;
			break;

		case VERTEX_2_SLIDER_58:
			return mVertices[2].a_vertex_normal.z;
			break;

		case VERTEX_2_SLIDER_59:
			return mVertices[2].a_vertex_tangent.x;
			break;

		case VERTEX_2_SLIDER_60:
			return mVertices[2].a_vertex_tangent.y;
			break;

		case VERTEX_2_SLIDER_61:
			return mVertices[2].a_vertex_tangent.z;
			break;

		case VERTEX_2_SLIDER_62:
			return mVertices[2].a_vertex_uv.x;
			break;

		case VERTEX_2_SLIDER_63:
			return mVertices[2].a_vertex_uv.y;
			break;

		case VERTEX_3_SLIDER_67:
			return mVertices[3].a_vertex_pos.x;
			break;

		case VERTEX_3_SLIDER_68:
			return mVertices[3].a_vertex_pos.y;
			break;

		case VERTEX_3_SLIDER_69:
			return mVertices[3].a_vertex_pos.z;
			break;

		case VERTEX_3_SLIDER_70:
			return mVertices[3].a_vertex_normal.x;
			break;

		case VERTEX_3_SLIDER_71:
			return mVertices[3].a_vertex_normal.y;
			break;

		case VERTEX_3_SLIDER_72:
			return mVertices[3].a_vertex_normal.z;
			break;

		case VERTEX_3_SLIDER_73:
			return mVertices[3].a_vertex_tangent.x;
			break;

		case VERTEX_3_SLIDER_74:
			return mVertices[3].a_vertex_tangent.y;
			break;

		case VERTEX_3_SLIDER_75:
			return mVertices[3].a_vertex_tangent.z;
			break;

		case VERTEX_3_SLIDER_76:
			return mVertices[3].a_vertex_uv.x;
			break;

		case VERTEX_3_SLIDER_77:
			return mVertices[3].a_vertex_uv.y;
			break;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
