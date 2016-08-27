
#include "SettingsReader.h"
#include "assets/assets_storage.h"
#include <cstring>

bool SettingsReader::read(const pugi::xml_document& doc)
{
	mIsEmpty = true;
	auto root_node = doc.child("program");

	if (root_node.empty())
	{
		return false;
	}

	auto vertices_node = root_node.child("vertices");

	if (vertices_node.empty())
	{
		return false;
	}

	auto indices_node = root_node.child("indices");

	if (indices_node.empty())
	{
		return false;
	}

	auto m_mvp_node = root_node.child("matrix_mvp");

	if (m_mvp_node.empty())
	{
		return false;
	}

	auto m_normal_node = root_node.child("matrix_normal");

	if (m_normal_node.empty())
	{
		return false;
	}

	auto texture_node = root_node.child("texture");

	if (texture_node.empty())
	{
		return false;
	}

	for (auto vertex = vertices_node.begin(); vertex != vertices_node.end(); ++vertex)
	{
		if (std::strcmp(vertex->name(), "vertex"))
		{
			continue;
		}

		auto pos_node = vertex->child("pos");

		if (pos_node.empty())
		{
			return false;
		}

		auto normal_node = vertex->child("normal");

		if (normal_node.empty())
		{
			return false;
		}

		auto tangent_node = vertex->child("tangent");

		if (tangent_node.empty())
		{
			return false;
		}

		auto uv_node = vertex->child("uv");

		if (uv_node.empty())
		{
			return false;
		}

		auto a_vertex_pos = glm::vec3(
								pos_node.attribute("x").as_float(),
								pos_node.attribute("y").as_float(),
								pos_node.attribute("z").as_float());
		auto a_vertex_normal = glm::vec3(
								   normal_node.attribute("x").as_float(),
								   normal_node.attribute("y").as_float(),
								   normal_node.attribute("z").as_float());
		auto a_vertex_tangent = glm::vec3(
									tangent_node.attribute("x").as_float(),
									tangent_node.attribute("y").as_float(),
									tangent_node.attribute("z").as_float());
		auto a_vertex_uv = glm::vec2(
							   uv_node.attribute("u").as_float(),
							   uv_node.attribute("v").as_float());
		auto vertex_data = VertexStructure(
							   a_vertex_pos, a_vertex_normal, a_vertex_tangent, a_vertex_uv);
		mVertices.push_back(vertex_data);
	}

	for (auto index = indices_node.begin(); index != indices_node.end(); ++index)
	{
		if (std::strcmp(index->name(), "index"))
		{
			continue;
		}

		auto index_data = index->attribute("value").as_uint();
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
	return true;
}

bool load_data(const char* demo_data_asset, SettingsReader& demo_data)
{
	auto data = eps::assets_storage::instance().read<SettingsReader>(demo_data_asset);

	if (!data || data.value().mIsEmpty)
	{
		return false;
	}

	demo_data.mVertices = data.value().mVertices;
	demo_data.mIndices = data.value().mIndices;
	demo_data.mMatrixMvp = data.value().mMatrixMvp;
	demo_data.mMatrixNormal = data.value().mMatrixNormal;
	demo_data.mTexturePath = data.value().mTexturePath;
	//
	return true;
}
