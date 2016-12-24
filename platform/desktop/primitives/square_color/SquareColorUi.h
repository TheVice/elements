#ifndef _SQUARE_COLOR_UI_H_
#define _SQUARE_COLOR_UI_H_

#include "SquareColorVertex.h"
#include <UiAsset.h>
#include <elements/math/types.h>
#include <vector>

namespace Rendering
{
class SquareColorUi : public Library::UiAsset
{
	RTTI_DECLARATIONS(SquareColorUi, UiAsset)

public:
	SquareColorUi(Library::Game& aGame, const std::string& aAssetPath);
	~SquareColorUi();

public:
	SquareColorUi() = delete;
	SquareColorUi(const SquareColorUi& aRhs) = delete;
	SquareColorUi& operator = (const SquareColorUi& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Update() override;

public:
	void Set_u_transform(const eps::math::mat4& a_u_transform);
	const eps::math::mat4& Get_u_transform() const;

	void Set_u_color(const eps::math::vec4& a_u_color);
	const eps::math::vec4& Get_u_color() const;

	void SetVertices(const std::vector<SquareColorVertex>& aVertices);
	const std::vector<SquareColorVertex>& GetVertices() const;

	bool IsNeedRestore() const;

private:
	virtual float& GetValueBySliderId(int aSliderId) override;

private:
	bool mIsRestoreNeed;
	eps::math::mat4 m_u_transform;
	eps::math::vec4 m_u_color;
	std::vector<SquareColorVertex> mVertices;
};
}

#endif
