#ifndef _ROSE_H_
#define _ROSE_H_

#include "drawableObject.h"

namespace Rendering
{
namespace Compass
{

class rose : public drawableObject
{

public:

	explicit rose();

	virtual bool initialize(const eps::math::uvec2 & size) override;

	eps::math::vec2& position();
	eps::math::vec2& radius();

public:

	static const eps::math::vec2& defaultRadius();

private:

	eps::math::vec2 mPosition;
	eps::math::vec2 mRadius;
	eps::math::vec4 mInnerColor;
	eps::math::vec4 mOuterColor;

private:

	static const eps::math::vec2 sDefaultRadius;
	static const eps::math::vec4 sDefaultInnerColor;
	static const eps::math::vec4 sDefaultOuterColor;
};

}
}

#endif
