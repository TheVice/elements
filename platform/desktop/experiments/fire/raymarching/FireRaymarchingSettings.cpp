
#include "FireRaymarchingSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_noise.clear();	\
	u_dt = 0.0f;	\
	u_intensity = 0.0f;	\
	u_covering = 0.0f;	\
	u_texel = eps::math::vec2();	\
	u_color_hot = eps::math::vec3();	\
	u_color_cold = eps::math::vec3();	\
	\
	mIsEmpty = true;

bool FireRaymarchingSettings::read(const pugi::xml_document& doc)
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

	const auto u_noise_node = settings_node.child("u_noise");

	if (u_noise_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_dt_node = settings_node.child("u_dt");

	if (u_dt_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_intensity_node = settings_node.child("u_intensity");

	if (u_intensity_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_covering_node = settings_node.child("u_covering");

	if (u_covering_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_texel_node = settings_node.child("u_texel");

	if (u_texel_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_color_hot_node = settings_node.child("u_color_hot");

	if (u_color_hot_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_color_cold_node = settings_node.child("u_color_cold");

	if (u_color_cold_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& subNode : vertices_node)
	{
		if (std::strcmp(subNode.name(), "vertex"))
		{
			continue;
		}

		const auto a_vertex_xy_node = subNode.child("a_vertex_xy");

		if (a_vertex_xy_node.empty())
		{
			return !mIsEmpty;
		}

		const auto a_vertex_uv_node = subNode.child("a_vertex_uv");

		if (a_vertex_uv_node.empty())
		{
			return !mIsEmpty;
		}

		auto a_vertex_xy = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_xy_node, a_vertex_xy))
		{
			return !mIsEmpty;
		}

		auto a_vertex_uv = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_uv_node, a_vertex_uv))
		{
			return !mIsEmpty;
		}

		const auto vertex = FireRaymarchingVertex(a_vertex_xy, a_vertex_uv);
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

	if (!Library::ReaderHelpers::read_std_string(u_noise_node, u_noise))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_dt_node, u_dt))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_intensity_node, u_intensity))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_covering_node, u_covering))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_texel_node, u_texel))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_color_hot_node, u_color_hot))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_color_cold_node, u_color_cold))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
