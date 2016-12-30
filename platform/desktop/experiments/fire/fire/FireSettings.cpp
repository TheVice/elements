
#include "FireSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_fire.clear();	\
	u_background.clear();	\
	u_texel = eps::math::vec2();	\
	\
	mIsEmpty = true;

bool FireSettings::read(const pugi::xml_document& doc)
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

	const auto u_fire_node = settings_node.child("u_fire");

	if (u_fire_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_background_node = settings_node.child("u_background");

	if (u_background_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_texel_node = settings_node.child("u_texel");

	if (u_texel_node.empty())
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

		const auto vertex = FireVertex(a_vertex_xy, a_vertex_uv);
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

	if (!Library::ReaderHelpers::read_std_string(u_fire_node, u_fire))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_background_node, u_background))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_texel_node, u_texel))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
