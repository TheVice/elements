#ifndef _POSITIONS_PROCESS_UI_H_
#define _POSITIONS_PROCESS_UI_H_

#include "PositionsProcessVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class PositionsProcessUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(PositionsProcessUi, UiAsset)

public:
	PositionsProcessUi(Library::Game& aGame, const std::string& aAssetPath);
	~PositionsProcessUi();

public:
	PositionsProcessUi() = delete;
	PositionsProcessUi(const PositionsProcessUi& aRhs) = delete;
	PositionsProcessUi& operator = (const PositionsProcessUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_dt(const float& a_u_dt);
	const float& Get_u_dt() const;

	void SetVertices(const std::vector<PositionsProcessVertex>& aVertices);
	const std::vector<PositionsProcessVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	float m_u_dt;
	std::vector<PositionsProcessVertex> mVertices;
};
}

#endif
