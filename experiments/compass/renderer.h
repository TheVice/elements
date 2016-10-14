#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "arrow.h"
#include "rose.h"

#include <elements/math/types.h>
#include <elements/utils/std/pointer.h>
#include <elements/rendering/passes/pass_composition.h>

namespace Rendering
{
namespace Compass
{

class renderer
{
public:

	renderer();

	bool initialize();
	bool construct(const eps::math::uvec2 & size);

	void render(float dt);

	void set_rotation(float omega);

private:

	eps::rendering::pass_composition passes_;
	eps::utils::unique<arrow> arrow_;
	eps::utils::unique<rose> rose_;
};

}
}

#endif
