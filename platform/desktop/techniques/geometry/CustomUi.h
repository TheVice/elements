#ifndef _CUSTOM_UI_H_
#define _CUSTOM_UI_H_

#include "Ui.h"

namespace Rendering
{
class CustomUi : public Desktop::Ui
{
	RTTI_DECLARATIONS(CustomUi, Ui)

public:
	CustomUi(Library::Game& aGame, const std::string& aAssetPath);
	~CustomUi();

public:
	CustomUi() = delete;
	CustomUi(const CustomUi& aRhs) = delete;
	CustomUi& operator = (const CustomUi& aRhs) = delete;

public:
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;

public:
	void SetMatrixMvp(const glm::mat4& aMatrixMvp);
	const glm::mat4& GetMatrixMvp() const;

protected:
	virtual Desktop::SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax) override;

private:
	glm::mat4 mMatrixMvp;
	glm::mat3 mMatrixNormal;
};
}

#endif
