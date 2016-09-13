#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

#include "RTTI.h"
#include "Variable.h"
#include <vector>
#include <map>

namespace Library
{

class ShaderProgram : public RTTI
{
	RTTI_DECLARATIONS(ShaderProgram, RTTI)

public:
	ShaderProgram();
	virtual ~ShaderProgram();

public:
	ShaderProgram(const ShaderProgram& aRhs) = delete;
	ShaderProgram& operator = (const ShaderProgram& aRhs) = delete;

public:
	// Variable* operator [](const std::string& aVariableName);

	GLuint GetProgram() const;
	const std::vector<Variable*>& GetVariables() const;
	const std::map<std::string, Variable*>& GetVariablesByName() const;

	GLvoid SetProgram(GLuint aProgram);
	virtual GLvoid Initialize(GLuint aVertexArrayObject);
	virtual GLvoid Use() const;
	virtual GLuint GetVertexSize() const;

	GLint GetAttrib(const GLchar* aAttribName);
	GLint GetUniform(const GLchar* aUniformName);

protected:
	GLuint mProgram;
	std::vector<Variable*> mVariables;
	std::map<std::string, Variable*> mVariablesByName;
};

#define SHADER_VARIABLE_DECLARATION(VariableName)	\
	public:											\
	Variable& VariableName() const;					\
	private:										\
	Variable* m ## VariableName;

#define SHADER_VARIABLE_DEFINITION(ShaderProgram, VariableName)	\
	Variable& ShaderProgram::VariableName() const				\
	{															\
		return *m ## VariableName;								\
	}

#define SHADER_VARIABLE_INITIALIZATION(VariableName) m ## VariableName(nullptr)

#define SHADER_VARIABLE_INSTANTIATE(VariableName)																\
	m ## VariableName = new Variable(*this, #VariableName);														\
	mVariables.push_back(m ## VariableName);																	\
	mVariablesByName.insert(std::pair<std::string, Variable*>(m ## VariableName->GetName(), m ## VariableName));
}

#endif