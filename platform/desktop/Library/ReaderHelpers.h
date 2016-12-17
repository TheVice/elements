#ifndef _READER_HELPERS_H_
#define _READER_HELPERS_H_

#include <pugixml.hpp>
#include <glm/glm.hpp>
#include <array>
#include <vector>

namespace Library
{
namespace ReaderHelpers
{

template<typename T>
bool read_glm_vec(const pugi::xml_node& aNode, T& aValue)
{
	if (aNode.empty())
	{
		return false;
	}

	std::array<std::string, 4> keys;
	const auto element_count = aValue.length();

	if (static_cast<size_t>(element_count) > keys.size())
	{
		return false;
	}

	if (aNode.attribute("x"))
	{
		keys = { "x", "y", "z", "w" };
	}
	else if (aNode.attribute("u"))
	{
		keys = { "u", "v" };

		if (static_cast<size_t>(element_count) > 2u)
		{
			return false;
		}
	}
	else if (aNode.attribute("r"))
	{
		keys = { "r", "g", "b", "a" };
	}
	else if (aNode.attribute("s"))
	{
		keys = { "s", "t", "p", "q" };
	}
	else
	{
		return false;
	}

	for (auto element_num = 0; element_num < element_count; ++element_num)
	{
		const auto attribute_node = aNode.attribute(keys[element_num].c_str());

		if (!attribute_node)
		{
			return false;
		}

		aValue[element_num] = attribute_node.as_float();
	}

	return true;
}

template<typename T>
bool read_glm_mat(const pugi::xml_node& aNode, T& aValue)
{
	if (aNode.empty())
	{
		return false;
	}

	const std::array<std::string, 4> keys = { "r0", "r1", "r2", "r3" };
	const auto row_count = aValue.length();

	if (static_cast<size_t>(row_count) > keys.size())
	{
		return false;
	}

	for (auto row_num = 0; row_num < row_count; ++row_num)
	{
		const auto row_node = aNode.child(keys[row_num].c_str());

		if (!row_node)
		{
			return false;
		}

		auto row = aValue[row_num];

		if (!read_glm_vec(row_node, row))
		{
			return false;
		}

		aValue[row_num] = row;
	}

	return true;
}

bool read_bool(const pugi::xml_node& aNode, bool& aValue);
bool read_float(const pugi::xml_node& aNode, float& aValue);
bool read_std_string(const pugi::xml_node& aNode, std::string& aValue);
bool read_unsigned_int(const pugi::xml_node& aNode, unsigned int& aValue);
bool read_indices(const pugi::xml_node& aNode, std::vector<unsigned char>& aIndices);

}
}

#endif
