#ifndef _ARROW_H_
#define _ARROW_H_

#include "drawableObject.h"

namespace Rendering
{
namespace Compass
{

class arrow : public drawableObject
{

public:

	explicit arrow();

	virtual bool initialize(const eps::math::uvec2 & size) override;

	eps::math::vec2& position();
	eps::math::vec2& size();
	void rotate(float angle);

public:

	static const eps::math::vec2& defaultSize();

private:

	eps::math::vec2 mPosition;
	eps::math::vec2 mSize;
	eps::math::vec4 mColorNorth;
	eps::math::vec4 mColorSouth;

private:

	static const eps::math::vec2 sDefaultSize;
	static const eps::math::vec4 sDefaultColorNorth;
	static const eps::math::vec4 sDefaultColorSouth;
};

}
}

#endif
