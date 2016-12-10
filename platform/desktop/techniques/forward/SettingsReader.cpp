
#include "SettingsReader.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <glm/gtc/constants.hpp>
#include <cstring>


namespace Rendering
{

void SettingsReader::clear()
{
	mVertices.clear();
	mIndices.clear();
	//
	mMatrixMvp = glm::mat4();
	mMatrixModelView = glm::mat4();
	mMatrixView = glm::mat4();
	mMatrixNormal = glm::mat3();
	//
	mLightPos = glm::vec3();
	mCameraPos = glm::vec3();
	//
	mMapDiffuse.clear();
	mMapSpecular.clear();
	mMapNormal.clear();
	//
	mLightIntensity = glm::vec3();
	mLightRange = glm::zero<float>();
	//
	mIsEmpty = true;
}

bool SettingsReader::read(const pugi::xml_document& doc)
{
	clear();
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

	const auto m_mvp_node = root_node.child("u_matrix_mvp");

	if (m_mvp_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_matrix_model_view_node = root_node.child("u_matrix_model_view");

	if (m_matrix_model_view_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_matrix_view_node = root_node.child("u_matrix_view");

	if (m_matrix_view_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_normal_node = root_node.child("u_matrix_normal");

	if (m_normal_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_light_pos_node = root_node.child("light_pos");

	if (m_light_pos_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_camera_pos_node = root_node.child("camera_pos");

	if (m_camera_pos_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_map_diffuse_node = root_node.child("map_diffuse");

	if (m_map_diffuse_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_map_specular_node = root_node.child("map_specular");

	if (m_map_specular_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_map_normal_node = root_node.child("map_normal");

	if (m_map_normal_node.empty())
	{
		return !mIsEmpty;
	}

	const auto m_light_intensity = root_node.child("light_intensity");

	if (m_light_intensity.empty())
	{
		return !mIsEmpty;
	}

	const auto m_light_range_node = root_node.child("light_range");

	if (m_light_range_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& vertex : vertices_node)
	{
		if (std::strcmp(vertex.name(), "vertex"))
		{
			continue;
		}

		const auto pos_node = vertex.child("position");

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

		if (!Library::ReaderHelpers::read_glm_vec(pos_node, vertex_pos))
		{
			return !mIsEmpty;
		}

		auto vertex_normal = glm::vec3();

		if (!Library::ReaderHelpers::read_glm_vec(normal_node, vertex_normal))
		{
			return !mIsEmpty;
		}

		auto vertex_tangent = glm::vec3();

		if (!Library::ReaderHelpers::read_glm_vec(tangent_node, vertex_tangent))
		{
			return !mIsEmpty;
		}

		auto vertex_uv = glm::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(uv_node, vertex_uv))
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

	if (!Library::ReaderHelpers::read_glm_mat(m_mvp_node, mMatrixMvp))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat(m_matrix_model_view_node, mMatrixModelView))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat(m_matrix_view_node, mMatrixView))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat(m_normal_node, mMatrixNormal))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(m_light_pos_node, mLightPos))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(m_camera_pos_node, mCameraPos))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(m_map_diffuse_node, mMapDiffuse))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(m_map_specular_node, mMapSpecular))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_std_string(m_map_normal_node, mMapNormal))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_vec(m_light_intensity, mLightIntensity))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(m_light_range_node, mLightRange))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
