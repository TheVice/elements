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
	void Set_u_transform(const glm::mat4& a_u_transform);
	const glm::mat4& Get_u_transform() const;

	void Set_u_size(const float& a_u_size);
	const float& Get_u_size() const;

	void SetVertices(const std::vector<VertexStructure>& aVertices);
	const std::vector<VertexStructure>& GetVertices() const;

	bool IsNeedRestore() const;
	bool IsPointSpriteEnabled();
	bool IsVertexProgramPointSizeEnabled();

	void SetCheckBoxState(bool aPointSpriteEnabled, bool aVertexProgramPointSizeEnabled);

protected:
	virtual Library::SliderModel* GetSliderModel(int aSliderId, float aMin, float aMax) override;

private:
	glm::mat4 m_u_transform;
	float m_u_size;
	std::vector<VertexStructure> mVertices;

	std::vector<Library::SliderModel*> mSliderModels;

	bool mIsRestoreNeed;
};
}

#endif
