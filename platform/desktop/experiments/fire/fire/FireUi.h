#ifndef _FIRE_UI_H_
#define _FIRE_UI_H_

#include "FireVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class FireUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(FireUi, UiAsset)

public:
	FireUi(Library::Game& aGame, const std::string& aAssetPath);
	~FireUi();

public:
	FireUi() = delete;
	FireUi(const FireUi& aRhs) = delete;
	FireUi& operator = (const FireUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_texel(const eps::math::vec2& a_u_texel);
	const eps::math::vec2& Get_u_texel() const;

	void SetVertices(const std::vector<FireVertex>& aVertices);
	const std::vector<FireVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::vec2 m_u_texel;
	std::vector<FireVertex> mVertices;
};
}

#endif
