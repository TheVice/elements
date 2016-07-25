
#include "ReaderHelpers.h"
#include <cstdlib>

bool read_glm_vec2(const pugi::xml_node& aNode, glm::vec2& aValue)
{
	if (aNode.empty())
	{
		return false;
	}

	if (aNode.child("x").first_child().empty())
	{
		return false;
	}

	if (aNode.child("y").first_child().empty())
	{
		return false;
	}

	aValue.x = std::atof(aNode.child("x").first_child().value());
	aValue.y = std::atof(aNode.child("y").first_child().value());
	//
	return true;
}

bool read_glm_vec4(const pugi::xml_node& aNode, glm::vec4& aValue)
{
	if (aNode.empty())
	{
		return false;
	}

	if (aNode.child("x").first_child().empty())
	{
		return false;
	}

	if (aNode.child("y").first_child().empty())
	{
		return false;
	}

	if (aNode.child("z").first_child().empty())
	{
		return false;
	}

	if (aNode.child("w").first_child().empty())
	{
		return false;
	}

	aValue.x = std::atof(aNode.child("x").first_child().value());
	aValue.y = std::atof(aNode.child("y").first_child().value());
	aValue.z = std::atof(aNode.child("z").first_child().value());
	aValue.w = std::atof(aNode.child("w").first_child().value());
	//
	return true;
}

bool read_glm_mat4(const pugi::xml_node& aNode, glm::mat4& aValue)
{
	if (aNode.empty())
	{
		return false;
	}

	glm::vec4 value0;

	if (!read_glm_vec4(aNode.child("value0"), value0))
	{
		return false;
	}

	glm::vec4 value1;

	if (!read_glm_vec4(aNode.child("value1"), value1))
	{
		return false;
	}

	glm::vec4 value2;

	if (!read_glm_vec4(aNode.child("value2"), value2))
	{
		return false;
	}

	glm::vec4 value3;

	if (!read_glm_vec4(aNode.child("value3"), value3))
	{
		return false;
	}

	aValue[0] = value0;
	aValue[1] = value1;
	aValue[2] = value2;
	aValue[3] = value3;
	//
	return true;
}
