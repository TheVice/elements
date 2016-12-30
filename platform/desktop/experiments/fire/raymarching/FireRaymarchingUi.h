#ifndef _FIRE_RAYMARCHING_UI_H_
#define _FIRE_RAYMARCHING_UI_H_

#include "FireRaymarchingVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class FireRaymarchingUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(FireRaymarchingUi, UiAsset)

public:
	FireRaymarchingUi(Library::Game& aGame, const std::string& aAssetPath);
	~FireRaymarchingUi();

public:
	FireRaymarchingUi() = delete;
	FireRaymarchingUi(const FireRaymarchingUi& aRhs) = delete;
	FireRaymarchingUi& operator = (const FireRaymarchingUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_dt(const float& a_u_dt);
	const float& Get_u_dt() const;

	void Set_u_intensity(const float& a_u_intensity);
	const float& Get_u_intensity() const;

	void Set_u_covering(const float& a_u_covering);
	const float& Get_u_covering() const;

	void Set_u_texel(const eps::math::vec2& a_u_texel);
	const eps::math::vec2& Get_u_texel() const;

	void Set_u_color_hot(const eps::math::vec3& a_u_color_hot);
	const eps::math::vec3& Get_u_color_hot() const;

	void Set_u_color_cold(const eps::math::vec3& a_u_color_cold);
	const eps::math::vec3& Get_u_color_cold() const;

	void SetVertices(const std::vector<FireRaymarchingVertex>& aVertices);
	const std::vector<FireRaymarchingVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	float m_u_dt;
	float m_u_intensity;
	float m_u_covering;
	eps::math::vec2 m_u_texel;
	eps::math::vec3 m_u_color_hot;
	eps::math::vec3 m_u_color_cold;
	std::vector<FireRaymarchingVertex> mVertices;
};
}

#endif
