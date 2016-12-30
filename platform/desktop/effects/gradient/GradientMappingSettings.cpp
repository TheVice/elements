
#include "GradientMappingSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_source.clear();	\
	u_color_1 = eps::math::vec3();	\
	u_color_2 = eps::math::vec3();	\
	\
	mIsEmpty = true;

bool GradientMappingSettings::read(const pugi::xml_document& doc)
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

	const auto u_source_node = settings_node.child("u_source");

	if (u_source_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_color_1_node = settings_node.child("u_color_1");

	if (u_color_1_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_color_2_node = settings_node.child("u_color_2");

	if (u_color_2_node.empty())
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

		const auto vertex = GradientMappingVertex(a_vertex_xy, a_vertex_uv);
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

	if (!Library::ReaderHelpers::read_std_string(u_source_node, u_source))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_color_1_node, u_color_1))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_color_2_node, u_color_2))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
