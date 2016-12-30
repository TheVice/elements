
#include "VelocitiesProcessSettings.h"
#include <elements/assets/assets_storage.h>
#include <ReaderHelpers.h>
#include <cstring>

namespace Rendering
{

#define CLEAR()	\
	mVertices.clear();	\
	mIndices.clear();	\
	\
	u_product.clear();	\
	u_dt = 0.0f;	\
	\
	mIsEmpty = true;

bool VelocitiesProcessSettings::read(const pugi::xml_document& doc)
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

	const auto u_product_node = settings_node.child("u_product");

	if (u_product_node.empty())
	{
		return !mIsEmpty;
	}

	const auto u_dt_node = settings_node.child("u_dt");

	if (u_dt_node.empty())
	{
		return !mIsEmpty;
	}

	for (const auto& subNode : vertices_node)
	{
		if (std::strcmp(subNode.name(), "vertex"))
		{
			continue;
		}

		const auto a_field_uv_node = subNode.child("a_field_uv");

		if (a_field_uv_node.empty())
		{
			return !mIsEmpty;
		}

		const auto a_field_data_node = subNode.child("a_field_data");

		if (a_field_data_node.empty())
		{
			return !mIsEmpty;
		}

		auto a_field_uv = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_field_uv_node, a_field_uv))
		{
			return !mIsEmpty;
		}

		auto a_field_data = eps::math::vec2();

		if (!Library::ReaderHelpers::read_glm_vec(a_field_data_node, a_field_data))
		{
			return !mIsEmpty;
		}

		const auto vertex = VelocitiesProcessVertex(a_field_uv, a_field_data);
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

	if (!Library::ReaderHelpers::read_std_string(u_product_node, u_product))
	{
		return !mIsEmpty;
	}

	if (!Library::ReaderHelpers::read_float(u_dt_node, u_dt))
	{
		return !mIsEmpty;
	}

	mIsEmpty = false;
	return !mIsEmpty;
}

}
