
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
	mProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(mProgram);

	for (Variable* variable : mVariables)
	{
		delete variable;
	}
}

GLuint ShaderProgram::CompileShaderFromData(GLenum aShaderType, const GLchar* aShaderSource)
{
	assert(aShaderSource);
	//
	const auto length = static_cast<GLint>(std::strlen(aShaderSource));
	assert(length);
	//
	const GLuint shader = glCreateShader(aShaderType);
	glShaderSource(shader, 1, &aShaderSource, &length);
	glCompileShader(shader);
	//
	IsShaderCompiled(shader);
	//
	return shader;
}

GLvoid ShaderProgram::IsShaderCompiled(GLuint aShader)
{
	GLint compileStatus = GL_FALSE;
	glGetShaderiv(aShader, GL_COMPILE_STATUS, &compileStatus);

	if (GL_FALSE == compileStatus)
	{
		GLint logLength = 0;
		glGetShaderiv(aShader, GL_INFO_LOG_LENGTH, &logLength);
		//
		std::string log(logLength + 1, '\0');
		//
		glGetShaderInfoLog(aShader, logLength, nullptr, &log.front());
		//
		std::stringstream errorMessage;
		errorMessage << log.c_str() << std::endl;
		errorMessage << "glCompileShader() failed" << std::endl;
		//
		throw std::runtime_error(errorMessage.str());
	}
}

GLvoid ShaderProgram::IsProgramLinked(GLuint aProgram)
{
	GLint linkStatus = GL_FALSE;
	glGetProgramiv(aProgram, GL_LINK_STATUS, &linkStatus);

	if (GL_FALSE == linkStatus)
	{
		GLint logLength = 0;
		glGetProgramiv(aProgram, GL_INFO_LOG_LENGTH, &logLength);
		//
		std::string log(logLength + 1, '\0');
		//
		glGetProgramInfoLog(aProgram, logLength, nullptr, &log.front());
		//
		std::stringstream errorMessage;
		errorMessage << log.c_str() << std::endl;
		errorMessage << "glLinkProgram() failed" << std::endl;
		//
		throw std::runtime_error(errorMessage.str());
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

GLvoid ShaderProgram::BuildProgram(const std::vector<ShaderDefinition>& aShaderDefinitions)
{
	assert(!aShaderDefinitions.empty());
	//
	std::vector<GLuint> compiledShaders(aShaderDefinitions.size());
	compiledShaders.clear();

	for (const auto& shaderDefinition : aShaderDefinitions)
	{
		const GLuint compiledShader = CompileShaderFromData(shaderDefinition.first, &shaderDefinition.second.front());
		glAttachShader(mProgram, compiledShader);
		compiledShaders.push_back(compiledShader);
	}

	glLinkProgram(mProgram);
	//
	IsProgramLinked(mProgram);

	for (auto compileShader : compiledShaders)
	{
		glDeleteShader(compileShader);
	}
}

GLvoid ShaderProgram::Initialize(GLuint aVertexArrayObject)
{
	glBindVertexArray(aVertexArrayObject);
}

GLvoid ShaderProgram::Use() const
{
	glUseProgram(mProgram);
}

GLvoid ShaderProgram::CreateVertexBuffer(const GLvoid* aVertices, GLuint aVertexCount,
		GLuint& aVertexBuffer) const
{
	glGenBuffers(1, &aVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, aVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, GetVertexSize() * aVertexCount, aVertices, GL_STATIC_DRAW);
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
