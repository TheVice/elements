#ifndef _PROJECTOR_UI_H_
#define _PROJECTOR_UI_H_

#include "ProjectorVertex.h"
#include <UiAsset.h>
#include <vector>

namespace Rendering
{
class ProjectorUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(ProjectorUi, UiAsset)

public:
	ProjectorUi(Library::Game& aGame, const std::string& aAssetPath);
	~ProjectorUi();

public:
	ProjectorUi() = delete;
	ProjectorUi(const ProjectorUi& aRhs) = delete;
	ProjectorUi& operator = (const ProjectorUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_matrix_mvp(const glm::mat4& a_u_matrix_mvp);
	const glm::mat4& Get_u_matrix_mvp() const;

	void Set_u_matrix_model(const glm::mat4& a_u_matrix_model);
	const glm::mat4& Get_u_matrix_model() const;

	void Set_u_matrix_pvp(const glm::mat4& a_u_matrix_pvp);
	const glm::mat4& Get_u_matrix_pvp() const;

	void SetVertices(const std::vector<ProjectorVertex>& aVertices);
	const std::vector<ProjectorVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	glm::mat4 m_u_matrix_mvp;
	glm::mat4 m_u_matrix_model;
	glm::mat4 m_u_matrix_pvp;
	std::vector<ProjectorVertex> mVertices;
};
}

#endif
