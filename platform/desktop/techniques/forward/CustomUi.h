#ifndef _CUSTOM_UI_H_
#define _CUSTOM_UI_H_

#include "VertexStructure.h"
#include <UiAsset.h>

namespace Rendering
{
class CustomUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(CustomUi, UiAsset)

public:
	CustomUi(Library::Game& aGame, const std::string& aAssetPath);
	~CustomUi();

public:
	CustomUi() = delete;
	CustomUi(const CustomUi& aRhs) = delete;
	CustomUi& operator = (const CustomUi& aRhs) = delete;

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

	void SetVertices(const std::vector<VertexStructure>& aVertices);
	const std::vector<VertexStructure>& GetVertices() const;

	bool IsNeedRestore() const;

protected:
	virtual Library::SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax) override;

private:
	glm::mat4 m_u_matrix_mvp;
	glm::mat4 m_u_matrix_model_view;
	glm::mat3 m_u_matrix_normal;
	glm::mat4 m_u_matrix_view;
	glm::vec3 m_u_camera_pos;
	glm::vec3 m_u_light_pos;
	glm::vec3 m_u_light_intensity;
	float m_u_light_range;
	std::vector<VertexStructure> mVertices;

	std::vector<Library::SliderModel*> mSliderModels;

	bool mIsRestoreNeed;
};
}

#endif
