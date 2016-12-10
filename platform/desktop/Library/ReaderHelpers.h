#ifndef _READER_HELPERS_H_
#define _READER_HELPERS_H_

#include <pugixml.hpp>
#include <glm/glm.hpp>
#include <algorithm>
#include <array>
#include <bitset>
#include <vector>

namespace Library
{
namespace ReaderHelpers
{

template<typename T>
bool read_glm_vec(const pugi::xml_node& aNode, T& aValue)
{
	std::array<char, 14> keys = { 'x', 'y', 'z', 'w',
								  'u', 'v',
								  'r', 'g', 'b', 'a',
								  's', 't', 'p', 'q'
								};
	std::bitset<4> setKeys;
	const auto vecLength = aValue.length();

	switch (vecLength)
	{
		case 2:
			setKeys.set(2);
			setKeys.set(3);
			break;

		case 3:
			setKeys.set(3);
			break;

		case 4:
			setKeys.reset();
			break;

		default:
			return false;
	}

	for (const auto& attribute : aNode.attributes())
	{
		const auto find = std::find(keys.cbegin(), keys.cend(), attribute.name()[0]);

		if (find != keys.cend())
		{
			const auto value = attribute.as_float();

			switch (*find)
			{
				case 'x':
				case 'u':
				case 'r':
				case 's':
					if (!setKeys.test(0))
					{
						aValue[0] = value;
						setKeys.set(0);
					}

					break;

				case 'y':
				case 'v':
				case 'g':
				case 't':
					if (!setKeys.test(1))
					{
						aValue[1] = value;
						setKeys.set(1);
					}

					break;

				case 'z':
				case 'b':
				case 'p':
					if (!setKeys.test(2))
					{
						aValue[2] = value;
						setKeys.set(2);
					}

					break;

				case 'w':
				case 'a':
				case 'q':
					if (!setKeys.test(3))
					{
						aValue[3] = value;
						setKeys.set(3);
					}

					break;

				default:
					break;
			}
		}
	}

	return setKeys.all();
}

template<typename T>
bool read_glm_mat(const pugi::xml_node& aNode, T& aValue)
{
	auto row_count = aValue.length();

	for (const auto& subNode : aNode)
	{
		auto row = aValue[0];

		if (read_glm_vec(subNode, row))
		{
			aValue[aValue.length() - row_count] = row;
			--row_count;

			if (!row_count)
			{
				return true;
			}
		}
	}

	return false;
}

bool read_float(const pugi::xml_node& aNode, float& aValue);
bool read_std_string(const pugi::xml_node& aNode, std::string& aValue);
bool read_unsigned_int(const pugi::xml_node& aNode, unsigned int& aValue);
bool read_indices(const pugi::xml_node& aNode, std::vector<unsigned char>& aIndices);

}
}

#endif
