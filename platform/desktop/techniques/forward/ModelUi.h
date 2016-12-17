#ifndef _MODEL_UI_H_
#define _MODEL_UI_H_

#include "ModelVertex.h"
#include <UiAsset.h>
#include <vector>

namespace Rendering
{
class ModelUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(ModelUi, UiAsset)

public:
	ModelUi(Library::Game& aGame, const std::string& aAssetPath);
	~ModelUi();

public:
	ModelUi() = delete;
	ModelUi(const ModelUi& aRhs) = delete;
	ModelUi& operator = (const ModelUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_matrix_mvp(const glm::mat4& a_u_matrix_mvp);
	const glm::mat4& Get_u_matrix_mvp() const;

	void Set_u_matrix_model_view(const glm::mat4& a_u_matrix_model_view);
	const glm::mat4& Get_u_matrix_model_view() const;

	void Set_u_matrix_normal(const glm::mat3& a_u_matrix_normal);
	const glm::mat3& Get_u_matrix_normal() const;

	void Set_u_matrix_view(const glm::mat4& a_u_matrix_view);
	const glm::mat4& Get_u_matrix_view() const;

	void Set_u_camera_pos(const glm::vec3& a_u_camera_pos);
	const glm::vec3& Get_u_camera_pos() const;

	void Set_u_light_pos(const glm::vec3& a_u_light_pos);
	const glm::vec3& Get_u_light_pos() const;

	void Set_u_light_intensity(const glm::vec3& a_u_light_intensity);
	const glm::vec3& Get_u_light_intensity() const;

	void Set_u_light_range(float a_u_light_range);
	float Get_u_light_range() const;

	void SetVertices(const std::vector<ModelVertex>& aVertices);
	const std::vector<ModelVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	glm::mat4 m_u_matrix_mvp;
	glm::mat4 m_u_matrix_model_view;
	glm::mat3 m_u_matrix_normal;
	glm::mat4 m_u_matrix_view;
	glm::vec3 m_u_camera_pos;
	glm::vec3 m_u_light_pos;
	glm::vec3 m_u_light_intensity;
	float m_u_light_range;
	std::vector<ModelVertex> mVertices;
};
}

#endif
