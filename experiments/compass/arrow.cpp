
#include "arrow.h"
#include <elements/math/transform.h>

namespace Rendering
{
namespace Compass
{

arrow::arrow()
	: drawableObject()
	, mPosition()
	, mSize(sDefaultSize)
	, mColorNorth(sDefaultColorNorth)
	, mColorSouth(sDefaultColorSouth)
{
}

bool arrow::initialize(const eps::math::uvec2 & size)
{
	shader_path_ = "shaders/primitives/square_color.prog";
	vertices_.clear();
	//
	vertices_.push_back(std::make_pair(
		eps::math::vec4(mPosition.x, mPosition.y + mSize.y / 2, mPosition.x + mSize.x, mPosition.y + mSize.y), mColorNorth
	));
	//
	vertices_.push_back(std::make_pair(
		eps::math::vec4(mPosition.x, mPosition.y + mSize.y / 2, mPosition.x + mSize.x, mPosition.y), mColorSouth
	));
	//
	return drawableObject::initialize(size);
}

eps::math::vec2& arrow::position()
{
	return mPosition;
}

eps::math::vec2& arrow::size()
{
	return mSize;
}

void arrow::rotate(float angle)
{
	// TODO: Proper rotation only if object located in center of window
	mWorldMatrix = eps::math::rotate(angle, eps::math::vec3(0.0f, 0.0f, 1.0f)) * mDescartesMatrix;
}

const eps::math::vec2& arrow::defaultSize()
{
	return sDefaultSize;
}

const eps::math::vec2 arrow::sDefaultSize(24.0f, 68.0f);
const eps::math::vec4 arrow::sDefaultColorNorth(0.75686f, 0.15294f, 0.17647f, 1.0f);
const eps::math::vec4 arrow::sDefaultColorSouth(0.8f, 0.8f, 0.8f, 1.0f);

}
}
