
#include "PositionsProcessSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_positions.clear();	\
	u_velocities.clear();	\
	u_dt = 0.0f;	\
	\
	mIsEmpty = true;

bool PositionsProcessSettings::read(const pugi::xml_document& doc)
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

	const auto u_positions_node = settings_node.child("u_positions");

	if (u_positions_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_velocities_node = settings_node.child("u_velocities");

	if (u_velocities_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_dt_node = settings_node.child("u_dt");

	if (u_dt_node.empty())
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

		auto a_vertex_xy = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_vertex_xy_node, a_vertex_xy))
		{
			return !mIsEmpty;
		}

		const auto vertex = PositionsProcessVertex(a_vertex_xy);
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

	if (!Library::ReaderHelpers::read_std_string(u_positions_node, u_positions))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_velocities_node, u_velocities))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_dt_node, u_dt))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
