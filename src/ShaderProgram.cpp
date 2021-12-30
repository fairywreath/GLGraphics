#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm\gtc\type_ptr.hpp>

ShaderProgram::ShaderProgram() :
	mID(0)
{
}

ShaderProgram::ShaderProgram(const char* vsPath, const char* fsPath) :
	mID(0)
{
	load(vsPath, fsPath);
}

ShaderProgram::~ShaderProgram()
{
}

bool ShaderProgram::load(const char* vsPath, const char* fsPath)
{
	std::string vertSource;
	std::string fragSource;
	std::ifstream vsFile;
	std::ifstream fsFile;

	// ensure filestream can throw exceptions
	vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vsFile.open(vsPath);
		fsFile.open(fsPath);

		std::stringstream vsStream;
		std::stringstream fsStream;

		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();

		vsFile.close();
		fsFile.close();

		vertSource = vsStream.str();
		fragSource = fsStream.str();
	}
	catch (std::ifstream::failure err)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vsSource = vertSource.c_str();
	const char* fsSource = fragSource.c_str();

	// compile shaders
	GLuint vs, fs;

	int success;
	char infoLog[512];

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, nullptr);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, nullptr);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	mID = glCreateProgram();
	glAttachShader(mID, vs);
	glAttachShader(mID, fs);
	glLinkProgram(mID);
	if (!success)
	{
		glGetProgramInfoLog(mID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return success;
}

GLuint ShaderProgram::getID() const
{
	return mID;
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

void ShaderProgram::setMat4(const std::string& name, glm::mat4 matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setVec3(const std::string& name, glm::vec3 vec) const
{
	glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(vec));
}
