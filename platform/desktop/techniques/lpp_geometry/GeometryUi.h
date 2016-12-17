#ifndef _GEOMETRY_UI_H_
#define _GEOMETRY_UI_H_

#include "GeometryVertex.h"
#include <UiAsset.h>
#include <vector>

namespace Rendering
{
class GeometryUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(GeometryUi, UiAsset)

public:
	GeometryUi(Library::Game& aGame, const std::string& aAssetPath);
	~GeometryUi();

public:
	GeometryUi() = delete;
	GeometryUi(const GeometryUi& aRhs) = delete;
	GeometryUi& operator = (const GeometryUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_matrix_mvp(const eps::math::mat4& a_u_matrix_mvp);
	const eps::math::mat4& Get_u_matrix_mvp() const;

	void Set_u_matrix_model_view(const eps::math::mat4& a_u_matrix_model_view);
	const eps::math::mat4& Get_u_matrix_model_view() const;

	//void Set_u_has_map_normal(bool a_u_has_map_normal);
	bool Get_u_has_map_normal() const;

	void SetVertices(const std::vector<GeometryVertex>& aVertices);
	const std::vector<GeometryVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::mat4 m_u_matrix_mvp;
	eps::math::mat4 m_u_matrix_model_view;
	bool m_u_has_map_normal;
	std::vector<GeometryVertex> mVertices;
};
}

#endif
