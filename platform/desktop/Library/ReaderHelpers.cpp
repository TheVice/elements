
#include "ReaderHelpers.h"
#include <map>
#include <cstring>

namespace Library
{
namespace ReaderHelpers
{

bool read_by_map(const pugi::xml_node& aNode, char aMemberCount,
				 const std::map<std::string, float*> aMatrixMap)
{
	for (const auto& attribute : aNode.attributes())
	{
		const auto search = aMatrixMap.find(attribute.name());

		if (search != aMatrixMap.end())
		{
			(*search->second) = attribute.as_float();
			aMemberCount--;
		}
	}

	return aMemberCount == 0;
}

bool read_by_map(const pugi::xml_node& aNode, char aMemberCount,
				 const std::map<std::string, unsigned int*> aMatrixMap)
{
	for (const auto& attribute : aNode.attributes())
	{
		const auto search = aMatrixMap.find(attribute.name());

		if (search != aMatrixMap.end())
		{
			(*search->second) = attribute.as_uint();
			aMemberCount--;
		}
	}

	return aMemberCount == 0;
}

bool read_float(const pugi::xml_node& aNode, float& aValue)
{
	const std::map<std::string, float*> matrixMap =
	{
		{ "value", &aValue }
	};
	//
	return read_by_map(aNode, 1, matrixMap);
}

bool read_glm_vec2(const pugi::xml_node& aNode, glm::vec2& aValue)
{
	const std::map<std::string, float*> matrixMap =
	{
		{ "x", &aValue[0] },
		{ "y", &aValue[1] },
		//
		{ "u", &aValue[0] },
		{ "v", &aValue[1] }
	};
	//
	return read_by_map(aNode, aValue.length(), matrixMap);
}

bool read_glm_vec3(const pugi::xml_node& aNode, glm::vec3& aValue)
{
	const std::map<std::string, float*> matrixMap =
	{
		{ "x", &aValue[0] },
		{ "y", &aValue[1] },
		{ "z", &aValue[2] }
	};
	//
	return read_by_map(aNode, aValue.length(), matrixMap);
}

bool read_glm_vec4(const pugi::xml_node& aNode, glm::vec4& aValue)
{
	const std::map<std::string, float*> matrixMap =
	{
		{ "x", &aValue[0] },
		{ "y", &aValue[1] },
		{ "z", &aValue[2] },
		{ "w", &aValue[3] }
	};
	//
	return read_by_map(aNode, aValue.length(), matrixMap);
}

bool read_glm_mat3(const pugi::xml_node& aNode, glm::mat3& aValue)
{
	const std::map<std::string, float*> matrixMap =
	{
		{ "m00", &aValue[0][0] },
		{ "m01", &aValue[0][1] },
		{ "m02", &aValue[0][2] },
		//
		{ "m10", &aValue[1][0] },
		{ "m11", &aValue[1][1] },
		{ "m12", &aValue[1][2] },
		//
		{ "m20", &aValue[2][0] },
		{ "m21", &aValue[2][1] },
		{ "m22", &aValue[2][2] }
	};
	//
	return read_by_map(aNode, aValue[0].length() * aValue.length(), matrixMap);
}

bool read_glm_mat4(const pugi::xml_node& aNode, glm::mat4& aValue)
{
	const std::map<std::string, float*> matrixMap =
	{
		{ "m00", &aValue[0][0] },
		{ "m01", &aValue[0][1] },
		{ "m02", &aValue[0][2] },
		{ "m03", &aValue[0][3] },
		//
		{ "m10", &aValue[1][0] },
		{ "m11", &aValue[1][1] },
		{ "m12", &aValue[1][2] },
		{ "m13", &aValue[1][3] },
		//
		{ "m20", &aValue[2][0] },
		{ "m21", &aValue[2][1] },
		{ "m22", &aValue[2][2] },
		{ "m23", &aValue[2][3] },
		//
		{ "m30", &aValue[3][0] },
		{ "m31", &aValue[3][1] },
		{ "m32", &aValue[3][2] },
		{ "m33", &aValue[3][3] }
	};
	//
	return read_by_map(aNode, aValue[0].length() * aValue.length(), matrixMap);
}

bool read_unsigned_int(const pugi::xml_node& aNode, unsigned int& aValue)
{
	const std::map<std::string, unsigned int*> matrixMap =
	{
		{ "value", &aValue }
	};
	//
	return read_by_map(aNode, 1, matrixMap);
}

bool read_indices(const pugi::xml_node& aNode, std::vector<unsigned int>& aIndices)
{
	aIndices.clear();

	for (const auto& index : aNode)
	{
		if (std::strcmp(index.name(), "index"))
		{
			continue;
		}

		unsigned int index_data = 0u;

		if (!read_unsigned_int(index, index_data))
		{
			return false;
		}

		aIndices.push_back(index_data);
	}

	return !aIndices.empty();
}

}
}
