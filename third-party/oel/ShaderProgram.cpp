
#include "ShaderProgram.h"
#include <sstream>
#include <cassert>
#ifndef _MSC_VER
#include <cstring>
#endif

namespace Library
{

RTTI_DEFINITIONS(ShaderProgram)

ShaderProgram::ShaderProgram() :
	mProgram(0),
	mVariables(),
	mVariablesByName()
{
}

ShaderProgram::~ShaderProgram()
{
	for (Variable* variable : mVariables)
	{
		delete variable;
	}
}

GLuint ShaderProgram::GetProgram() const
{
	return mProgram;
}

const std::vector<Variable*>& ShaderProgram::GetVariables() const
{
	return mVariables;
}

const std::map<std::string, Variable*>& ShaderProgram::GetVariablesByName() const
{
	return mVariablesByName;
}

GLvoid ShaderProgram::SetProgram(GLuint aProgram)
{
	assert(aProgram);
	mProgram = aProgram;
}

GLvoid ShaderProgram::Initialize(GLuint aVertexArrayObject)
{
	glBindVertexArray(aVertexArrayObject);
}

GLvoid ShaderProgram::Use() const
{
	glUseProgram(mProgram);
}

GLuint ShaderProgram::GetVertexSize() const
{
	throw std::runtime_error("GetVertexSize() method not implemented for ShaderProgram class");
}

GLint ShaderProgram::GetAttrib(const GLchar* aAttribName)
{
	assert(aAttribName);
	const GLint attrib = glGetAttribLocation(mProgram, aAttribName);

	if (attrib == -1)
	{
		std::stringstream errorMessage;
		errorMessage << "Program attribute not found: " << aAttribName << std::endl;
		errorMessage << "glGetAttribLocation() failed" << std::endl;
		throw std::runtime_error(errorMessage.str());
	}

	return attrib;
}

GLint ShaderProgram::GetUniform(const GLchar* aUniformName)
{
	assert(aUniformName);
	const GLint uniform = glGetUniformLocation(mProgram, aUniformName);

	if (uniform == -1)
	{
		std::stringstream errorMessage;
		errorMessage << "Program uniform not found: " << aUniformName << std::endl;
		errorMessage << "glGetUniformLocation() failed" << std::endl;
		throw std::runtime_error(errorMessage.str());
	}

	return uniform;
}

}
