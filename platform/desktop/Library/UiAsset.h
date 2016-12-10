#ifndef _UI_ASSET_H_
#define _UI_ASSET_H_

#include "DrawableUiGameComponent.h"
#include <map>
#include <string>
#include <cstdio>

namespace Library
{
class ValueSliderModel;
class UiAsset : public DrawableUiGameComponent
{
	RTTI_DECLARATIONS(UiAsset, DrawableUiGameComponent)

public:
	UiAsset(Game& aGame, const std::string& aAssetPath);
	virtual ~UiAsset();

public:
	UiAsset() = delete;
	UiAsset(const UiAsset& aRhs) = delete;
	UiAsset& operator = (const UiAsset& aRhs) = delete;

public:
	virtual bool Initialize() override;

private:
	virtual float& GetValueBySliderId(int aSliderId);

protected:
	std::map<std::string, std::weak_ptr<eps::ui::control>> mControls;
	std::map<int, ValueSliderModel*> mSliderModels;

private:
	const std::string mAssetPath;
};
}

#define DISPLAY_FLOAT_VALUE_AT_LABEL(VALUE, LABEL)												\
	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls[LABEL].lock()))	\
	{																							\
		if (directLabel->get_visible())															\
		{																						\
			const auto written = std::snprintf(nullptr, 0, "%.2f", VALUE);						\
			std::string message(written, '\0');													\
			std::sprintf(&message.front(), "%.2f", VALUE);										\
			directLabel->set_text(message);														\
		}																						\
	}

#define SET_VISIBLE(VALUE, CONTROL)							\
	if (auto directControl = (mControls[CONTROL].lock()))	\
	{														\
		directControl->set_visible(VALUE);					\
	}

#define SET_REAL_VALUE_AT_SLIDER(VALUE, SLIDER_ID)	\
	mSliderModels[SLIDER_ID]->setRealValue(VALUE);

#define IS_ALL_SLIDER_MODELS_SET(SLIDER_COUNT)	\
	for (int i = 0; i < SLIDER_COUNT; ++i)		\
	{											\
		if (!mSliderModels.count(i))			\
		{										\
			return false;						\
		}										\
	}

#define IS_CONTROL_EXIST(CONTROL_NAME)		\
	if (!mControls.count(CONTROL_NAME))		\
	{										\
		return false;						\
	}

#endif
