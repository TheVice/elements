
#include "ProjectorUi.h"
#include "ProjectorControls.h"
#include <checkbox.h>
#include <SliderModel.h>
#include <elements/ui/controls/button.h>
#include <elements/ui/controls/check.h>
#include <elements/ui/controls/label.h>
#include <elements/ui/controls/panel.h>
#include <elements/ui/controls/slider.h>

namespace Rendering
{
RTTI_DEFINITIONS(ProjectorUi)

ProjectorUi::ProjectorUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_matrix_mvp(),
	m_u_matrix_model(),
	m_u_matrix_pvp(),
	mVertices(
{
	VertexStructure(),
					VertexStructure(),
					VertexStructure(),
					VertexStructure()
})
{
}

ProjectorUi::~ProjectorUi()
{
}

bool ProjectorUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(RESTORE_BUTTON)
	IS_CONTROL_EXIST(U_MATRIX_MVP_BUTTON_13)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_BUTTON_28)
	IS_CONTROL_EXIST(U_MATRIX_PVP_BUTTON_43)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_49)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_55)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_61)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_67)
	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_PANEL_14)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_PANEL_29)
	IS_CONTROL_EXIST(U_MATRIX_PVP_PANEL_44)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_50)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_56)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_62)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_68)
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
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_16)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_17)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_18)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_19)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_20)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_21)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_22)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_23)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_24)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_25)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_26)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_27)
	IS_CONTROL_EXIST(U_MATRIX_MODEL_LABEL_30)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_31)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_32)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_33)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_34)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_35)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_36)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_37)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_38)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_39)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_40)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_41)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_42)
	IS_CONTROL_EXIST(U_MATRIX_PVP_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_47)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_48)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_51)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_52)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_53)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_54)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_57)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_58)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_59)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_60)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_63)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_64)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_65)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_66)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_69)
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
				SET_VISIBLE(false, U_MATRIX_MODEL_PANEL_29)
				SET_VISIBLE(false, U_MATRIX_PVP_PANEL_44)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_MODEL_BUTTON_28].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_MATRIX_MODEL_PANEL_29].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(!directPanel->get_visible(), U_MATRIX_MODEL_PANEL_29)
				SET_VISIBLE(false, U_MATRIX_PVP_PANEL_44)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_PVP_BUTTON_43].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_MATRIX_PVP_PANEL_44].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_MATRIX_MODEL_PANEL_29)
				SET_VISIBLE(!directPanel->get_visible(), U_MATRIX_PVP_PANEL_44)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_49].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_50].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_50)
				SET_VISIBLE(false, VERTEX_1_PANEL_56)
				SET_VISIBLE(false, VERTEX_2_PANEL_62)
				SET_VISIBLE(false, VERTEX_3_PANEL_68)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_55].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_56].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_50)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_56)
				SET_VISIBLE(false, VERTEX_2_PANEL_62)
				SET_VISIBLE(false, VERTEX_3_PANEL_68)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_61].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_62].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_50)
				SET_VISIBLE(false, VERTEX_1_PANEL_56)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_62)
				SET_VISIBLE(false, VERTEX_3_PANEL_68)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_67].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_68].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_50)
				SET_VISIBLE(false, VERTEX_1_PANEL_56)
				SET_VISIBLE(false, VERTEX_2_PANEL_62)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_68)
			}
		});
	}

	return true;
}

void ProjectorUi::Update()
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

	if (auto directPanel = mControls[U_MATRIX_MODEL_PANEL_29].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[0][0], U_MATRIX_MODEL_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[0][1], U_MATRIX_MODEL_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[0][2], U_MATRIX_MODEL_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[1][0], U_MATRIX_MODEL_LABEL_19)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[1][1], U_MATRIX_MODEL_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[1][2], U_MATRIX_MODEL_LABEL_21)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[2][0], U_MATRIX_MODEL_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[2][1], U_MATRIX_MODEL_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[2][2], U_MATRIX_MODEL_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[3][0], U_MATRIX_MODEL_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[3][1], U_MATRIX_MODEL_LABEL_26)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_model[3][2], U_MATRIX_MODEL_LABEL_27)
		}
	}

	if (auto directPanel = mControls[U_MATRIX_PVP_PANEL_44].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[0][0], U_MATRIX_PVP_LABEL_31)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[0][1], U_MATRIX_PVP_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[0][2], U_MATRIX_PVP_LABEL_33)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[1][0], U_MATRIX_PVP_LABEL_34)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[1][1], U_MATRIX_PVP_LABEL_35)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[1][2], U_MATRIX_PVP_LABEL_36)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[2][0], U_MATRIX_PVP_LABEL_37)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[2][1], U_MATRIX_PVP_LABEL_38)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[2][2], U_MATRIX_PVP_LABEL_39)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[3][0], U_MATRIX_PVP_LABEL_40)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[3][1], U_MATRIX_PVP_LABEL_41)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_matrix_pvp[3][2], U_MATRIX_PVP_LABEL_42)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_50].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VERTEX_0_LABEL_46)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VERTEX_0_LABEL_47)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VERTEX_0_LABEL_48)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_56].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VERTEX_1_LABEL_52)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VERTEX_1_LABEL_53)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VERTEX_1_LABEL_54)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_62].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VERTEX_2_LABEL_58)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VERTEX_2_LABEL_59)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VERTEX_2_LABEL_60)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_68].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VERTEX_3_LABEL_64)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VERTEX_3_LABEL_65)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VERTEX_3_LABEL_66)
		}
	}
}

void ProjectorUi::Set_u_matrix_mvp(const glm::mat4& a_u_matrix_mvp)
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

const glm::mat4& ProjectorUi::Get_u_matrix_mvp() const
{
	return m_u_matrix_mvp;
}

void ProjectorUi::Set_u_matrix_model(const glm::mat4& a_u_matrix_model)
{
	m_u_matrix_model = a_u_matrix_model;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[0][0], U_MATRIX_MODEL_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[0][1], U_MATRIX_MODEL_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[0][2], U_MATRIX_MODEL_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[1][0], U_MATRIX_MODEL_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[1][1], U_MATRIX_MODEL_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[1][2], U_MATRIX_MODEL_SLIDER_21)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[2][0], U_MATRIX_MODEL_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[2][1], U_MATRIX_MODEL_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[2][2], U_MATRIX_MODEL_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[3][0], U_MATRIX_MODEL_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[3][1], U_MATRIX_MODEL_SLIDER_26)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_model[3][2], U_MATRIX_MODEL_SLIDER_27)
	//
	mIsRestoreNeed = false;
}

const glm::mat4& ProjectorUi::Get_u_matrix_model() const
{
	return m_u_matrix_model;
}

void ProjectorUi::Set_u_matrix_pvp(const glm::mat4& a_u_matrix_pvp)
{
	m_u_matrix_pvp = a_u_matrix_pvp;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[0][0], U_MATRIX_PVP_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[0][1], U_MATRIX_PVP_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[0][2], U_MATRIX_PVP_SLIDER_33)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[1][0], U_MATRIX_PVP_SLIDER_34)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[1][1], U_MATRIX_PVP_SLIDER_35)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[1][2], U_MATRIX_PVP_SLIDER_36)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[2][0], U_MATRIX_PVP_SLIDER_37)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[2][1], U_MATRIX_PVP_SLIDER_38)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[2][2], U_MATRIX_PVP_SLIDER_39)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[3][0], U_MATRIX_PVP_SLIDER_40)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[3][1], U_MATRIX_PVP_SLIDER_41)
	SET_REAL_VALUE_AT_SLIDER(m_u_matrix_pvp[3][2], U_MATRIX_PVP_SLIDER_42)
	//
	mIsRestoreNeed = false;
}

const glm::mat4& ProjectorUi::Get_u_matrix_pvp() const
{
	return m_u_matrix_pvp;
}

void ProjectorUi::SetVertices(const std::vector<VertexStructure>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.x, VERTEX_0_SLIDER_46)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.y, VERTEX_0_SLIDER_47)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.z, VERTEX_0_SLIDER_48)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.x, VERTEX_1_SLIDER_52)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.y, VERTEX_1_SLIDER_53)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.z, VERTEX_1_SLIDER_54)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.x, VERTEX_2_SLIDER_58)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.y, VERTEX_2_SLIDER_59)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.z, VERTEX_2_SLIDER_60)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.x, VERTEX_3_SLIDER_64)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.y, VERTEX_3_SLIDER_65)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.z, VERTEX_3_SLIDER_66)
	//
	mIsRestoreNeed = false;
}

const std::vector<VertexStructure>& ProjectorUi::GetVertices() const
{
	return mVertices;
}

bool ProjectorUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& ProjectorUi::GetValueBySliderId(int aSliderId)
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

		case U_MATRIX_MODEL_SLIDER_16:
			return m_u_matrix_model[0][0];

		case U_MATRIX_MODEL_SLIDER_17:
			return m_u_matrix_model[0][1];

		case U_MATRIX_MODEL_SLIDER_18:
			return m_u_matrix_model[0][2];

		case U_MATRIX_MODEL_SLIDER_19:
			return m_u_matrix_model[1][0];

		case U_MATRIX_MODEL_SLIDER_20:
			return m_u_matrix_model[1][1];

		case U_MATRIX_MODEL_SLIDER_21:
			return m_u_matrix_model[1][2];

		case U_MATRIX_MODEL_SLIDER_22:
			return m_u_matrix_model[2][0];

		case U_MATRIX_MODEL_SLIDER_23:
			return m_u_matrix_model[2][1];

		case U_MATRIX_MODEL_SLIDER_24:
			return m_u_matrix_model[2][2];

		case U_MATRIX_MODEL_SLIDER_25:
			return m_u_matrix_model[3][0];

		case U_MATRIX_MODEL_SLIDER_26:
			return m_u_matrix_model[3][1];

		case U_MATRIX_MODEL_SLIDER_27:
			return m_u_matrix_model[3][2];

		case U_MATRIX_PVP_SLIDER_31:
			return m_u_matrix_pvp[0][0];

		case U_MATRIX_PVP_SLIDER_32:
			return m_u_matrix_pvp[0][1];

		case U_MATRIX_PVP_SLIDER_33:
			return m_u_matrix_pvp[0][2];

		case U_MATRIX_PVP_SLIDER_34:
			return m_u_matrix_pvp[1][0];

		case U_MATRIX_PVP_SLIDER_35:
			return m_u_matrix_pvp[1][1];

		case U_MATRIX_PVP_SLIDER_36:
			return m_u_matrix_pvp[1][2];

		case U_MATRIX_PVP_SLIDER_37:
			return m_u_matrix_pvp[2][0];

		case U_MATRIX_PVP_SLIDER_38:
			return m_u_matrix_pvp[2][1];

		case U_MATRIX_PVP_SLIDER_39:
			return m_u_matrix_pvp[2][2];

		case U_MATRIX_PVP_SLIDER_40:
			return m_u_matrix_pvp[3][0];

		case U_MATRIX_PVP_SLIDER_41:
			return m_u_matrix_pvp[3][1];

		case U_MATRIX_PVP_SLIDER_42:
			return m_u_matrix_pvp[3][2];

		case VERTEX_0_SLIDER_46:
			return mVertices[0].a_vertex_pos.x;

		case VERTEX_0_SLIDER_47:
			return mVertices[0].a_vertex_pos.y;

		case VERTEX_0_SLIDER_48:
			return mVertices[0].a_vertex_pos.z;

		case VERTEX_1_SLIDER_52:
			return mVertices[1].a_vertex_pos.x;

		case VERTEX_1_SLIDER_53:
			return mVertices[1].a_vertex_pos.y;

		case VERTEX_1_SLIDER_54:
			return mVertices[1].a_vertex_pos.z;

		case VERTEX_2_SLIDER_58:
			return mVertices[2].a_vertex_pos.x;

		case VERTEX_2_SLIDER_59:
			return mVertices[2].a_vertex_pos.y;

		case VERTEX_2_SLIDER_60:
			return mVertices[2].a_vertex_pos.z;

		case VERTEX_3_SLIDER_64:
			return mVertices[3].a_vertex_pos.x;

		case VERTEX_3_SLIDER_65:
			return mVertices[3].a_vertex_pos.y;

		case VERTEX_3_SLIDER_66:
			return mVertices[3].a_vertex_pos.z;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
