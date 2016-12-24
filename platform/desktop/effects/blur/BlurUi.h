#ifndef _BLUR_UI_H_
#define _BLUR_UI_H_

#include "BlurVertex.h"
#include <UiAsset.h>
#include <vector>

namespace Rendering
{
class BlurUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(BlurUi, UiAsset)

public:
	BlurUi(Library::Game& aGame, const std::string& aAssetPath);
	~BlurUi();

public:
	BlurUi() = delete;
	BlurUi(const BlurUi& aRhs) = delete;
	BlurUi& operator = (const BlurUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_offset(const eps::math::vec2& a_u_offset);
	const eps::math::vec2& Get_u_offset() const;

	void SetVertices(const std::vector<BlurVertex>& aVertices);
	const std::vector<BlurVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::vec2 m_u_offset;
	std::vector<BlurVertex> mVertices;
};
}

#endif
