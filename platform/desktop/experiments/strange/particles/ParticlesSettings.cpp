
#include "ParticlesSettings.h"
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
	\
	mIsEmpty = true;

bool ParticlesSettings::read(const pugi::xml_document& doc)
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

	for (const auto& subNode : vertices_node)
	{
		if (std::strcmp(subNode.name(), "vertex"))
		{
			continue;
		}

		const auto a_positions_uv_node = subNode.child("a_positions_uv");

		if (a_positions_uv_node.empty())
		{
			return !mIsEmpty;
		}

		auto a_positions_uv = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_positions_uv_node, a_positions_uv))
		{
			return !mIsEmpty;
		}

		const auto vertex = ParticlesVertex(a_positions_uv);
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

	mIsEmpty = false;
	return !mIsEmpty;
}

}
