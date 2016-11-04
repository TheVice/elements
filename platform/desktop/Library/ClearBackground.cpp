
#include "ClearBackground.h"

namespace Library
{
RTTI_DEFINITIONS(ClearBackground)

ClearBackground::ClearBackground(Game& aGame) :
	DrawableGameComponent(aGame),
	mBackgroundColor(sBackgroundColor)
{
}

ClearBackground::ClearBackground(Game& aGame, const eps::math::vec4& aBackgroundColor) :
	DrawableGameComponent(aGame),
	mBackgroundColor(aBackgroundColor)
{
}

ClearBackground::~ClearBackground()
{
}

void ClearBackground::Draw()
{
	glClearBufferfv(GL_COLOR, 0, &mBackgroundColor[0]);
}

void ClearBackground::SetColor(const eps::math::vec4& aBackgroundColor)
{
	mBackgroundColor = aBackgroundColor;
}

const eps::math::vec4& ClearBackground::GetColor() const
{
	return mBackgroundColor;
}

const eps::math::vec4 ClearBackground::sBackgroundColor = { 0.392f, 0.584f, 0.929f, 1.0f };

}
