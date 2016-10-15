
#include "CustomUi.h"
#include "ui/controls/button.h"
#include "ui/controls/label.h"
#include "ui/controls/panel.h"
#include "SliderModel.h"
#include "checkbox.h"
#include "Controls.h"
#include <sstream>
#include <iomanip>

namespace Rendering
{
RTTI_DEFINITIONS(CustomUi)

CustomUi::CustomUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	m_u_transform(),
	m_u_size(),
	mVertices(
{
	VertexStructure(),
					VertexStructure(),
					VertexStructure(),
					VertexStructure()
}),
mSliderModels(SLIDER_MODEL_COUNT),
mIsRestoreNeed(false)
{
}

CustomUi::~CustomUi()
{
}

void CustomUi::Initialize()
{
	UiAsset::Initialize();
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
	IS_ALL_SLIDER_MODELS_SET(mSliderModels)

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
			if (auto transformPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[U_TRANSFORM_PANEL_14].lock()))
			{
				transformPanel->set_visible(!transformPanel->get_visible());
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_SIZE_BUTTON_17].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto sizePanel = std::static_pointer_cast<eps::ui::button>(this->mControls[U_SIZE_PANEL_18].lock()))
			{
				sizePanel->set_visible(!sizePanel->get_visible());
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_22].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_0_PANEL_23].lock()))
			{
				ltPanel->set_visible(!ltPanel->get_visible());
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_1_PANEL_28].lock()))
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_2_PANEL_33].lock()))
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_3_PANEL_38].lock()))
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_27].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_0_PANEL_23].lock()))
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_1_PANEL_28].lock()))
			{
				rtPanel->set_visible(!rtPanel->get_visible());
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_2_PANEL_33].lock()))
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_3_PANEL_38].lock()))
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_32].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_0_PANEL_23].lock()))
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_1_PANEL_28].lock()))
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_2_PANEL_33].lock()))
			{
				rbPanel->set_visible(!rbPanel->get_visible());
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_3_PANEL_38].lock()))
			{
				lbPanel->set_visible(false);
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_37].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto ltPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_0_PANEL_23].lock()))
			{
				ltPanel->set_visible(false);
			}

			if (auto rtPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_1_PANEL_28].lock()))
			{
				rtPanel->set_visible(false);
			}

			if (auto rbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_2_PANEL_33].lock()))
			{
				rbPanel->set_visible(false);
			}

			if (auto lbPanel = std::static_pointer_cast<eps::ui::button>(this->mControls[VERTEX_3_PANEL_38].lock()))
			{
				lbPanel->set_visible(!lbPanel->get_visible());
			}
		});
	}
}

void CustomUi::Update(const Library::GameTime& aGameTime)
{
	UiAsset::Update(aGameTime);
	//
	DISPLAY_VALUE_AT_LABEL(m_u_transform[0][0], U_TRANSFORM_LABEL_1)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[0][1], U_TRANSFORM_LABEL_2)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[0][2], U_TRANSFORM_LABEL_3)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[1][0], U_TRANSFORM_LABEL_4)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[1][1], U_TRANSFORM_LABEL_5)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[1][2], U_TRANSFORM_LABEL_6)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[2][0], U_TRANSFORM_LABEL_7)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[2][1], U_TRANSFORM_LABEL_8)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[2][2], U_TRANSFORM_LABEL_9)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[3][0], U_TRANSFORM_LABEL_10)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[3][1], U_TRANSFORM_LABEL_11)
	DISPLAY_VALUE_AT_LABEL(m_u_transform[3][2], U_TRANSFORM_LABEL_12)
	DISPLAY_VALUE_AT_LABEL(m_u_size, U_SIZE_LABEL_16)
	//
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_20)
	DISPLAY_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_21)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_25)
	DISPLAY_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_26)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_30)
	DISPLAY_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_31)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_35)
	DISPLAY_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_36)
}

void CustomUi::Set_u_transform(const glm::mat4& a_u_transform)
{
	m_u_transform = a_u_transform;
	//
	SET_REAL_SLIDER_VALUE(m_u_transform[0][0], U_TRANSFORM_SLIDER_1)
	SET_REAL_SLIDER_VALUE(m_u_transform[0][1], U_TRANSFORM_SLIDER_2)
	SET_REAL_SLIDER_VALUE(m_u_transform[0][2], U_TRANSFORM_SLIDER_3)
	SET_REAL_SLIDER_VALUE(m_u_transform[1][0], U_TRANSFORM_SLIDER_4)
	SET_REAL_SLIDER_VALUE(m_u_transform[1][1], U_TRANSFORM_SLIDER_5)
	SET_REAL_SLIDER_VALUE(m_u_transform[1][2], U_TRANSFORM_SLIDER_6)
	SET_REAL_SLIDER_VALUE(m_u_transform[2][0], U_TRANSFORM_SLIDER_7)
	SET_REAL_SLIDER_VALUE(m_u_transform[2][1], U_TRANSFORM_SLIDER_8)
	SET_REAL_SLIDER_VALUE(m_u_transform[2][2], U_TRANSFORM_SLIDER_9)
	SET_REAL_SLIDER_VALUE(m_u_transform[3][0], U_TRANSFORM_SLIDER_10)
	SET_REAL_SLIDER_VALUE(m_u_transform[3][1], U_TRANSFORM_SLIDER_11)
	SET_REAL_SLIDER_VALUE(m_u_transform[3][2], U_TRANSFORM_SLIDER_12)
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
	SET_REAL_SLIDER_VALUE(m_u_size, U_SIZE_SLIDER_16)
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
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_20)
	SET_REAL_SLIDER_VALUE(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_21)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_25)
	SET_REAL_SLIDER_VALUE(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_26)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_30)
	SET_REAL_SLIDER_VALUE(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_31)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_35)
	SET_REAL_SLIDER_VALUE(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_36)
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
	if (auto directCheckbox = std::static_pointer_cast<Desktop::checkbox>
							  (mControls[GL_POINT_SPRITE_CHECKBOX].lock()))
	{
		return (Desktop::checkbox::state::CHECKED == directCheckbox->get_state());
	}

	return false;
}

bool CustomUi::IsVertexProgramPointSizeEnabled()
{
	if (auto directCheckbox = std::static_pointer_cast<Desktop::checkbox>
							  (mControls[GL_VERTEX_PROGRAM_POINT_SIZE_CHECKBOX].lock()))
	{
		return (Desktop::checkbox::state::CHECKED == directCheckbox->get_state());
	}

	return false;
}

void CustomUi::SetCheckBoxState(bool aPointSpriteEnabled, bool aVertexProgramPointSizeEnabled)
{
	if (auto directCheckbox = std::static_pointer_cast<Desktop::checkbox>
							  (mControls[GL_POINT_SPRITE_CHECKBOX].lock()))
	{
		directCheckbox->set_state(aPointSpriteEnabled ? Desktop::checkbox::state::CHECKED :
								  Desktop::checkbox::state::UNCHECKED);
	}

	if (auto directCheckbox = std::static_pointer_cast<Desktop::checkbox>
							  (mControls[GL_VERTEX_PROGRAM_POINT_SIZE_CHECKBOX].lock()))
	{
		directCheckbox->set_state(aVertexProgramPointSizeEnabled ? Desktop::checkbox::state::CHECKED :
								  Desktop::checkbox::state::UNCHECKED);
	}
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
		case U_TRANSFORM_SLIDER_1:
			modelValue = &m_u_transform[0][0];
			break;

		case U_TRANSFORM_SLIDER_2:
			modelValue = &m_u_transform[0][1];
			break;

		case U_TRANSFORM_SLIDER_3:
			modelValue = &m_u_transform[0][2];
			break;

		case U_TRANSFORM_SLIDER_4:
			modelValue = &m_u_transform[1][0];
			break;

		case U_TRANSFORM_SLIDER_5:
			modelValue = &m_u_transform[1][1];
			break;

		case U_TRANSFORM_SLIDER_6:
			modelValue = &m_u_transform[1][2];
			break;

		case U_TRANSFORM_SLIDER_7:
			modelValue = &m_u_transform[2][0];
			break;

		case U_TRANSFORM_SLIDER_8:
			modelValue = &m_u_transform[2][1];
			break;

		case U_TRANSFORM_SLIDER_9:
			modelValue = &m_u_transform[2][2];
			break;

		case U_TRANSFORM_SLIDER_10:
			modelValue = &m_u_transform[3][0];
			break;

		case U_TRANSFORM_SLIDER_11:
			modelValue = &m_u_transform[3][1];
			break;

		case U_TRANSFORM_SLIDER_12:
			modelValue = &m_u_transform[3][2];
			break;

		case U_SIZE_SLIDER_16:
			modelValue = &m_u_size;
			break;

		case VERTEX_0_SLIDER_20:
			modelValue = &mVertices[0].a_vertex_xy.x;
			break;

		case VERTEX_0_SLIDER_21:
			modelValue = &mVertices[0].a_vertex_xy.y;
			break;

		case VERTEX_1_SLIDER_25:
			modelValue = &mVertices[1].a_vertex_xy.x;
			break;

		case VERTEX_1_SLIDER_26:
			modelValue = &mVertices[1].a_vertex_xy.y;
			break;

		case VERTEX_2_SLIDER_30:
			modelValue = &mVertices[2].a_vertex_xy.x;
			break;

		case VERTEX_2_SLIDER_31:
			modelValue = &mVertices[2].a_vertex_xy.y;
			break;

		case VERTEX_3_SLIDER_35:
			modelValue = &mVertices[3].a_vertex_xy.x;
			break;

		case VERTEX_3_SLIDER_36:
			modelValue = &mVertices[3].a_vertex_xy.y;
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
