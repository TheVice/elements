#ifndef _READER_HELPERS_H_
#define _READER_HELPERS_H_

#include <pugixml.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace Library
{
namespace ReaderHelpers
{

bool read_float(const pugi::xml_node& aNode, float& aValue);

bool read_glm_vec2(const pugi::xml_node& aNode, glm::vec2& aValue);
bool read_glm_vec3(const pugi::xml_node& aNode, glm::vec3& aValue);
bool read_glm_vec4(const pugi::xml_node& aNode, glm::vec4& aValue);

bool read_glm_mat3(const pugi::xml_node& aNode, glm::mat3& aValue);
bool read_glm_mat4(const pugi::xml_node& aNode, glm::mat4& aValue);

bool read_unsigned_int(const pugi::xml_node& aNode, unsigned int& aValue);

bool read_indices(const pugi::xml_node& aNode, std::vector<unsigned int>& aIndices);

}
}

#endif
