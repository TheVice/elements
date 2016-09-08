
#include "SettingsReader.h"
#include "assets/assets_storage.h"
#include "ReaderHelpers.h"
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

		auto vertex_pos = glm::vec2();

		if (!Library::ReaderHelpers::read_glm_vec2(pos_node, vertex_pos))
		{
			return !mIsEmpty;
		}

		const auto vertex_data = VertexStructure(vertex_pos);
		mVertices.push_back(vertex_data);
	}

	if (!Library::ReaderHelpers::read_indices(indices_node, mIndices))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_glm_mat4(transform_node, mTransform))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(size_node, mSize))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}
