#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* vsPath, const char* fsPath);
	ShaderProgram(const char* vsPath, const char* gsPath, const char* fsPath);

	virtual ~ShaderProgram();

	bool load(const char* vsPath, const char* fsPath);
	bool load(const char* vsPath, const char* gsPath, const char* fsPath);

	void deleteShaderProgram();

	void use() const;
	GLuint getID() const;
	bool isLoaded() const;

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;

    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;

	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;


private:
	GLuint mID;
	bool mIsLoaded;
};

#endif