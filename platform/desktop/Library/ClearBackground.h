#ifndef _CLEAR_BACKGROUND_H_
#define _CLEAR_BACKGROUND_H_

#include <DrawableGameComponent.h>
#include <elements/math/types.h>
#include <elements/rendering/core/opengl.h>

namespace Library
{
class ClearBackground : public DrawableGameComponent
{
	RTTI_DECLARATIONS(ClearBackground, DrawableGameComponent)

public:
	ClearBackground(Game& aGame);
	ClearBackground(Game& aGame, const eps::math::vec4& aBackgroundColor);
	~ClearBackground();

public:
	ClearBackground() = delete;
	ClearBackground(const ClearBackground& aRhs) = delete;
	ClearBackground& operator = (const ClearBackground& aRhs) = delete;

public:
	virtual void Draw() override;

	void SetColor(const eps::math::vec4& aBackgroundColor);
	const eps::math::vec4& GetColor() const;

private:
	eps::math::vec4 mBackgroundColor;

public:
	static const eps::math::vec4 sBackgroundColor;
};
}

#endif
