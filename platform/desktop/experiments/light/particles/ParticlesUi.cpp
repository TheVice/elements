#include "ParticlesUi.h"
#include "ParticlesControls.h"
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
RTTI_DEFINITIONS(ParticlesUi)

ParticlesUi::ParticlesUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	m_u_texel(),
	m_u_size(),
	mVertices(
{
	ParticlesVertex(),
					ParticlesVertex(),
					ParticlesVertex(),
					ParticlesVertex()
})
{
}

ParticlesUi::~ParticlesUi() = default;

bool ParticlesUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(U_TEXEL_BUTTON_3)
	IS_CONTROL_EXIST(U_SIZE_BUTTON_7)
	IS_CONTROL_EXIST(VERTEX_0_BUTTON_12)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_17)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_22)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_27)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(U_TEXEL_PANEL_4)
	IS_CONTROL_EXIST(U_SIZE_PANEL_8)
	IS_CONTROL_EXIST(VERTEX_0_PANEL_13)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_18)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_23)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_28)
	//
	IS_CONTROL_EXIST(U_TEXEL_LABEL_1)
	IS_CONTROL_EXIST(U_TEXEL_LABEL_2)
	IS_CONTROL_EXIST(U_TEXEL_LABEL_5)
	IS_CONTROL_EXIST(U_SIZE_LABEL_6)
	IS_CONTROL_EXIST(U_SIZE_LABEL_9)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_10)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_11)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_14)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_19)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_20)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_26)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_29)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_TEXEL_BUTTON_3].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_TEXEL_PANEL_4].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), U_TEXEL_PANEL_4)
				SET_VISIBLE(false, U_SIZE_PANEL_8)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[U_SIZE_BUTTON_7].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[U_SIZE_PANEL_8].lock())
			{
				SET_VISIBLE(false, U_TEXEL_PANEL_4)
				SET_VISIBLE(!directPanel->get_visible(), U_SIZE_PANEL_8)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_12].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_13].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_13)
				SET_VISIBLE(false, VERTEX_1_PANEL_18)
				SET_VISIBLE(false, VERTEX_2_PANEL_23)
				SET_VISIBLE(false, VERTEX_3_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_17].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_18].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_13)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_18)
				SET_VISIBLE(false, VERTEX_2_PANEL_23)
				SET_VISIBLE(false, VERTEX_3_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_22].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_23].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_13)
				SET_VISIBLE(false, VERTEX_1_PANEL_18)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_23)
				SET_VISIBLE(false, VERTEX_3_PANEL_28)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_27].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_28].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_13)
				SET_VISIBLE(false, VERTEX_1_PANEL_18)
				SET_VISIBLE(false, VERTEX_2_PANEL_23)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_28)
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

void ParticlesUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[U_TEXEL_PANEL_4].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_texel[0], U_TEXEL_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_texel[1], U_TEXEL_LABEL_2)
		}
	}

	if (auto directPanel = mControls[U_SIZE_PANEL_8].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(m_u_size, U_SIZE_LABEL_6)
		}
	}

	if (auto directPanel = mControls[VERTEX_0_PANEL_13].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_product_uv.x, VERTEX_0_LABEL_10)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_product_uv.y, VERTEX_0_LABEL_11)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_18].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_product_uv.x, VERTEX_1_LABEL_15)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_product_uv.y, VERTEX_1_LABEL_16)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_23].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_product_uv.x, VERTEX_2_LABEL_20)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_product_uv.y, VERTEX_2_LABEL_21)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_28].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_product_uv.x, VERTEX_3_LABEL_25)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_product_uv.y, VERTEX_3_LABEL_26)
		}
	}
}

void ParticlesUi::Set_u_texel(const eps::math::vec2& a_u_texel)
{
	m_u_texel = a_u_texel;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_texel[0], U_TEXEL_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(m_u_texel[1], U_TEXEL_SLIDER_2)
	//
	mIsRestoreNeed = false;
}

const eps::math::vec2& ParticlesUi::Get_u_texel() const
{
	return m_u_texel;
}

void ParticlesUi::Set_u_size(const float& a_u_size)
{
	m_u_size = a_u_size;
	//
	SET_REAL_VALUE_AT_SLIDER(m_u_size, U_SIZE_SLIDER_6)
	//
	mIsRestoreNeed = false;
}

const float& ParticlesUi::Get_u_size() const
{
	return m_u_size;
}

void ParticlesUi::SetVertices(const std::vector<ParticlesVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_product_uv.x, VERTEX_0_SLIDER_10)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_product_uv.y, VERTEX_0_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_product_uv.x, VERTEX_1_SLIDER_15)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_product_uv.y, VERTEX_1_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_product_uv.x, VERTEX_2_SLIDER_20)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_product_uv.y, VERTEX_2_SLIDER_21)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_product_uv.x, VERTEX_3_SLIDER_25)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_product_uv.y, VERTEX_3_SLIDER_26)
	//
	mIsRestoreNeed = false;
}

const std::vector<ParticlesVertex>& ParticlesUi::GetVertices() const
{
	return mVertices;
}

bool ParticlesUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& ParticlesUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case U_TEXEL_SLIDER_1:
			return m_u_texel[0];

		case U_TEXEL_SLIDER_2:
			return m_u_texel[1];

		case U_SIZE_SLIDER_6:
			return m_u_size;

		case VERTEX_0_SLIDER_10:
			return mVertices[0].a_product_uv.x;

		case VERTEX_0_SLIDER_11:
			return mVertices[0].a_product_uv.y;

		case VERTEX_1_SLIDER_15:
			return mVertices[1].a_product_uv.x;

		case VERTEX_1_SLIDER_16:
			return mVertices[1].a_product_uv.y;

		case VERTEX_2_SLIDER_20:
			return mVertices[2].a_product_uv.x;

		case VERTEX_2_SLIDER_21:
			return mVertices[2].a_product_uv.y;

		case VERTEX_3_SLIDER_25:
			return mVertices[3].a_product_uv.x;

		case VERTEX_3_SLIDER_26:
			return mVertices[3].a_product_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
