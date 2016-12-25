
#include "LppLightingSettings.h"
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
	u_camera_view_param = eps::math::vec2();	\
	u_camera_near = 0.0f;	\
	u_camera_far = 0.0f;	\
	u_map_geometry.clear();	\
	u_map_depth.clear();	\
	u_light_pos = eps::math::vec3();	\
	u_light_intensity = eps::math::vec3();	\
	u_light_inv_range_square = 0.0f;	\
	\
	mIsEmpty = true;

bool LppLightingSettings::read(const pugi::xml_document& doc)
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

	const auto u_camera_view_param_node = settings_node.child("u_camera_view_param");

	if (u_camera_view_param_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_camera_near_node = settings_node.child("u_camera_near");

	if (u_camera_near_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_camera_far_node = settings_node.child("u_camera_far");

	if (u_camera_far_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_map_geometry_node = settings_node.child("u_map_geometry");

	if (u_map_geometry_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_map_depth_node = settings_node.child("u_map_depth");

	if (u_map_depth_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_light_pos_node = settings_node.child("u_light_pos");

	if (u_light_pos_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_light_intensity_node = settings_node.child("u_light_intensity");

	if (u_light_intensity_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_light_inv_range_square_node = settings_node.child("u_light_inv_range_square");

	if (u_light_inv_range_square_node.empty())
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

		auto a_vertex_pos = eps::math::vec3();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_pos_node, a_vertex_pos))
		{
			return !mIsEmpty;
		}

		const auto vertex = LppLightingVertex(a_vertex_pos);
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

	if (!Library::ReaderHelpers::read_glm_vec(u_camera_view_param_node, u_camera_view_param))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_camera_near_node, u_camera_near))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_camera_far_node, u_camera_far))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_map_geometry_node, u_map_geometry))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_map_depth_node, u_map_depth))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_light_pos_node, u_light_pos))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_light_intensity_node, u_light_intensity))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_light_inv_range_square_node, u_light_inv_range_square))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
