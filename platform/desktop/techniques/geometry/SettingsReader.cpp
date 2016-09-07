
#include "SettingsReader.h"
#include "assets/assets_storage.h"
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

		const auto a_vertex_pos = glm::vec3(
									  pos_node.attribute("x").as_float(),
									  pos_node.attribute("y").as_float(),
									  pos_node.attribute("z").as_float());
		const auto a_vertex_normal = glm::vec3(
										 normal_node.attribute("x").as_float(),
										 normal_node.attribute("y").as_float(),
										 normal_node.attribute("z").as_float());
		const auto a_vertex_tangent = glm::vec3(
										  tangent_node.attribute("x").as_float(),
										  tangent_node.attribute("y").as_float(),
										  tangent_node.attribute("z").as_float());
		const auto a_vertex_uv = glm::vec2(
									 uv_node.attribute("u").as_float(),
									 uv_node.attribute("v").as_float());
		const auto vertex_data = VertexStructure(
									 a_vertex_pos, a_vertex_normal, a_vertex_tangent, a_vertex_uv);
		mVertices.push_back(vertex_data);
	}

	for (const auto& index : indices_node)
	{
		if (std::strcmp(index.name(), "index"))
		{
			continue;
		}

		const auto index_data = index.attribute("value").as_uint();
		mIndices.push_back(index_data);
	}

	mMatrixMvp = glm::mat4(
					 m_mvp_node.attribute("m00").as_float(),
					 m_mvp_node.attribute("m01").as_float(),
					 m_mvp_node.attribute("m02").as_float(),
					 m_mvp_node.attribute("m03").as_float(),
					 //
					 m_mvp_node.attribute("m10").as_float(),
					 m_mvp_node.attribute("m11").as_float(),
					 m_mvp_node.attribute("m12").as_float(),
					 m_mvp_node.attribute("m13").as_float(),
					 //
					 m_mvp_node.attribute("m20").as_float(),
					 m_mvp_node.attribute("m21").as_float(),
					 m_mvp_node.attribute("m22").as_float(),
					 m_mvp_node.attribute("m23").as_float(),
					 //
					 m_mvp_node.attribute("m30").as_float(),
					 m_mvp_node.attribute("m31").as_float(),
					 m_mvp_node.attribute("m32").as_float(),
					 m_mvp_node.attribute("m33").as_float());
	//
	mMatrixNormal = glm::mat3(
						m_normal_node.attribute("m00").as_float(),
						m_normal_node.attribute("m01").as_float(),
						m_normal_node.attribute("m02").as_float(),
						//
						m_normal_node.attribute("m10").as_float(),
						m_normal_node.attribute("m11").as_float(),
						m_normal_node.attribute("m12").as_float(),
						//
						m_normal_node.attribute("m20").as_float(),
						m_normal_node.attribute("m21").as_float(),
						m_normal_node.attribute("m22").as_float());
	//
	mTexturePath = texture_node.attribute("path").as_string();
	//
	mIsEmpty = false;
	return !mIsEmpty;
}
