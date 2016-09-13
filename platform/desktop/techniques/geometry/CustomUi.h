#ifndef _CUSTOM_UI_H_
#define _CUSTOM_UI_H_

#include "UiAsset.h"
#include "VertexStructure.h"

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
	virtual void Initialize() override;
	virtual void Update(const Library::GameTime& aGameTime) override;

public:
	void Set_u_matrix_mvp(const glm::mat4& a_u_matrix_mvp);
	const glm::mat4& Get_u_matrix_mvp() const;

	void Set_u_matrix_normal(const glm::mat3& a_u_matrix_normal);
	const glm::mat3& Get_u_matrix_normal() const;

	void SetVertices(const std::vector<VertexStructure>& aVertices);
	const std::vector<VertexStructure>& GetVertices() const;

	bool IsNeedRestore() const;
	bool IsEncodeNormal() const;

	void SetEncodeNormalControlsVisible(bool aVisible);

protected:
	virtual Library::SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax) override;

private:
	glm::mat4 m_u_matrix_mvp;
	glm::mat3 m_u_matrix_normal;
	std::vector<VertexStructure> mVertices;

	std::vector<Library::SliderModel*> mSliderModels;

	bool mIsRestoreNeed;
	bool mIsEncodeNormal;
};
}

#endif