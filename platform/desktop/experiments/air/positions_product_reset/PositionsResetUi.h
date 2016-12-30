#ifndef _POSITIONS_RESET_UI_H_
#define _POSITIONS_RESET_UI_H_

#include "PositionsResetVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class PositionsResetUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(PositionsResetUi, UiAsset)

public:
	PositionsResetUi(Library::Game& aGame, const std::string& aAssetPath);
	~PositionsResetUi();

public:
	PositionsResetUi() = delete;
	PositionsResetUi(const PositionsResetUi& aRhs) = delete;
	PositionsResetUi& operator = (const PositionsResetUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:

	void SetVertices(const std::vector<PositionsResetVertex>& aVertices);
	const std::vector<PositionsResetVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	std::vector<PositionsResetVertex> mVertices;
};
}

#endif
