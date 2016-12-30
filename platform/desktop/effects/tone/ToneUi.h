#ifndef _TONE_UI_H_
#define _TONE_UI_H_

#include "ToneVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class ToneUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(ToneUi, UiAsset)

public:
	ToneUi(Library::Game& aGame, const std::string& aAssetPath);
	~ToneUi();

public:
	ToneUi() = delete;
	ToneUi(const ToneUi& aRhs) = delete;
	ToneUi& operator = (const ToneUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_exposure(const float& a_u_exposure);
	const float& Get_u_exposure() const;

	void Set_u_gamma(const float& a_u_gamma);
	const float& Get_u_gamma() const;

	void SetVertices(const std::vector<ToneVertex>& aVertices);
	const std::vector<ToneVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	float m_u_exposure;
	float m_u_gamma;
	std::vector<ToneVertex> mVertices;
};
}

#endif
