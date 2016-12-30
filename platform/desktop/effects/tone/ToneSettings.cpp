
#include "ToneSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_source_1.clear();	\
	u_source_2.clear();	\
	u_exposure = 0.0f;	\
	u_gamma = 0.0f;	\
	\
	mIsEmpty = true;

bool ToneSettings::read(const pugi::xml_document& doc)
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

	const auto u_source_1_node = settings_node.child("u_source_1");

	if (u_source_1_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_source_2_node = settings_node.child("u_source_2");

	if (u_source_2_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_exposure_node = settings_node.child("u_exposure");

	if (u_exposure_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_gamma_node = settings_node.child("u_gamma");

	if (u_gamma_node.empty())
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

		const auto vertex = ToneVertex(a_vertex_xy, a_vertex_uv);
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

	if (!Library::ReaderHelpers::read_std_string(u_source_1_node, u_source_1))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_source_2_node, u_source_2))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_exposure_node, u_exposure))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_gamma_node, u_gamma))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
