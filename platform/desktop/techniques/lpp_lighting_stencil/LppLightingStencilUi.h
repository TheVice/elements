#ifndef _LPP_LIGHTING_STENCIL_UI_H_
#define _LPP_LIGHTING_STENCIL_UI_H_

#include "LppLightingStencilVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class LppLightingStencilUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(LppLightingStencilUi, UiAsset)

public:
	LppLightingStencilUi(Library::Game& aGame, const std::string& aAssetPath);
	~LppLightingStencilUi();

public:
	LppLightingStencilUi() = delete;
	LppLightingStencilUi(const LppLightingStencilUi& aRhs) = delete;
	LppLightingStencilUi& operator = (const LppLightingStencilUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp);
	const eps::math::mat4& Get_u_matrix_mvp() const;

	void SetVertices(const std::vector<LppLightingStencilVertex>& aVertices);
	const std::vector<LppLightingStencilVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::mat4 m_u_matrix_mvp;
	std::vector<LppLightingStencilVertex> mVertices;
};
}

#endif
