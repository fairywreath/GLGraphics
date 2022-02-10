#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
	Shader();
	Shader(const std::string& shaderPath, const GLenum& shaderType);
	virtual ~Shader();

	bool load(const std::string& shaderPath, const GLenum& shaderType);
	void deleteShader();

	unsigned int getId() const;
	bool isLoaded() const;
	const std::string& getPath() const;
	const GLenum& getType() const;

private:
	GLuint mID;
	std::string mPath;
	GLenum mType;
	bool mIsLoaded;
};


#endif