#ifndef _RECONSTRUCT_UI_H_
#define _RECONSTRUCT_UI_H_

#include "ReconstructVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class ReconstructUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(ReconstructUi, UiAsset)

public:
	ReconstructUi(Library::Game& aGame, const std::string& aAssetPath);
	~ReconstructUi();

public:
	ReconstructUi() = delete;
	ReconstructUi(const ReconstructUi& aRhs) = delete;
	ReconstructUi& operator = (const ReconstructUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp);
	const eps::math::mat4& Get_u_matrix_mvp() const;

	//	void Set_u_has_map_diffuse(bool a_u_has_map_diffuse);
	bool Get_u_has_map_diffuse() const;

	//	void Set_u_has_map_specular(bool a_u_has_map_specular);
	bool Get_u_has_map_specular() const;

	void Set_u_color_diffuse(const eps::math::vec3& a_u_color_diffuse);
	const eps::math::vec3& Get_u_color_diffuse() const;

	void Set_u_color_specular(const eps::math::vec3& a_u_color_specular);
	const eps::math::vec3& Get_u_color_specular() const;

	void SetVertices(const std::vector<ReconstructVertex>& aVertices);
	const std::vector<ReconstructVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::mat4 m_u_matrix_mvp;
	bool m_u_has_map_diffuse;
	bool m_u_has_map_specular;
	eps::math::vec3 m_u_color_diffuse;
	eps::math::vec3 m_u_color_specular;
	std::vector<ReconstructVertex> mVertices;
};
}

#endif
