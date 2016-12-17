
#include "ReaderHelpers.h"
#include <limits>
#include <cstring>

namespace Library
{
namespace ReaderHelpers
{

bool read_bool(const pugi::xml_node& aNode, bool& aValue)
{
	if (!aNode.empty())
	{
		aValue = aNode.text().as_bool();
		return true;
	}

	return false;
}

bool read_float(const pugi::xml_node& aNode, float& aValue)
{
	if (!aNode.empty())
	{
		aValue = aNode.text().as_float();
		return true;
	}

	return false;
}

bool read_std_string(const pugi::xml_node& aNode, std::string& aValue)
{
	aValue.clear();

	if (!aNode.empty())
	{
		aValue = aNode.text().get();
		return !aValue.empty();
	}

	return false;
}

bool read_unsigned_int(const pugi::xml_node& aNode, unsigned int& aValue)
{
	if (!aNode.empty())
	{
		aValue = aNode.text().as_uint();
		return true;
	}

	return false;
}

bool read_indices(const pugi::xml_node& aNode, std::vector<unsigned char>& aIndices)
{
	aIndices.clear();

	for (const auto& subNode : aNode)
	{
		if (std::strcmp(subNode.name(), "index"))
		{
			continue;
		}

		unsigned int index = 0u;

		if (!read_unsigned_int(subNode, index))
		{
			return false;
		}

		if (index > std::numeric_limits<unsigned char>::max())
		{
			return false;
		}

		aIndices.push_back(static_cast<unsigned char>(index));
	}

	return !aIndices.empty();
}

}
}
