#ifndef _LIQUID_UI_H_
#define _LIQUID_UI_H_

#include "LiquidVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class LiquidUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(LiquidUi, UiAsset)

public:
	LiquidUi(Library::Game& aGame, const std::string& aAssetPath);
	~LiquidUi();

public:
	LiquidUi() = delete;
	LiquidUi(const LiquidUi& aRhs) = delete;
	LiquidUi& operator = (const LiquidUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_surface_color(const eps::math::vec4& a_u_surface_color);
	const eps::math::vec4& Get_u_surface_color() const;

	void Set_u_surface_texel(const eps::math::vec2& a_u_surface_texel);
	const eps::math::vec2& Get_u_surface_texel() const;

	void SetVertices(const std::vector<LiquidVertex>& aVertices);
	const std::vector<LiquidVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::vec4 m_u_surface_color;
	eps::math::vec2 m_u_surface_texel;
	std::vector<LiquidVertex> mVertices;
};
}

#endif
