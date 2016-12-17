
#include "GeometrySettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_matrix_mvp = eps::math::mat4();	\
	u_matrix_model_view = eps::math::mat4();	\
	u_map_normal.clear();	\
	u_has_map_normal = true;	\
	\
	mIsEmpty = true;

bool GeometrySettings::read(const pugi::xml_document& doc)
{
	CLEAR()
	const auto settings_node = doc.child("settings");

	if (settings_node.empty())
	{
		return !mIsEmpty;
	}

	const auto vertices_node = settings_node.child("vertices");

	if (vertices_node.empty())
	{
		return !mIsEmpty;
	}

	const auto indices_node = settings_node.child("indices");

	if (indices_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_matrix_mvp_node = settings_node.child("u_matrix_mvp");

	if (u_matrix_mvp_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_matrix_model_view_node = settings_node.child("u_matrix_model_view");

	if (u_matrix_model_view_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_map_normal_node = settings_node.child("u_map_normal");

	if (u_map_normal_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_has_map_normal_node = settings_node.child("u_has_map_normal");

	if (u_has_map_normal_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& subNode : vertices_node)
	{
		if (std::strcmp(subNode.name(), "vertex"))
		{
			continue;
		}

		const auto a_vertex_pos_node = subNode.child("a_vertex_pos");

		if (a_vertex_pos_node.empty())
		{
			return !mIsEmpty;
		}

		const auto a_vertex_normal_node = subNode.child("a_vertex_normal");

		if (a_vertex_normal_node.empty())
		{
			return !mIsEmpty;
		}

		const auto a_vertex_tangent_node = subNode.child("a_vertex_tangent");

		if (a_vertex_tangent_node.empty())
		{
			return !mIsEmpty;
		}

		const auto a_vertex_uv_node = subNode.child("a_vertex_uv");

		if (a_vertex_uv_node.empty())
		{
			return !mIsEmpty;
		}

		auto a_vertex_pos = eps::math::vec3();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_pos_node, a_vertex_pos))
		{
			return !mIsEmpty;
		}

		auto a_vertex_normal = eps::math::vec3();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_normal_node, a_vertex_normal))
		{
			return !mIsEmpty;
		}

		auto a_vertex_tangent = eps::math::vec3();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_tangent_node, a_vertex_tangent))
		{
			return !mIsEmpty;
		}

		auto a_vertex_uv = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_uv_node, a_vertex_uv))
		{
			return !mIsEmpty;
		}

		const auto vertex = GeometryVertex(a_vertex_pos, a_vertex_normal, a_vertex_tangent, a_vertex_uv);
		mVertices.push_back(vertex);
	}

	if (mVertices.empty())
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_indices(indices_node, mIndices))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat(u_matrix_mvp_node, u_matrix_mvp))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat(u_matrix_model_view_node, u_matrix_model_view))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_map_normal_node, u_map_normal))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_bool(u_has_map_normal_node, u_has_map_normal))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
