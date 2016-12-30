
#include "VelocitiesResetEffect.h"
#include <elements/rendering/core/program.h>
#include <elements/rendering/state/state_macro.h>
#include <cassert>

namespace Rendering
{

VelocitiesResetEffect::VelocitiesResetEffect(const std::vector<VelocitiesResetVertex>& vertices,
		const std::vector<GLubyte>& indices,
		eps::rendering::buffer_usage usage)
	: texture_vertices_(usage)
	, texture_indices_(usage)
{
	assert(!vertices.empty());
	assert(!indices.empty());
	// Create the vertex buffer object
	texture_vertices_.allocate(&vertices.front(), vertices.size(), sizeof(vertices.front()));
	// Create the index buffer object
	texture_indices_.allocate(&indices.front(), indices.size(), sizeof(indices.front()));
}

void VelocitiesResetEffect::construct(const std::vector<VelocitiesResetVertex>& vertices)
{
	assert(!vertices.empty());
	// Update vertex buffer object
	texture_vertices_.allocate(&vertices.front(), vertices.size(), sizeof(vertices.front()));
}

void VelocitiesResetEffect::render(eps::rendering::program& program, short a_position, short index_count)
{
	EPS_STATE_VERTICES(texture_vertices_.get_product());
	EPS_STATE_INDICES(texture_indices_.get_product());
	//
	program.attribute_array(a_position, offsetof(VelocitiesResetVertex, a_vertex_xy), eps::math::vec2().length(),
							sizeof(VelocitiesResetVertex));
	program.attribute_array_enable(a_position);
	//
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_BYTE, 0);
}

}

