#ifndef _UI_ASSET_H_
#define _UI_ASSET_H_

#include "DrawableUiGameComponent.h"
#include "ui/system.h"
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
	virtual void Initialize() override;

protected:
	virtual SliderModel* GetSliderModel(int aSliderId);
	virtual SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax);

private:
	const std::string mAssetPath;

protected:
	std::map<std::string, std::weak_ptr<eps::ui::control>> mControls;
};
}

#endif
