
#include "ProjectorSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAN()						\
	mVertices.clear();				\
	mIndices.clear();				\
	\
	u_matrix_mvp = glm::mat4();		\
	u_matrix_model = glm::mat4();	\
	u_matrix_pvp = glm::mat4();		\
	u_map_projective.clear();		\
	\
	mIsEmpty = true;

bool ProjectorSettings::read(const pugi::xml_document& doc)
{
	CLEAN()
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

	const auto u_matrix_model_node = settings_node.child("u_matrix_model");

	if (u_matrix_model_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_matrix_pvp_node = settings_node.child("u_matrix_pvp");

	if (u_matrix_mvp_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_map_projective_node = settings_node.child("u_map_projective");

	if (u_map_projective_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& subNode : vertices_node)
	{
		if (std::strcmp(subNode.name(), "vertex"))
		{
			continue;
		}

		const auto position_node = subNode.child("position");

		if (position_node.empty())
		{
			return !mIsEmpty;
		}

		auto position = glm::vec3();

		if (!Library::ReaderHelpers::read_glm_vec(position_node, position))
		{
			return !mIsEmpty;
		}

		const auto vertex = VertexStructure(position);
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

	if (!Library::ReaderHelpers::read_glm_mat(u_matrix_model_node, u_matrix_model))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat(u_matrix_pvp_node, u_matrix_pvp))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(u_map_projective_node, u_map_projective))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
