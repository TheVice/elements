
#include "ModelEffect.h"
#include <elements/rendering/core/program.h>
#include <elements/rendering/state/state_macro.h>

namespace Rendering
{

ModelEffect::ModelEffect(const std::vector<ModelVertex>& vertices,
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

void ModelEffect::construct(const std::vector<ModelVertex>& vertices)
{
	assert(!vertices.empty());
	// Update vertex buffer object
	texture_vertices_.allocate(&vertices.front(), vertices.size(), sizeof(vertices.front()));
}

void ModelEffect::render(eps::rendering::program& program, const std::array<short, 4>& a_position,
						 short index_count)
{
	EPS_STATE_VERTICES(texture_vertices_.get_product());
	EPS_STATE_INDICES(texture_indices_.get_product());
	//
	program.attribute_array(std::get<0>(a_position), offsetof(ModelVertex, a_vertex_pos),
							eps::math::vec3().length(), sizeof(ModelVertex));
	program.attribute_array_enable(std::get<0>(a_position));
	program.attribute_array(std::get<1>(a_position), offsetof(ModelVertex, a_vertex_normal),
							eps::math::vec3().length(), sizeof(ModelVertex));
	program.attribute_array_enable(std::get<1>(a_position));
	program.attribute_array(std::get<2>(a_position), offsetof(ModelVertex, a_vertex_tangent),
							eps::math::vec3().length(), sizeof(ModelVertex));
	program.attribute_array_enable(std::get<2>(a_position));
	program.attribute_array(std::get<3>(a_position), offsetof(ModelVertex, a_vertex_uv),
							eps::math::vec2().length(), sizeof(ModelVertex));
	program.attribute_array_enable(std::get<3>(a_position));
	//
	glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_BYTE, 0);
}

}
