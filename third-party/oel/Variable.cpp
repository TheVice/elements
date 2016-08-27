
#include "Variable.h"
#include "ShaderProgram.h"

namespace Library
{
Variable::Variable(ShaderProgram& aShaderProgram, const std::string& aName) :
	mShaderProgram(aShaderProgram),
	mLocation(aShaderProgram.GetUniform(&aName.front())),
	mName(aName)
{
}

ShaderProgram& Variable::GetShaderProgram()
{
	return mShaderProgram;
}

GLint Variable::GetLocation() const
{
	return mLocation;
}

const std::string& Variable::GetName() const
{
	return mName;
}

Variable& Variable::operator << (const glm::mat4& aValue)
{
	glUniformMatrix4fv(mLocation, 1, GL_FALSE, &aValue[0][0]);
	//
	return *this;
}

Variable& Variable::operator << (const glm::mat3& aValue)
{
	glUniformMatrix3fv(mLocation, 1, GL_FALSE, &aValue[0][0]);
	//
	return *this;
}

Variable& Variable::operator << (const glm::vec4& aValue)
{
	glUniform4fv(mLocation, 1, &aValue[0]);
	//
	return *this;
}

Variable& Variable::operator << (const glm::vec3& aValue)
{
	glUniform3fv(mLocation, 1, &aValue[0]);
	//
	return *this;
}

Variable& Variable::operator << (const glm::vec2& aValue)
{
	glUniform2fv(mLocation, 1, &aValue[0]);
	//
	return *this;
}

Variable& Variable::operator << (float aValue)
{
	glUniform1f(mLocation, aValue);
	//
	return *this;
}

Variable& Variable::operator << (int aValue)
{
	glUniform1i(mLocation, aValue);
	//
	return *this;
}
}
