
#include "MetaballUi.h"
#include "MetaballControls.h"
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
RTTI_DEFINITIONS(MetaballUi)

MetaballUi::MetaballUi(Library::Game& aGame, const std::string& aAssetPath) :
	UiAsset(aGame, aAssetPath),
	mIsRestoreNeed(true),
	mVertices(
{
	MetaballVertex(),
				   MetaballVertex(),
				   MetaballVertex(),
				   MetaballVertex()
})
{
}

MetaballUi::~MetaballUi() = default;

bool MetaballUi::Initialize()
{
	if (!UiAsset::Initialize())
	{
		return false;
	}

	IS_CONTROL_EXIST(VERTEX_0_BUTTON_5)
	IS_CONTROL_EXIST(VERTEX_1_BUTTON_12)
	IS_CONTROL_EXIST(VERTEX_2_BUTTON_19)
	IS_CONTROL_EXIST(VERTEX_3_BUTTON_26)
	IS_CONTROL_EXIST(RESTORE_BUTTON)
	//
	IS_CONTROL_EXIST(VERTEX_0_PANEL_6)
	IS_CONTROL_EXIST(VERTEX_1_PANEL_13)
	IS_CONTROL_EXIST(VERTEX_2_PANEL_20)
	IS_CONTROL_EXIST(VERTEX_3_PANEL_27)
	//
	IS_CONTROL_EXIST(VERTEX_0_LABEL_1)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_2)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_3)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_4)
	IS_CONTROL_EXIST(VERTEX_0_LABEL_7)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_8)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_9)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_10)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_11)
	IS_CONTROL_EXIST(VERTEX_1_LABEL_14)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_15)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_16)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_17)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_18)
	IS_CONTROL_EXIST(VERTEX_2_LABEL_21)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_22)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_23)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_24)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_25)
	IS_CONTROL_EXIST(VERTEX_3_LABEL_28)
	//
	IS_ALL_SLIDER_MODELS_SET(SLIDER_MODEL_COUNT)

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_0_BUTTON_5].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_0_PANEL_6].lock())
			{
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_0_PANEL_6)
				SET_VISIBLE(false, VERTEX_1_PANEL_13)
				SET_VISIBLE(false, VERTEX_2_PANEL_20)
				SET_VISIBLE(false, VERTEX_3_PANEL_27)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_1_BUTTON_12].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_1_PANEL_13].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_6)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_1_PANEL_13)
				SET_VISIBLE(false, VERTEX_2_PANEL_20)
				SET_VISIBLE(false, VERTEX_3_PANEL_27)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_2_BUTTON_19].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_2_PANEL_20].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_6)
				SET_VISIBLE(false, VERTEX_1_PANEL_13)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_2_PANEL_20)
				SET_VISIBLE(false, VERTEX_3_PANEL_27)
			}
		});
	}

	if (auto directButton = std::static_pointer_cast<eps::ui::button>(mControls[VERTEX_3_BUTTON_26].lock()))
	{
		directButton->set_click([this](eps::ui::state)
		{
			if (auto directPanel = mControls[VERTEX_3_PANEL_27].lock())
			{
				SET_VISIBLE(false, VERTEX_0_PANEL_6)
				SET_VISIBLE(false, VERTEX_1_PANEL_13)
				SET_VISIBLE(false, VERTEX_2_PANEL_20)
				SET_VISIBLE(!directPanel->get_visible(), VERTEX_3_PANEL_27)
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

void MetaballUi::Update()
{
	UiAsset::Update();

	if (auto directPanel = mControls[VERTEX_0_PANEL_6].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.x, VERTEX_0_LABEL_1)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_xy.y, VERTEX_0_LABEL_2)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.x, VERTEX_0_LABEL_3)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[0].a_vertex_uv.y, VERTEX_0_LABEL_4)
		}
	}

	if (auto directPanel = mControls[VERTEX_1_PANEL_13].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.x, VERTEX_1_LABEL_8)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_xy.y, VERTEX_1_LABEL_9)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.x, VERTEX_1_LABEL_10)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[1].a_vertex_uv.y, VERTEX_1_LABEL_11)
		}
	}

	if (auto directPanel = mControls[VERTEX_2_PANEL_20].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.x, VERTEX_2_LABEL_15)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_xy.y, VERTEX_2_LABEL_16)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.x, VERTEX_2_LABEL_17)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[2].a_vertex_uv.y, VERTEX_2_LABEL_18)
		}
	}

	if (auto directPanel = mControls[VERTEX_3_PANEL_27].lock())
	{
		if (directPanel->get_visible())
		{
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.x, VERTEX_3_LABEL_22)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_xy.y, VERTEX_3_LABEL_23)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.x, VERTEX_3_LABEL_24)
			DISPLAY_FLOAT_VALUE_AT_LABEL(mVertices[3].a_vertex_uv.y, VERTEX_3_LABEL_25)
		}
	}
}


void MetaballUi::SetVertices(const std::vector<MetaballVertex>& aVertices)
{
	mVertices = aVertices;
	//
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.x, VERTEX_0_SLIDER_1)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_xy.y, VERTEX_0_SLIDER_2)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.x, VERTEX_0_SLIDER_3)
	SET_REAL_VALUE_AT_SLIDER(mVertices[0].a_vertex_uv.y, VERTEX_0_SLIDER_4)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.x, VERTEX_1_SLIDER_8)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_xy.y, VERTEX_1_SLIDER_9)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.x, VERTEX_1_SLIDER_10)
	SET_REAL_VALUE_AT_SLIDER(mVertices[1].a_vertex_uv.y, VERTEX_1_SLIDER_11)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.x, VERTEX_2_SLIDER_15)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_xy.y, VERTEX_2_SLIDER_16)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.x, VERTEX_2_SLIDER_17)
	SET_REAL_VALUE_AT_SLIDER(mVertices[2].a_vertex_uv.y, VERTEX_2_SLIDER_18)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.x, VERTEX_3_SLIDER_22)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_xy.y, VERTEX_3_SLIDER_23)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.x, VERTEX_3_SLIDER_24)
	SET_REAL_VALUE_AT_SLIDER(mVertices[3].a_vertex_uv.y, VERTEX_3_SLIDER_25)
	//
	mIsRestoreNeed = false;
}

const std::vector<MetaballVertex>& MetaballUi::GetVertices() const
{
	return mVertices;
}

bool MetaballUi::IsNeedRestore() const
{
	return mIsRestoreNeed;
}

float& MetaballUi::GetValueBySliderId(int aSliderId)
{
	switch (aSliderId)
	{
		case VERTEX_0_SLIDER_1:
			return mVertices[0].a_vertex_xy.x;

		case VERTEX_0_SLIDER_2:
			return mVertices[0].a_vertex_xy.y;

		case VERTEX_0_SLIDER_3:
			return mVertices[0].a_vertex_uv.x;

		case VERTEX_0_SLIDER_4:
			return mVertices[0].a_vertex_uv.y;

		case VERTEX_1_SLIDER_8:
			return mVertices[1].a_vertex_xy.x;

		case VERTEX_1_SLIDER_9:
			return mVertices[1].a_vertex_xy.y;

		case VERTEX_1_SLIDER_10:
			return mVertices[1].a_vertex_uv.x;

		case VERTEX_1_SLIDER_11:
			return mVertices[1].a_vertex_uv.y;

		case VERTEX_2_SLIDER_15:
			return mVertices[2].a_vertex_xy.x;

		case VERTEX_2_SLIDER_16:
			return mVertices[2].a_vertex_xy.y;

		case VERTEX_2_SLIDER_17:
			return mVertices[2].a_vertex_uv.x;

		case VERTEX_2_SLIDER_18:
			return mVertices[2].a_vertex_uv.y;

		case VERTEX_3_SLIDER_22:
			return mVertices[3].a_vertex_xy.x;

		case VERTEX_3_SLIDER_23:
			return mVertices[3].a_vertex_xy.y;

		case VERTEX_3_SLIDER_24:
			return mVertices[3].a_vertex_uv.x;

		case VERTEX_3_SLIDER_25:
			return mVertices[3].a_vertex_uv.y;

		default:
			assert(false);
	}

	static float modelValue = 0.0f;
	return modelValue;
}

}
