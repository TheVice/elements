
#include "rose.h"

namespace Rendering
{
namespace Compass
{

rose::rose()
	: drawableObject()
	, mPosition()
	, mRadius(sDefaultRadius)
	, mInnerColor(sDefaultInnerColor)
	, mOuterColor(sDefaultOuterColor)
{
}

bool rose::initialize(const eps::math::uvec2 & size)
{
	shader_path_ = "assets/shaders/primitives/circle_color.prog";
	vertices_.clear();
	//
	vertices_.push_back(std::make_pair(
		eps::math::vec4(mPosition.x - mRadius.y, mPosition.y - mRadius.y, mPosition.x + mRadius.y, mPosition.y + mRadius.y), mOuterColor
	));
	//
	vertices_.push_back(std::make_pair(
		eps::math::vec4(mPosition.x - mRadius.x, mPosition.y - mRadius.x, mPosition.x + mRadius.x, mPosition.y + mRadius.x), mInnerColor
	));
	//
	return drawableObject::initialize(size);
}

eps::math::vec2& rose::position()
{
	return mPosition;
}

eps::math::vec2& rose::radius()
{
	return mRadius;
}

const eps::math::vec2& rose::defaultRadius()
{
	return sDefaultRadius;
}

const eps::math::vec2 rose::sDefaultRadius(23.0f, 48.0f);
const eps::math::vec4 rose::sDefaultInnerColor(0.34902f, 0.34902f, 0.34902f, 1.0f);
const eps::math::vec4 rose::sDefaultOuterColor(0.13333f, 0.13333f, 0.13333f, 1.0f);

}
}
