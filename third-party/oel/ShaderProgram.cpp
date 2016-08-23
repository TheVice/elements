
#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <cassert>
#ifndef _MSC_VER
#include <cstring>
#endif

namespace Library
{
namespace Utility
{

std::streamoff readFile(const std::string& aFileName, std::vector<char>& aFileContent)
{
	aFileContent.clear();
	std::ifstream file(aFileName, std::fstream::binary);

	if (file)
	{
		file.seekg(0, std::fstream::end);
		const std::streamoff length = file.tellg();

		if (!length)
		{
			file.close();
			return length;
		}

		file.seekg(0, std::fstream::beg);
		aFileContent.reserve(static_cast<std::string::size_type>(length));
		aFileContent.resize(static_cast<std::string::size_type>(length));
		file.read(&aFileContent.front(), length);
		file.close();
		return length;
	}

	return 0;
}

std::streamoff readFile(const char* aFileName, std::vector<char>& aFileContent)
{
	return readFile(std::string(aFileName), aFileContent);
}

}

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

GLuint ShaderProgram::CompileShaderFromFile(GLenum aShaderType, const std::string& aFileName)
{
	std::vector<char> shaderSource;
	Utility::readFile(aFileName, shaderSource);

	if (shaderSource.empty())
	{
		std::stringstream errorMessage;
		errorMessage << "Unable to read shader file: " << aFileName << std::endl;
		errorMessage << "CompileShaderFromFile() failed" << std::endl;
		throw std::runtime_error(errorMessage.str());
	}

	return CompileShaderFromData(aShaderType, shaderSource);
}

GLuint ShaderProgram::CompileShaderFromData(GLenum aShaderType, const char* aShaderSource)
{
	const GLuint length = std::strlen(aShaderSource);

	if (!length)
	{
		std::stringstream errorMessage;
		errorMessage << "Shader data are empty" << std::endl;
		errorMessage << "CompileShaderFromData() failed" << std::endl;
		throw std::runtime_error(errorMessage.str());
	}

	std::vector<char> shaderSource(length);
	shaderSource.resize(length);
	std::memcpy(&shaderSource.front(), aShaderSource, length);
	return CompileShaderFromData(aShaderType, shaderSource);
}

GLuint ShaderProgram::CompileShaderFromData(GLenum aShaderType, std::vector<char>& aShaderSource)
{
	assert(!aShaderSource.empty());
	//
	const GLchar* sourcePointer = &aShaderSource.front();
	const GLint length = aShaderSource.size();
	//
	GLuint shader = glCreateShader(aShaderType);
	glShaderSource(shader, 1, &sourcePointer, &length);
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

GLvoid ShaderProgram::BuildProgram(const std::vector<ShaderDefinition>& aShaderDefinitions, GLboolean aIsData)
{
	std::vector<GLuint> compiledShaders;
	compiledShaders.reserve(aShaderDefinitions.size());
	compiledShaders.clear();

	for (ShaderDefinition shaderDefinition : aShaderDefinitions)
	{
		GLuint compiledShader = 0;

		if (aIsData)
		{
			compiledShader = CompileShaderFromData(shaderDefinition.first, &shaderDefinition.second.front());
		}
		else
		{
			compiledShader = CompileShaderFromFile(shaderDefinition.first, shaderDefinition.second);
		}

		glAttachShader(mProgram, compiledShader);
		compiledShaders.push_back(compiledShader);
	}

	glLinkProgram(mProgram);
	//
	IsProgramLinked(mProgram);

	for (GLuint compileShader : compiledShaders)
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
	throw std::runtime_error("ShaderProgram::GetVertexSize() not implemented for base class");
}

GLint ShaderProgram::GetAttrib(const GLchar* aAttribName)
{
	GLint attrib = glGetAttribLocation(mProgram, aAttribName);

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
	GLint uniform = glGetUniformLocation(mProgram, aUniformName);

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
