#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm\gtc\type_ptr.hpp>

ShaderProgram::ShaderProgram() :
	mID(0),
	mIsLoaded(false)
{
}

ShaderProgram::ShaderProgram(const char* vsPath, const char* fsPath) :
	mID(0),
	mIsLoaded(false)
{
	load(vsPath, fsPath);
}

ShaderProgram::ShaderProgram(const char* vsPath, const char* gsPath, const char* fsPath) :
	mID(0),
	mIsLoaded(false)
{
	load(vsPath, gsPath, fsPath);
}

ShaderProgram::~ShaderProgram()
{
	deleteShaderProgram();
}

bool ShaderProgram::load(const char* vsPath, const char* fsPath)
{
	Shader vertShader(vsPath, GL_VERTEX_SHADER);
	Shader fragShader(fsPath, GL_FRAGMENT_SHADER);

	mID = glCreateProgram();
	glAttachShader(mID, vertShader.getId());
	glAttachShader(mID, fragShader.getId());
	glLinkProgram(mID);

	GLint success;
	GLchar infoLog[1024];
	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mID, 1024, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: \n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;

		glDeleteProgram(mID);
		mID = 0;
	}

	mIsLoaded = static_cast<bool>(success);
	return mIsLoaded;
}

bool ShaderProgram::load(const char* vsPath, const char* gsPath, const char* fsPath)
{
	Shader vertShader(vsPath, GL_VERTEX_SHADER);
	Shader geomShader(gsPath, GL_GEOMETRY_SHADER);
	Shader fragShader(fsPath, GL_FRAGMENT_SHADER);

	mID = glCreateProgram();
	glAttachShader(mID, vertShader.getId());
	glAttachShader(mID, geomShader.getId());
	glAttachShader(mID, fragShader.getId());
	glLinkProgram(mID);

	GLint success;
	GLchar infoLog[1024];
	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mID, 1024, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: \n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	
		glDeleteProgram(mID);
		mID = 0;
	}

	mIsLoaded = static_cast<bool>(success);
	return mIsLoaded;
}

void ShaderProgram::deleteShaderProgram()
{
	if (mIsLoaded)
	{
		glDeleteProgram(mID);
		mID = 0;
		mIsLoaded = false;
	}
}

GLuint ShaderProgram::getID() const
{
	return mID;
}

bool ShaderProgram::isLoaded() const
{
	return mIsLoaded;
}


void ShaderProgram::use() const
{
	glUseProgram(mID);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
}

void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}
void ShaderProgram::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(mID, name.c_str()), x, y, z, w);
}

void ShaderProgram::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}