#ifndef _POSITIONS_PRODUCT_RESET_UI_H_
#define _POSITIONS_PRODUCT_RESET_UI_H_

#include "PositionsProductResetVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class PositionsProductResetUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(PositionsProductResetUi, UiAsset)

public:
	PositionsProductResetUi(Library::Game& aGame, const std::string& aAssetPath);
	~PositionsProductResetUi();

public:
	PositionsProductResetUi() = delete;
	PositionsProductResetUi(const PositionsProductResetUi& aRhs) = delete;
	PositionsProductResetUi& operator = (const PositionsProductResetUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:

	void SetVertices(const std::vector<PositionsProductResetVertex>& aVertices);
	const std::vector<PositionsProductResetVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	std::vector<PositionsProductResetVertex> mVertices;
};
}

#endif
