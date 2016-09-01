#ifndef _CAPS_VIEW_H_
#define _CAPS_VIEW_H_

#include "DrawableUiGameComponent.h"
#include <map>

namespace Desktop
{
class CapsView : public DrawableUiGameComponent
{
	RTTI_DECLARATIONS(CapsView, DrawableUiGameComponent)

public:
	CapsView(Library::Game& aGame);
	~CapsView();

public:
	CapsView() = delete;
	CapsView(const CapsView& aRhs) = delete;
	CapsView& operator = (const CapsView& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;

private:
	std::map<std::string, std::weak_ptr<eps::ui::control>> mControls;

private:
	static const std::map<std::string, unsigned int> mCaps;
};
}

#endif
