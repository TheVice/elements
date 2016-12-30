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

	IS_CONTROL_EXIST(VERTEX_0_BUTTON_3)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_8)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_13)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_18)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	//
	IS_CONTROL_EXIST(VERTEX_0_PANEL_4)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_9)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_14)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_19)
	//
	IS_CONTROL_EXIST(VERTEX_0_LABEL_1)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_2)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_5)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_6)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_7)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_10)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_11)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_12)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_17)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_20)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_3].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_4].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_4)
				SET_VISIBLE(false, VERTEX_1_PANEL_9)
				SET_VISIBLE(false, VERTEX_2_PANEL_14)
				SET_VISIBLE(false, VERTEX_3_PANEL_19)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_8].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_9].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_4)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_9)
				SET_VISIBLE(false, VERTEX_2_PANEL_14)
				SET_VISIBLE(false, VERTEX_3_PANEL_19)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_13].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_14].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_4)
				SET_VISIBLE(false, VERTEX_1_PANEL_9)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_14)
				SET_VISIBLE(false, VERTEX_3_PANEL_19)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_18].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_19].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_4)
				SET_VISIBLE(false, VERTEX_1_PANEL_9)
				SET_VISIBLE(false, VERTEX_2_PANEL_14)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_19)
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

	if (auto directPanel = mControls[VERTEX_0_PANEL_4].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_positions_uv.x, VERTEX_0_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_positions_uv.y, VERTEX_0_LABEL_2)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_9].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_positions_uv.x, VERTEX_1_LABEL_6)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_positions_uv.y, VERTEX_1_LABEL_7)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_14].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_positions_uv.x, VERTEX_2_LABEL_11)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_positions_uv.y, VERTEX_2_LABEL_12)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_19].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_positions_uv.x, VERTEX_3_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_positions_uv.y, VERTEX_3_LABEL_17)
		}
	}
}


void ParticlesUi::SetVertices(const std::vector<ParticlesVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_positions_uv.x, VERTEX_0_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_positions_uv.y, VERTEX_0_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_positions_uv.x, VERTEX_1_SLIDER_6)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_positions_uv.y, VERTEX_1_SLIDER_7)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_positions_uv.x, VERTEX_2_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_positions_uv.y, VERTEX_2_SLIDER_12)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_positions_uv.x, VERTEX_3_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_positions_uv.y, VERTEX_3_SLIDER_17)
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
		case VERTEX_0_SLIDER_1:
			return mVertices[0].a_positions_uv.x;

		case VERTEX_0_SLIDER_2:
			return mVertices[0].a_positions_uv.y;

		case VERTEX_1_SLIDER_6:
			return mVertices[1].a_positions_uv.x;

		case VERTEX_1_SLIDER_7:
			return mVertices[1].a_positions_uv.y;

		case VERTEX_2_SLIDER_11:
			return mVertices[2].a_positions_uv.x;

		case VERTEX_2_SLIDER_12:
			return mVertices[2].a_positions_uv.y;

		case VERTEX_3_SLIDER_16:
			return mVertices[3].a_positions_uv.x;

		case VERTEX_3_SLIDER_17:
			return mVertices[3].a_positions_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
