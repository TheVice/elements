#ifndef _READER_HELPERS_H_
#define _READER_HELPERS_H_

#include <pugixml.hpp>
#include <glm/glm.hpp>

bool read_glm_vec2(const pugi::xml_node& aNode, glm::vec2& aValue);
bool read_glm_vec4(const pugi::xml_node& aNode, glm::vec4& aValue);
bool read_glm_mat4(const pugi::xml_node& aNode, glm::mat4& aValue);

#endif
