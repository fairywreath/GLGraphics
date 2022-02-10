#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader() :
	mID(0),
	mPath(""),
	mType(0),
	mIsLoaded(false)
{
}

Shader::Shader(const std::string& shaderPath, const GLenum& shaderType) :
	mID(0),
	mPath(shaderPath),
	mType(0),
	mIsLoaded(false)
{
	load(shaderPath, shaderType);
}

Shader::~Shader()
{
	deleteShader();
}

bool Shader::load(const std::string& shaderPath, const GLenum& shaderType)
{
	std::string source;
	std::ifstream file;

	// ensure filestream can throw exceptions
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(shaderPath);

		std::stringstream sstream;
		sstream << file.rdbuf();

		file.close();

		source = sstream.str();
	}
	catch (std::ifstream::failure err)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << shaderPath << std::endl;
	}

	int success;
	char infoLog[512];
	const char* shaderSource = source.c_str();

	mID = glCreateShader(shaderType);
	glShaderSource(mID, 1, &shaderSource, nullptr);
	glCompileShader(mID);
	glGetShaderiv(mID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(mID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED: " << shaderPath << std::endl
				  << infoLog << std::endl;

		glDeleteShader(mID);
		mID = 0;
		mIsLoaded = false;

		return false;
	};

	mPath = shaderPath;
	mType = shaderType;
	mIsLoaded = true;
	return true;
}

void Shader::deleteShader()
{
	if (mIsLoaded) 
	{
		glDeleteShader(mID);
		mID = 0;
		mIsLoaded = 0;
	}
}

unsigned int Shader::getId() const
{
	return mID;
}

bool Shader::isLoaded() const
{
	return mIsLoaded;
}

const std::string& Shader::getPath() const
{
	return mPath;
}

const GLenum& Shader::getType() const
{
	return mType;
}
