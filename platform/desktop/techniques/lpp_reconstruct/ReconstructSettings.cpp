
#include "ReconstructSettings.h"
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
	u_map_light.clear();	\
	u_map_diffuse.clear();	\
	u_map_specular.clear();	\
	u_has_map_diffuse = true;	\
	u_has_map_specular = true;	\
	u_color_diffuse = eps::math::vec3();	\
	u_color_specular = eps::math::vec3();	\
	\
	mIsEmpty = true;

bool ReconstructSettings::read(const pugi::xml_document& doc)
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

	const auto u_map_light_node = settings_node.child("u_map_light");

	if (u_map_light_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_map_diffuse_node = settings_node.child("u_map_diffuse");

	if (u_map_diffuse_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_map_specular_node = settings_node.child("u_map_specular");

	if (u_map_specular_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_has_map_diffuse_node = settings_node.child("u_has_map_diffuse");

	if (u_has_map_diffuse_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_has_map_specular_node = settings_node.child("u_has_map_specular");

	if (u_has_map_specular_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_color_diffuse_node = settings_node.child("u_color_diffuse");

	if (u_color_diffuse_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_color_specular_node = settings_node.child("u_color_specular");

	if (u_color_specular_node.empty())
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

		auto a_vertex_uv = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_uv_node, a_vertex_uv))
		{
			return !mIsEmpty;
		}

		const auto vertex = ReconstructVertex(a_vertex_pos, a_vertex_uv);
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

	if (!Library::ReaderHelpers::read_std_string(u_map_light_node, u_map_light))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_map_diffuse_node, u_map_diffuse))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_map_specular_node, u_map_specular))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_bool(u_has_map_diffuse_node, u_has_map_diffuse))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_bool(u_has_map_specular_node, u_has_map_specular))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_color_diffuse_node, u_color_diffuse))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_color_specular_node, u_color_specular))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
