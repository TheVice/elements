
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

	auto transform_node = root_node.child("transform");

	if (transform_node.empty())
	{
		return false;
	}

	auto size_node = root_node.child("size");

	if (size_node.empty())
	{
		return false;
	}

	mVertices.reserve(6);
	mVertices.resize(0);

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

		auto a_vertex_pos = glm::vec2(
								pos_node.attribute("x").as_float(),
								pos_node.attribute("y").as_float());
		auto vertex_data = VertexStructure(a_vertex_pos);
		mVertices.push_back(vertex_data);
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
	mSize = size_node.attribute("value").as_float();
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
	demo_data.mTransform = data.value().mTransform;
	demo_data.mSize = data.value().mSize;
	//
	return true;
}
