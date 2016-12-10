
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
	mIsRestoreNeed(true),
	m_u_transform(),
	m_u_size(),
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

	//
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	IS_CONTROL_EXIST(U_TRANSFORM_BUTTON_13)
	IS_CONTROL_EXIST(U_SIZE_BUTTON_17)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_22)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_27)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_32)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_37)
	//
	IS_CONTROL_EXIST(U_TRANSFORM_PANEL_14)
	IS_CONTROL_EXIST(U_SIZE_PANEL_18)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_23)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_28)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_33)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_38)
	//
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_1)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_2)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_3)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_4)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_5)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_6)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_7)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_8)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_9)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_10)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_11)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_12)
	IS_CONTROL_EXIST(U_TRANSFORM_LABEL_15)
	IS_CONTROL_EXIST(U_SIZE_LABEL_16)
	IS_CONTROL_EXIST(U_SIZE_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_20)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_29)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_30)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_34)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_35)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_36)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_39)
	IS_CONTROL_EXIST(GL_POINT_SPRITE_LABEL)
	IS_CONTROL_EXIST(GL_VERTEX_PROGRAM_POINT_SIZE_LABEL)
	//
	IS_CONTROL_EXIST(GL_POINT_SPRITE_CHECKBOX)
	IS_CONTROL_EXIST(GL_VERTEX_PROGRAM_POINT_SIZE_CHECKBOX)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[RESTORE_BUTTON].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			this->mIsRestoreNeed = !this->mIsRestoreNeed;
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_TRANSFORM_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto transformPanel = this->mControls[U_TRANSFORM_PANEL_14].lock())
			{
				transformPanel->set_visible(!transformPanel->get_visible());
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_SIZE_BUTTON_17].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto sizePanel = this->mControls[U_SIZE_PANEL_18].lock())
			{
				sizePanel->set_visible(!sizePanel->get_visible());
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_22].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_23].lock())
			{
				ltPanel->set_visible(!ltPanel->get_visible());
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_28].lock())
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_33].lock())
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_38].lock())
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_27].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_23].lock())
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_28].lock())
			{
				rtPanel->set_visible(!rtPanel->get_visible());
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_33].lock())
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_38].lock())
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_32].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_23].lock())
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_28].lock())
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_33].lock())
			{
				rbPanel->set_visible(!rbPanel->get_visible());
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_38].lock())
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_37].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = this->mControls[VERTEX_0_PANEL_23].lock())
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = this->mControls[VERTEX_1_PANEL_28].lock())
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = this->mControls[VERTEX_2_PANEL_33].lock())
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = this->mControls[VERTEX_3_PANEL_38].lock())
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

	if (auto directPanel = this->mControls[U_TRANSFORM_PANEL_14].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[0][0], U_TRANSFORM_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[0][1], U_TRANSFORM_LABEL_2)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[0][2], U_TRANSFORM_LABEL_3)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[1][0], U_TRANSFORM_LABEL_4)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[1][1], U_TRANSFORM_LABEL_5)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[1][2], U_TRANSFORM_LABEL_6)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[2][0], U_TRANSFORM_LABEL_7)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[2][1], U_TRANSFORM_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[2][2], U_TRANSFORM_LABEL_9)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[3][0], U_TRANSFORM_LABEL_10)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[3][1], U_TRANSFORM_LABEL_11)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_transform[3][2], U_TRANSFORM_LABEL_12)
		}
	}

	if (auto directPanel = this->mControls[U_SIZE_PANEL_18].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_size, U_SIZE_LABEL_16)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_0_PANEL_23].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_21)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_1_PANEL_28].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_26)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_2_PANEL_33].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_30)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_31)
		}
	}

	if (auto directPanel = this->mControls[VERTEX_3_PANEL_38].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_35)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_36)
		}
	}
}

void CustomUi::Set_u_transform(const glm::mat4& a_u_transform)
{
	m_u_transform = a_u_transform;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[0][0], U_TRANSFORM_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[0][1], U_TRANSFORM_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[0][2], U_TRANSFORM_SLIDER_3)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[1][0], U_TRANSFORM_SLIDER_4)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[1][1], U_TRANSFORM_SLIDER_5)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[1][2], U_TRANSFORM_SLIDER_6)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[2][0], U_TRANSFORM_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[2][1], U_TRANSFORM_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[2][2], U_TRANSFORM_SLIDER_9)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[3][0], U_TRANSFORM_SLIDER_10)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[3][1], U_TRANSFORM_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(m_u_transform[3][2], U_TRANSFORM_SLIDER_12)
	//
	mIsRestoreNeed = false;
}

const glm::mat4& CustomUi::Get_u_transform() const
{
	return m_u_transform;
}

void CustomUi::Set_u_size(const float& a_u_size)
{
	m_u_size = a_u_size;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_size, U_SIZE_SLIDER_16)
	//
	mIsRestoreNeed = false;
}

const float& CustomUi::Get_u_size() const
{
	return m_u_size;
}

void CustomUi::SetVertices(const std::vector<VertexStructure>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_21)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_26)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_30)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_31)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_35)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_36)
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

bool CustomUi::IsPointSpriteEnabled()
{
	if (auto directCheckbox = std::static_pointer_cast<Library::checkbox>
							  (mControls[GL_POINT_SPRITE_CHECKBOX].lock()))
	{
		return (Library::checkbox::state::CHECKED == directCheckbox->get_state());
	}

	return false;
}

bool CustomUi::IsVertexProgramPointSizeEnabled()
{
	if (auto directCheckbox = std::static_pointer_cast<Library::checkbox>
							  (mControls[GL_VERTEX_PROGRAM_POINT_SIZE_CHECKBOX].lock()))
	{
		return (Library::checkbox::state::CHECKED == directCheckbox->get_state());
	}

	return false;
}

void CustomUi::SetCheckBoxState(bool aPointSpriteEnabled, bool aVertexProgramPointSizeEnabled)
{
	if (auto directCheckbox = std::static_pointer_cast<Library::checkbox>
							  (mControls[GL_POINT_SPRITE_CHECKBOX].lock()))
	{
		directCheckbox->set_state(aPointSpriteEnabled ? Library::checkbox::state::CHECKED :
								  Library::checkbox::state::UNCHECKED);
	}

	if (auto directCheckbox = std::static_pointer_cast<Library::checkbox>
							  (mControls[GL_VERTEX_PROGRAM_POINT_SIZE_CHECKBOX].lock()))
	{
		directCheckbox->set_state(aVertexProgramPointSizeEnabled ? Library::checkbox::state::CHECKED :
								  Library::checkbox::state::UNCHECKED);
	}
}

float& CustomUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_TRANSFORM_SLIDER_1:
			return m_u_transform[0][0];

		case U_TRANSFORM_SLIDER_2:
			return m_u_transform[0][1];

		case U_TRANSFORM_SLIDER_3:
			return m_u_transform[0][2];

		case U_TRANSFORM_SLIDER_4:
			return m_u_transform[1][0];

		case U_TRANSFORM_SLIDER_5:
			return m_u_transform[1][1];

		case U_TRANSFORM_SLIDER_6:
			return m_u_transform[1][2];

		case U_TRANSFORM_SLIDER_7:
			return m_u_transform[2][0];

		case U_TRANSFORM_SLIDER_8:
			return m_u_transform[2][1];

		case U_TRANSFORM_SLIDER_9:
			return m_u_transform[2][2];

		case U_TRANSFORM_SLIDER_10:
			return m_u_transform[3][0];

		case U_TRANSFORM_SLIDER_11:
			return m_u_transform[3][1];

		case U_TRANSFORM_SLIDER_12:
			return m_u_transform[3][2];

		case U_SIZE_SLIDER_16:
			return m_u_size;

		case VERTEX_0_SLIDER_20:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_21:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_1_SLIDER_25:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_26:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_2_SLIDER_30:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_31:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_3_SLIDER_35:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_36:
			return mVertices[3].a_vertex_xy.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
