#ifndef _UI_ASSET_H_
#define _UI_ASSET_H_

#include "DrawableUiGameComponent.h"
#include <elements/ui/system.h>
#include <map>

namespace Library
{
class SliderModel;
class UiAsset : public DrawableUiGameComponent
{
	RTTI_DECLARATIONS(UiAsset, DrawableUiGameComponent)

public:
	UiAsset(Game& aGame, const std::string& aAssetPath);
	~UiAsset();

public:
	UiAsset() = delete;
	UiAsset(const UiAsset& aRhs) = delete;
	UiAsset& operator = (const UiAsset& aRhs) = delete;

public:
	virtual bool Initialize() override;

protected:
	virtual SliderModel* GetSliderModel(int aSliderId);
	virtual SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax);

protected:
	std::map<std::string, std::weak_ptr<eps::ui::control>> mControls;

private:
	const std::string mAssetPath;
};
}

#define IS_CONTROL_EXIST(CONTROL_NAME)														\
	if (!mControls.count(CONTROL_NAME))														\
	{																						\
		throw std::runtime_error(std::string(CONTROL_NAME) + std::string(" not exist"));	\
	}


#define DISPLAY_VALUE_AT_LABEL(VALUE, LABEL)													\
	if (auto directLabel = std::static_pointer_cast<eps::ui::label>(mControls[LABEL].lock()))	\
	{																							\
		std::ostringstream message;																\
		message << std::setprecision(2) << VALUE;												\
		directLabel->set_text(message.str());													\
	}


#define SET_REAL_SLIDER_VALUE(VALUE, SLIDER)	\
	mSliderModels[SLIDER]->setRealValue(VALUE);


#define SET_VISIBLE(VALUE, CONTROL)							\
	if (auto directControl = (mControls[CONTROL].lock()))	\
	{														\
		directControl->set_visible(VALUE);					\
	}

#define IS_ALL_SLIDER_MODELS_SET(SLIDER_MODELS)						\
	for (const auto& sliderModel : SLIDER_MODELS)					\
	{																\
		if (!sliderModel)											\
		{															\
			throw std::runtime_error("Not all slider models set");	\
		}															\
	}

#endif
