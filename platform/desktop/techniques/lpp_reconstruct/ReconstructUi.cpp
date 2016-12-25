#include "ReconstructUi.h"
#include "ReconstructControls.h"
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
RTTI_DEFINITIONS(ReconstructUi)

ReconstructUi::ReconstructUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_matrix_mvp(),
	m_u_has_map_diffuse(),
	m_u_has_map_specular(),
	m_u_color_diffuse(),
	m_u_color_specular(),
	mVertices(
{
	ReconstructVertex(),
					  ReconstructVertex(),
					  ReconstructVertex(),
					  ReconstructVertex()
})
{
}

ReconstructUi::~ReconstructUi() = default;

bool ReconstructUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_MATRIX_MVP_BUTTON_13)
	IS_CONTROL_EXIST(U_COLOR_DIFFUSE_BUTTON_21)
	IS_CONTROL_EXIST(U_COLOR_SPECULAR_BUTTON_27)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_35)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_43)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_51)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_59)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	IS_CONTROL_EXIST(U_HAS_MAP_DIFFUSE_CHECK_16)
	IS_CONTROL_EXIST(U_HAS_MAP_SPECULAR_CHECK_17)
	//
	IS_CONTROL_EXIST(U_MATRIX_MVP_PANEL_14)
	IS_CONTROL_EXIST(U_COLOR_DIFFUSE_PANEL_22)
	IS_CONTROL_EXIST(U_COLOR_SPECULAR_PANEL_28)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_36)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_44)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_52)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_60)
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
	IS_CONTROL_EXIST(U_COLOR_DIFFUSE_LABEL_18)
	IS_CONTROL_EXIST(U_COLOR_DIFFUSE_LABEL_19)
	IS_CONTROL_EXIST(U_COLOR_DIFFUSE_LABEL_20)
	IS_CONTROL_EXIST(U_COLOR_DIFFUSE_LABEL_23)
	IS_CONTROL_EXIST(U_COLOR_SPECULAR_LABEL_24)
	IS_CONTROL_EXIST(U_COLOR_SPECULAR_LABEL_25)
	IS_CONTROL_EXIST(U_COLOR_SPECULAR_LABEL_26)
	IS_CONTROL_EXIST(U_COLOR_SPECULAR_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_34)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_37)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_38)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_39)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_40)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_41)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_42)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_45)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_46)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_47)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_48)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_49)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_50)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_53)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_54)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_55)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_56)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_57)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_58)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_61)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_MATRIX_MVP_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_MATRIX_MVP_PANEL_14].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_COLOR_DIFFUSE_PANEL_22)
				SET_VISIBLE(false, U_COLOR_SPECULAR_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_COLOR_DIFFUSE_BUTTON_21].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_DIFFUSE_PANEL_22].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_DIFFUSE_PANEL_22)
				SET_VISIBLE(false, U_COLOR_SPECULAR_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_COLOR_SPECULAR_BUTTON_27].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_COLOR_SPECULAR_PANEL_28].lock())
			{
				SET_VISIBLE(false, U_MATRIX_MVP_PANEL_14)
				SET_VISIBLE(false, U_COLOR_DIFFUSE_PANEL_22)
				SET_VISIBLE(!directPanel->get_visible(), U_COLOR_SPECULAR_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_35].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_36].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_36)
				SET_VISIBLE(false, VERTEX_1_PANEL_44)
				SET_VISIBLE(false, VERTEX_2_PANEL_52)
				SET_VISIBLE(false, VERTEX_3_PANEL_60)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_43].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_44].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_36)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_44)
				SET_VISIBLE(false, VERTEX_2_PANEL_52)
				SET_VISIBLE(false, VERTEX_3_PANEL_60)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_51].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_52].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_36)
				SET_VISIBLE(false, VERTEX_1_PANEL_44)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_52)
				SET_VISIBLE(false, VERTEX_3_PANEL_60)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_59].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_60].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_36)
				SET_VISIBLE(false, VERTEX_1_PANEL_44)
				SET_VISIBLE(false, VERTEX_2_PANEL_52)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_60)
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

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_HAS_MAP_DIFFUSE_CHECK_16].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			m_u_has_map_diffuse = !m_u_has_map_diffuse;
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>
							(mControls[U_HAS_MAP_SPECULAR_CHECK_17].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			m_u_has_map_specular = !m_u_has_map_specular;
		});
	}

	return true;
}

void ReconstructUi::Update()
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

	if (auto directPanel = mControls[U_COLOR_DIFFUSE_PANEL_22].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_diffuse[0], U_COLOR_DIFFUSE_LABEL_18)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_diffuse[1], U_COLOR_DIFFUSE_LABEL_19)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_diffuse[2], U_COLOR_DIFFUSE_LABEL_20)
		}
	}

	if (auto directPanel = mControls[U_COLOR_SPECULAR_PANEL_28].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_specular[0], U_COLOR_SPECULAR_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_specular[1], U_COLOR_SPECULAR_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_color_specular[2], U_COLOR_SPECULAR_LABEL_26)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_36].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.x, VERTEX_0_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.y, VERTEX_0_LABEL_31)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_pos.z, VERTEX_0_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_33)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_34)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_44].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.x, VERTEX_1_LABEL_38)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.y, VERTEX_1_LABEL_39)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_pos.z, VERTEX_1_LABEL_40)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_41)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_42)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_52].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.x, VERTEX_2_LABEL_46)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.y, VERTEX_2_LABEL_47)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_pos.z, VERTEX_2_LABEL_48)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_49)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_50)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_60].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.x, VERTEX_3_LABEL_54)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.y, VERTEX_3_LABEL_55)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_pos.z, VERTEX_3_LABEL_56)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_57)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_58)
		}
	}
}

void ReconstructUi::Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp)
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

const eps::math::mat4& ReconstructUi::Get_u_matrix_mvp() const
{
	return m_u_matrix_mvp;
}

/*void ReconstructUi::Set_u_has_map_diffuse(bool a_u_has_map_diffuse)
{
	m_u_has_map_diffuse = a_u_has_map_diffuse;
	//
	//
	mIsRestoreNeed = false;
}*/

bool ReconstructUi::Get_u_has_map_diffuse() const
{
	return m_u_has_map_diffuse;
}

/*void ReconstructUi::Set_u_has_map_specular(bool a_u_has_map_specular)
{
	m_u_has_map_specular = a_u_has_map_specular;
	//
	//
	mIsRestoreNeed = false;
}*/

bool ReconstructUi::Get_u_has_map_specular() const
{
	return m_u_has_map_specular;
}

void ReconstructUi::Set_u_color_diffuse(const eps::math::vec3& a_u_color_diffuse)
{
	m_u_color_diffuse = a_u_color_diffuse;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_diffuse[0], U_COLOR_DIFFUSE_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_diffuse[1], U_COLOR_DIFFUSE_SLIDER_19)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_diffuse[2], U_COLOR_DIFFUSE_SLIDER_20)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& ReconstructUi::Get_u_color_diffuse() const
{
	return m_u_color_diffuse;
}

void ReconstructUi::Set_u_color_specular(const eps::math::vec3& a_u_color_specular)
{
	m_u_color_specular = a_u_color_specular;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_color_specular[0], U_COLOR_SPECULAR_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_specular[1], U_COLOR_SPECULAR_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(m_u_color_specular[2], U_COLOR_SPECULAR_SLIDER_26)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec3& ReconstructUi::Get_u_color_specular() const
{
	return m_u_color_specular;
}

void ReconstructUi::SetVertices(const std::vector<ReconstructVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.x, VERTEX_0_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.y, VERTEX_0_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_pos.z, VERTEX_0_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_33)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_34)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.x, VERTEX_1_SLIDER_38)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.y, VERTEX_1_SLIDER_39)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_pos.z, VERTEX_1_SLIDER_40)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_41)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_42)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.x, VERTEX_2_SLIDER_46)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.y, VERTEX_2_SLIDER_47)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_pos.z, VERTEX_2_SLIDER_48)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_49)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_50)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.x, VERTEX_3_SLIDER_54)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.y, VERTEX_3_SLIDER_55)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_pos.z, VERTEX_3_SLIDER_56)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_57)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_58)
	//
	mIsRestoreNeed = false;
}

const std::vector<ReconstructVertex>& ReconstructUi::GetVertices() const
{
	return mVertices;
}

bool ReconstructUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& ReconstructUi::GetValueBySliderId(int aSliderId)
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

		case U_COLOR_DIFFUSE_SLIDER_18:
			return m_u_color_diffuse[0];

		case U_COLOR_DIFFUSE_SLIDER_19:
			return m_u_color_diffuse[1];

		case U_COLOR_DIFFUSE_SLIDER_20:
			return m_u_color_diffuse[2];

		case U_COLOR_SPECULAR_SLIDER_24:
			return m_u_color_specular[0];

		case U_COLOR_SPECULAR_SLIDER_25:
			return m_u_color_specular[1];

		case U_COLOR_SPECULAR_SLIDER_26:
			return m_u_color_specular[2];

		case VERTEX_0_SLIDER_30:
			return mVertices[0].a_vertex_pos.x;

		case VERTEX_0_SLIDER_31:
			return mVertices[0].a_vertex_pos.y;

		case VERTEX_0_SLIDER_32:
			return mVertices[0].a_vertex_pos.z;

		case VERTEX_0_SLIDER_33:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_34:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_38:
			return mVertices[1].a_vertex_pos.x;

		case VERTEX_1_SLIDER_39:
			return mVertices[1].a_vertex_pos.y;

		case VERTEX_1_SLIDER_40:
			return mVertices[1].a_vertex_pos.z;

		case VERTEX_1_SLIDER_41:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_42:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_46:
			return mVertices[2].a_vertex_pos.x;

		case VERTEX_2_SLIDER_47:
			return mVertices[2].a_vertex_pos.y;

		case VERTEX_2_SLIDER_48:
			return mVertices[2].a_vertex_pos.z;

		case VERTEX_2_SLIDER_49:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_50:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_54:
			return mVertices[3].a_vertex_pos.x;

		case VERTEX_3_SLIDER_55:
			return mVertices[3].a_vertex_pos.y;

		case VERTEX_3_SLIDER_56:
			return mVertices[3].a_vertex_pos.z;

		case VERTEX_3_SLIDER_57:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_58:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
