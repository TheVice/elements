
#include "SettingsReader.h"
#include "assets/assets_storage.h"
#include <cstring>

bool SettingsReader::read(const pugi::xml_document& doc)
{
	mVertices.clear();
	mIndices.clear();
	mTransform = glm::mat4();
	mSize = 0.0f;
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

	const auto transform_node = root_node.child("transform");

	if (transform_node.empty())
	{
		return !mIsEmpty;
	}

	const auto size_node = root_node.child("size");

	if (size_node.empty())
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

		const auto a_vertex_pos = glm::vec2(
									  pos_node.attribute("x").as_float(),
									  pos_node.attribute("y").as_float());
		const auto vertex_data = VertexStructure(a_vertex_pos);
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

	mTransform = glm::mat4(
					 transform_node.attribute("m00").as_float(),
					 transform_node.attribute("m01").as_float(),
					 transform_node.attribute("m02").as_float(),
					 transform_node.attribute("m03").as_float(),
					 //
					 transform_node.attribute("m10").as_float(),
					 transform_node.attribute("m11").as_float(),
					 transform_node.attribute("m12").as_float(),
					 transform_node.attribute("m13").as_float(),
					 //
					 transform_node.attribute("m20").as_float(),
					 transform_node.attribute("m21").as_float(),
					 transform_node.attribute("m22").as_float(),
					 transform_node.attribute("m23").as_float(),
					 //
					 transform_node.attribute("m30").as_float(),
					 transform_node.attribute("m31").as_float(),
					 transform_node.attribute("m32").as_float(),
					 transform_node.attribute("m33").as_float());
	//
	mSize = size_node.attribute("value").as_float();
	//
	mIsEmpty = false;
	return !mIsEmpty;
}
