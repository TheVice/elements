#ifndef _CAPS_VIEW_H_
#define _CAPS_VIEW_H_

#include <DrawableUiGameComponent.h>
#include <map>

namespace Library
{
class CapsView : public DrawableUiGameComponent
{
	RTTI_DECLARATIONS(CapsView, DrawableUiGameComponent)

public:
	CapsView(Game& aGame);
	~CapsView();

public:
	CapsView() = delete;
	CapsView(const CapsView& aRhs) = delete;
	CapsView& operator = (const CapsView& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

protected:
	virtual const std::map<std::string, unsigned int>& GetCaps() const;

protected:
	std::map<std::string, std::weak_ptr<eps::ui::control>> mControls;
};
}

#endif
