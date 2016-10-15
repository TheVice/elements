
#include "SettingsReader.h"
#include "assets/assets_storage.h"
#include "ReaderHelpers.h"
#include <cstring>

bool SettingsReader::read(const pugi::xml_document& doc)
{
	mVertices.clear();
	mIndices.clear();
	mMatrixMvp = glm::mat4();
	mMatrixNormal = glm::mat3();
	mTexturePath = "";
	mIsEmpty = true;
	//
	const auto root_node = doc.child("program");

	if (root_node.empty())
	{
		return !mIsEmpty;
	}

	const auto vertices_node = root_node.child("vertices");

	if (vertices_node.empty())
	{
		return !mIsEmpty;
	}

	const auto indices_node = root_node.child("indices");

	if (indices_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_mvp_node = root_node.child("matrix_mvp");

	if (m_mvp_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_normal_node = root_node.child("matrix_normal");

	if (m_normal_node.empty())
	{
		return !mIsEmpty;
	}

	const auto texture_node = root_node.child("texture");

	if (texture_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& vertex : vertices_node)
	{
		if (std::strcmp(vertex.name(), "vertex"))
		{
			continue;
		}

		const auto pos_node = vertex.child("pos");

		if (pos_node.empty())
		{
			return !mIsEmpty;
		}

		const auto normal_node = vertex.child("normal");

		if (normal_node.empty())
		{
			return !mIsEmpty;
		}

		const auto tangent_node = vertex.child("tangent");

		if (tangent_node.empty())
		{
			return !mIsEmpty;
		}

		const auto uv_node = vertex.child("uv");

		if (uv_node.empty())
		{
			return !mIsEmpty;
		}

		auto vertex_pos = glm::vec3();

		if (!Library::ReaderHelpers::read_glm_vec3(pos_node, vertex_pos))
		{
			return !mIsEmpty;
		}

		auto vertex_normal = glm::vec3();

		if (!Library::ReaderHelpers::read_glm_vec3(normal_node, vertex_normal))
		{
			return !mIsEmpty;
		}

		auto vertex_tangent = glm::vec3();

		if (!Library::ReaderHelpers::read_glm_vec3(tangent_node, vertex_tangent))
		{
			return !mIsEmpty;
		}

		auto vertex_uv = glm::vec2();

		if (!Library::ReaderHelpers::read_glm_vec2(uv_node, vertex_uv))
		{
			return !mIsEmpty;
		}

		const auto vertex_data = VertexStructure(vertex_pos, vertex_normal, vertex_tangent, vertex_uv);
		mVertices.push_back(vertex_data);
	}

	if (!Library::ReaderHelpers::read_indices(indices_node, mIndices))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat4(m_mvp_node, mMatrixMvp))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat3(m_normal_node, mMatrixNormal))
	{
		return !mIsEmpty;
	}

	const auto texture_path = texture_node.attribute("path");

	if (texture_path.empty())
	{
		return !mIsEmpty;
	}

	mTexturePath = texture_path.as_string();
	//
	mIsEmpty = false;
	return !mIsEmpty;
}
