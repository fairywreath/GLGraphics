#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* vsPath, const char* fsPath);
	virtual ~ShaderProgram();

	bool load(const char* vsPath, const char* fsPath);

	void use() const;
	GLuint getID() const;

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 matrix) const;
	void setVec3(const std::string& name, glm::vec3 vec) const;

private:
	GLuint mID;
};

#endif