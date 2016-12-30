#ifndef _GRADIENT_MAPPING_UI_H_
#define _GRADIENT_MAPPING_UI_H_

#include "GradientMappingVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class GradientMappingUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(GradientMappingUi, UiAsset)

public:
	GradientMappingUi(Library::Game& aGame, const std::string& aAssetPath);
	~GradientMappingUi();

public:
	GradientMappingUi() = delete;
	GradientMappingUi(const GradientMappingUi& aRhs) = delete;
	GradientMappingUi& operator = (const GradientMappingUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_color_1(const eps::math::vec3& a_u_color_1);
	const eps::math::vec3& Get_u_color_1() const;

	void Set_u_color_2(const eps::math::vec3& a_u_color_2);
	const eps::math::vec3& Get_u_color_2() const;

	void SetVertices(const std::vector<GradientMappingVertex>& aVertices);
	const std::vector<GradientMappingVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::vec3 m_u_color_1;
	eps::math::vec3 m_u_color_2;
	std::vector<GradientMappingVertex> mVertices;
};
}

#endif
