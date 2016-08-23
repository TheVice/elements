#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace Library
{
class ShaderProgram;

class Variable
{
public:
	Variable(ShaderProgram& aShaderProgram, const std::string& aName);

public:
	Variable(const Variable& aRhs) = delete;
	Variable& operator=(const Variable& aRhs) = delete;

public:
	ShaderProgram& GetShaderProgram();
	const GLint& GetLocation() const;
	const std::string& GetName() const;

	Variable& operator << (const glm::mat4& aValue);
	Variable& operator << (const glm::mat3& aValue);
	Variable& operator << (const glm::vec4& aValue);
	Variable& operator << (const glm::vec3& aValue);
	Variable& operator << (const glm::vec2& aValue);
	Variable& operator << (float aValue);
	Variable& operator << (int aValue);

private:
	ShaderProgram& mShaderProgram;
	GLint mLocation;
	std::string mName;
};
}

#endif
