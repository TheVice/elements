#include "ParticlesProductProcessUi.h"
#include "ParticlesProductProcessControls.h"
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
RTTI_DEFINITIONS(ParticlesProductProcessUi)

ParticlesProductProcessUi::ParticlesProductProcessUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_attractor_a(),
	m_u_attractor_b(),
	m_u_attractor_c(),
	m_u_attractor_d(),
	mVertices(
{
	ParticlesProductProcessVertex(),
								  ParticlesProductProcessVertex(),
								  ParticlesProductProcessVertex(),
								  ParticlesProductProcessVertex()
})
{
}

ParticlesProductProcessUi::~ParticlesProductProcessUi() = default;

bool ParticlesProductProcessUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_ATTRACTOR_A_BUTTON_2)
	IS_CONTROL_EXIST(U_ATTRACTOR_B_BUTTON_6)
	IS_CONTROL_EXIST(U_ATTRACTOR_C_BUTTON_10)
	IS_CONTROL_EXIST(U_ATTRACTOR_D_BUTTON_14)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_19)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_24)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_29)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_34)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_ATTRACTOR_A_PANEL_3)
	IS_CONTROL_EXIST(U_ATTRACTOR_B_PANEL_7)
	IS_CONTROL_EXIST(U_ATTRACTOR_C_PANEL_11)
	IS_CONTROL_EXIST(U_ATTRACTOR_D_PANEL_15)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_20)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_25)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_30)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_35)
	//
	IS_CONTROL_EXIST(U_ATTRACTOR_A_LABEL_1)
	IS_CONTROL_EXIST(U_ATTRACTOR_A_LABEL_4)
	IS_CONTROL_EXIST(U_ATTRACTOR_B_LABEL_5)
	IS_CONTROL_EXIST(U_ATTRACTOR_B_LABEL_8)
	IS_CONTROL_EXIST(U_ATTRACTOR_C_LABEL_9)
	IS_CONTROL_EXIST(U_ATTRACTOR_C_LABEL_12)
	IS_CONTROL_EXIST(U_ATTRACTOR_D_LABEL_13)
	IS_CONTROL_EXIST(U_ATTRACTOR_D_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_17)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_18)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_27)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_28)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_31)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_32)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_33)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_36)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_ATTRACTOR_A_BUTTON_2].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_ATTRACTOR_A_PANEL_3].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_ATTRACTOR_A_PANEL_3)
				SET_VISIBLE(false, U_ATTRACTOR_B_PANEL_7)
				SET_VISIBLE(false, U_ATTRACTOR_C_PANEL_11)
				SET_VISIBLE(false, U_ATTRACTOR_D_PANEL_15)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_ATTRACTOR_B_BUTTON_6].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_ATTRACTOR_B_PANEL_7].lock())
			{
				SET_VISIBLE(false, U_ATTRACTOR_A_PANEL_3)
				SET_VISIBLE(!directPanel->get_visible(), U_ATTRACTOR_B_PANEL_7)
				SET_VISIBLE(false, U_ATTRACTOR_C_PANEL_11)
				SET_VISIBLE(false, U_ATTRACTOR_D_PANEL_15)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_ATTRACTOR_C_BUTTON_10].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_ATTRACTOR_C_PANEL_11].lock())
			{
				SET_VISIBLE(false, U_ATTRACTOR_A_PANEL_3)
				SET_VISIBLE(false, U_ATTRACTOR_B_PANEL_7)
				SET_VISIBLE(!directPanel->get_visible(), U_ATTRACTOR_C_PANEL_11)
				SET_VISIBLE(false, U_ATTRACTOR_D_PANEL_15)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_ATTRACTOR_D_BUTTON_14].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_ATTRACTOR_D_PANEL_15].lock())
			{
				SET_VISIBLE(false, U_ATTRACTOR_A_PANEL_3)
				SET_VISIBLE(false, U_ATTRACTOR_B_PANEL_7)
				SET_VISIBLE(false, U_ATTRACTOR_C_PANEL_11)
				SET_VISIBLE(!directPanel->get_visible(), U_ATTRACTOR_D_PANEL_15)
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
				SET_VISIBLE(false, VERTEX_1_PANEL_25)
				SET_VISIBLE(false, VERTEX_2_PANEL_30)
				SET_VISIBLE(false, VERTEX_3_PANEL_35)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_24].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_25].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_20)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_25)
				SET_VISIBLE(false, VERTEX_2_PANEL_30)
				SET_VISIBLE(false, VERTEX_3_PANEL_35)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_29].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_30].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_20)
				SET_VISIBLE(false, VERTEX_1_PANEL_25)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_30)
				SET_VISIBLE(false, VERTEX_3_PANEL_35)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_34].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_35].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_20)
				SET_VISIBLE(false, VERTEX_1_PANEL_25)
				SET_VISIBLE(false, VERTEX_2_PANEL_30)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_35)
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

void ParticlesProductProcessUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_ATTRACTOR_A_PANEL_3].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_attractor_a, U_ATTRACTOR_A_LABEL_1)
		}
	}

	if (auto directPanel = mControls[U_ATTRACTOR_B_PANEL_7].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_attractor_b, U_ATTRACTOR_B_LABEL_5)
		}
	}

	if (auto directPanel = mControls[U_ATTRACTOR_C_PANEL_11].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_attractor_c, U_ATTRACTOR_C_LABEL_9)
		}
	}

	if (auto directPanel = mControls[U_ATTRACTOR_D_PANEL_15].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_attractor_d, U_ATTRACTOR_D_LABEL_13)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_20].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_18)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_25].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_23)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_30].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_27)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_28)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_35].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_32)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_33)
		}
	}
}

void ParticlesProductProcessUi::Set_u_attractor_a(const float& a_u_attractor_a)
{
	m_u_attractor_a = a_u_attractor_a;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_attractor_a, U_ATTRACTOR_A_SLIDER_1)
	//
	mIsRestoreNeed = false;
}

const float& ParticlesProductProcessUi::Get_u_attractor_a() const
{
	return m_u_attractor_a;
}

void ParticlesProductProcessUi::Set_u_attractor_b(const float& a_u_attractor_b)
{
	m_u_attractor_b = a_u_attractor_b;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_attractor_b, U_ATTRACTOR_B_SLIDER_5)
	//
	mIsRestoreNeed = false;
}

const float& ParticlesProductProcessUi::Get_u_attractor_b() const
{
	return m_u_attractor_b;
}

void ParticlesProductProcessUi::Set_u_attractor_c(const float& a_u_attractor_c)
{
	m_u_attractor_c = a_u_attractor_c;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_attractor_c, U_ATTRACTOR_C_SLIDER_9)
	//
	mIsRestoreNeed = false;
}

const float& ParticlesProductProcessUi::Get_u_attractor_c() const
{
	return m_u_attractor_c;
}

void ParticlesProductProcessUi::Set_u_attractor_d(const float& a_u_attractor_d)
{
	m_u_attractor_d = a_u_attractor_d;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_attractor_d, U_ATTRACTOR_D_SLIDER_13)
	//
	mIsRestoreNeed = false;
}

const float& ParticlesProductProcessUi::Get_u_attractor_d() const
{
	return m_u_attractor_d;
}

void ParticlesProductProcessUi::SetVertices(const std::vector<ParticlesProductProcessVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_27)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_28)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_32)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_33)
	//
	mIsRestoreNeed = false;
}

const std::vector<ParticlesProductProcessVertex>& ParticlesProductProcessUi::GetVertices() const
{
	return mVertices;
}

bool ParticlesProductProcessUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& ParticlesProductProcessUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_ATTRACTOR_A_SLIDER_1:
			return m_u_attractor_a;

		case U_ATTRACTOR_B_SLIDER_5:
			return m_u_attractor_b;

		case U_ATTRACTOR_C_SLIDER_9:
			return m_u_attractor_c;

		case U_ATTRACTOR_D_SLIDER_13:
			return m_u_attractor_d;

		case VERTEX_0_SLIDER_17:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_18:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_1_SLIDER_22:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_23:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_2_SLIDER_27:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_28:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_3_SLIDER_32:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_33:
			return mVertices[3].a_vertex_xy.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
