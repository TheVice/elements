#ifndef _SQUARE_TEXTURE_UI_H_
#define _SQUARE_TEXTURE_UI_H_

#include "SquareTextureVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class SquareTextureUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(SquareTextureUi, UiAsset)

public:
	SquareTextureUi(Library::Game& aGame, const std::string& aAssetPath);
	~SquareTextureUi();

public:
	SquareTextureUi() = delete;
	SquareTextureUi(const SquareTextureUi& aRhs) = delete;
	SquareTextureUi& operator = (const SquareTextureUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_transform(const eps::math::mat4& a_u_transform);
	const eps::math::mat4& Get_u_transform() const;

	void SetVertices(const std::vector<SquareTextureVertex>& aVertices);
	const std::vector<SquareTextureVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::mat4 m_u_transform;
	std::vector<SquareTextureVertex> mVertices;
};
}

#endif
