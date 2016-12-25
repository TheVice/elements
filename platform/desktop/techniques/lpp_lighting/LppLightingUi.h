#ifndef _LPP_LIGHTING_UI_H_
#define _LPP_LIGHTING_UI_H_

#include "LppLightingVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class LppLightingUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(LppLightingUi, UiAsset)

public:
	LppLightingUi(Library::Game& aGame, const std::string& aAssetPath);
	~LppLightingUi();

public:
	LppLightingUi() = delete;
	LppLightingUi(const LppLightingUi& aRhs) = delete;
	LppLightingUi& operator = (const LppLightingUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp);
	const eps::math::mat4& Get_u_matrix_mvp() const;

	void Set_u_camera_view_param(const eps::math::vec2& a_u_camera_view_param);
	const eps::math::vec2& Get_u_camera_view_param() const;

	void Set_u_camera_near(const float& a_u_camera_near);
	const float& Get_u_camera_near() const;

	void Set_u_camera_far(const float& a_u_camera_far);
	const float& Get_u_camera_far() const;

	void Set_u_light_pos(const eps::math::vec3& a_u_light_pos);
	const eps::math::vec3& Get_u_light_pos() const;

	void Set_u_light_intensity(const eps::math::vec3& a_u_light_intensity);
	const eps::math::vec3& Get_u_light_intensity() const;

	void Set_u_light_inv_range_square(const float& a_u_light_inv_range_square);
	const float& Get_u_light_inv_range_square() const;

	void SetVertices(const std::vector<LppLightingVertex>& aVertices);
	const std::vector<LppLightingVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::mat4 m_u_matrix_mvp;
	eps::math::vec2 m_u_camera_view_param;
	float m_u_camera_near;
	float m_u_camera_far;
	eps::math::vec3 m_u_light_pos;
	eps::math::vec3 m_u_light_intensity;
	float m_u_light_inv_range_square;
	std::vector<LppLightingVertex> mVertices;
};
}

#endif
