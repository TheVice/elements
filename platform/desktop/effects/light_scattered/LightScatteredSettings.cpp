
#include "LightScatteredSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_occluding.clear();	\
	u_exposure = 0.0f;	\
	u_decay = 0.0f;	\
	u_density = 0.0f;	\
	u_weight = 0.0f;	\
	u_light_position = eps::math::vec2();	\
	\
	mIsEmpty = true;

bool LightScatteredSettings::read(const pugi::xml_document& doc)
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

	const auto u_occluding_node = settings_node.child("u_occluding");

	if (u_occluding_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_exposure_node = settings_node.child("u_exposure");

	if (u_exposure_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_decay_node = settings_node.child("u_decay");

	if (u_decay_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_density_node = settings_node.child("u_density");

	if (u_density_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_weight_node = settings_node.child("u_weight");

	if (u_weight_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_light_position_node = settings_node.child("u_light_position");

	if (u_light_position_node.empty())
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

		const auto vertex = LightScatteredVertex(a_vertex_xy, a_vertex_uv);
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

	if (!Library::ReaderHelpers::read_std_string(u_occluding_node, u_occluding))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_exposure_node, u_exposure))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_decay_node, u_decay))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_density_node, u_density))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_weight_node, u_weight))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_light_position_node, u_light_position))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
