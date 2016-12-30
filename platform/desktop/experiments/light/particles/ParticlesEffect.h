#ifndef _PARTICLES_EFFECT_H_
#define _PARTICLES_EFFECT_H_

#include "ParticlesVertex.h"
#include <elements/rendering/core/buffer.h>
#include <vector>


namespace eps
{
namespace rendering
{
class program;
}
}

namespace Rendering
{
class ParticlesEffect
{
public:
	explicit ParticlesEffect(const std::vector<ParticlesVertex>& vertices,
							 const std::vector<GLubyte>& indices,
							 eps::rendering::buffer_usage usage = eps::rendering::buffer_usage::STATIC_DRAW);

	void construct(const std::vector<ParticlesVertex>& vertices);
	void render(eps::rendering::program& program, short a_position, short index_count);

private:
	eps::rendering::vertices texture_vertices_;
	eps::rendering::indices texture_indices_;
};
}

#endif

