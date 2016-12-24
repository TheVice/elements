#ifndef _SQUARE_TEXTURE_ALPHA_UI_H_
#define _SQUARE_TEXTURE_ALPHA_UI_H_

#include "SquareTextureAlphaVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class SquareTextureAlphaUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(SquareTextureAlphaUi, UiAsset)

public:
	SquareTextureAlphaUi(Library::Game& aGame, const std::string& aAssetPath);
	~SquareTextureAlphaUi();

public:
	SquareTextureAlphaUi() = delete;
	SquareTextureAlphaUi(const SquareTextureAlphaUi& aRhs) = delete;
	SquareTextureAlphaUi& operator = (const SquareTextureAlphaUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_transform(const eps::math::mat4& a_u_transform);
	const eps::math::mat4& Get_u_transform() const;

	void Set_u_color(const eps::math::vec4& a_u_color);
	const eps::math::vec4& Get_u_color() const;

	void SetVertices(const std::vector<SquareTextureAlphaVertex>& aVertices);
	const std::vector<SquareTextureAlphaVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::mat4 m_u_transform;
	eps::math::vec4 m_u_color;
	std::vector<SquareTextureAlphaVertex> mVertices;
};
}

#endif
