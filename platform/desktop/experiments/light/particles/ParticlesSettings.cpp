
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
	u_velocities.clear();	\
	u_background.clear();	\
	u_texel = eps::math::vec2();	\
	u_size = 0.0f;	\
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

	const auto u_velocities_node = settings_node.child("u_velocities");

	if (u_velocities_node.empty())
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

	const auto u_size_node = settings_node.child("u_size");

	if (u_size_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& subNode : vertices_node)
	{
		if (std::strcmp(subNode.name(), "vertex"))
		{
			continue;
		}

		const auto a_product_uv_node = subNode.child("a_product_uv");

		if (a_product_uv_node.empty())
		{
			return !mIsEmpty;
		}

		auto a_product_uv = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_product_uv_node, a_product_uv))
		{
			return !mIsEmpty;
		}

		const auto vertex = ParticlesVertex(a_product_uv);
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

	if (!Library::ReaderHelpers::read_std_string(u_background_node, u_background))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(u_texel_node, u_texel))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_size_node, u_size))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
