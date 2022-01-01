#ifndef ROTATINGCUBE_H
#define ROTATINGCUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../scene/SceneNode.h"
#include "../Shading/Texture.h"
#include "../Shading/ShaderProgram.h"


class RotatingCube : public SceneNode
{
public:
	~RotatingCube() override;

	void init() override;
	void setShaderProgram(GLuint program);

private:
	void drawCurrent() override;
	void updateCurrent(float dt) override;

private:
	ShaderProgram shader;
	
	GLuint VAO;
	GLuint VBO;

	Texture texture1;
	Texture texture2;

	glm::mat4 model;

	float currentAngle;
};


#endif