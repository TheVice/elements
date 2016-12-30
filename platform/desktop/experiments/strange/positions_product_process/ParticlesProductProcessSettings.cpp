
#include "ParticlesProductProcessSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_attractor_a = 0.0f;	\
	u_attractor_b = 0.0f;	\
	u_attractor_c = 0.0f;	\
	u_attractor_d = 0.0f;	\
	\
	mIsEmpty = true;

bool ParticlesProductProcessSettings::read(const pugi::xml_document& doc)
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

	const auto u_attractor_a_node = settings_node.child("u_attractor_a");

	if (u_attractor_a_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_attractor_b_node = settings_node.child("u_attractor_b");

	if (u_attractor_b_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_attractor_c_node = settings_node.child("u_attractor_c");

	if (u_attractor_c_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_attractor_d_node = settings_node.child("u_attractor_d");

	if (u_attractor_d_node.empty())
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

		const auto vertex = ParticlesProductProcessVertex(a_vertex_xy);
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

	if (!Library::ReaderHelpers::read_float(u_attractor_a_node, u_attractor_a))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_attractor_b_node, u_attractor_b))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_attractor_c_node, u_attractor_c))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_attractor_d_node, u_attractor_d))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
