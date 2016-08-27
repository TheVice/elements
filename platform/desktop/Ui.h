#ifndef _UI_H_
#define _UI_H_

#include "DrawableGameComponent.h"
#include "ui/system.h"
#include <map>

namespace Desktop
{
class SliderModel;
class Ui : public Library::DrawableGameComponent
{
	RTTI_DECLARATIONS(Ui, DrawableGameComponent)

public:
	Ui(Library::Game& aGame, const std::string& aAssetPath);
	~Ui();

public:
	Ui() = delete;
	Ui(const Ui& aRhs) = delete;
	Ui& operator = (const Ui& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;
	virtual void Draw(const Library::GameTime& aGameTime) override;

protected:
	virtual SliderModel* GetSliderModel(int aSliderId);
	virtual SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax);

private:
	const std::string mAssetPath;
	bool mTouchDown;
	eps::math::mat4 mTransformTouch;
	std::unique_ptr<eps::ui::system> mUiSystem;

protected:
	std::map<std::string, std::weak_ptr<eps::ui::control>> mControls;
};
}

#endif
