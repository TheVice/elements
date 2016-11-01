#ifndef _DRAWABLE_OBJECT_H_
#define _DRAWABLE_OBJECT_H_

#include <elements/math/types.h>
#include <elements/rendering/core/program.h>
#include <elements/rendering/primitives/square.h>

#include <string>
#include <vector>
#include <utility>

namespace Rendering
{
namespace Compass
{

class drawableObject
{

public:

	explicit drawableObject();

	virtual bool initialize(const eps::math::uvec2 & size);
	virtual void draw(float dt);

protected:
	std::string shader_path_;
	std::vector<std::pair<eps::math::vec4, eps::math::vec4>> vertices_;
	eps::math::mat4 mDescartesMatrix;
	eps::math::mat4 mWorldMatrix;
	bool isArrow;

private:

	eps::rendering::program program_face_;
	eps::rendering::primitive::square square_;
};

}
}

#endif
