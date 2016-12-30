#ifndef _LIGHT_SCATTERED_OCCLUDING_UI_H_
#define _LIGHT_SCATTERED_OCCLUDING_UI_H_

#include "LightScatteredOccludingVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class LightScatteredOccludingUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(LightScatteredOccludingUi, UiAsset)

public:
	LightScatteredOccludingUi(Library::Game& aGame, const std::string& aAssetPath);
	~LightScatteredOccludingUi();

public:
	LightScatteredOccludingUi() = delete;
	LightScatteredOccludingUi(const LightScatteredOccludingUi& aRhs) = delete;
	LightScatteredOccludingUi& operator = (const LightScatteredOccludingUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_size(const float& a_u_size);
	const float& Get_u_size() const;

	void SetVertices(const std::vector<LightScatteredOccludingVertex>& aVertices);
	const std::vector<LightScatteredOccludingVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	float m_u_size;
	std::vector<LightScatteredOccludingVertex> mVertices;
};
}

#endif
