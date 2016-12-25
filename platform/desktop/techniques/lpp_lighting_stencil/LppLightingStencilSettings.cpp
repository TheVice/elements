
#include "LppLightingStencilSettings.h"
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
	\
	mIsEmpty = true;

bool LppLightingStencilSettings::read(const pugi::xml_document& doc)
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

		const auto vertex = LppLightingStencilVertex(a_vertex_pos);
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

	mIsEmpty = false;
	return !mIsEmpty;
}

}
