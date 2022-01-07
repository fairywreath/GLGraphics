#ifndef LIGHTINGSCENE_H
#define LIGHTINGSCENE_H

#include "../scene/SceneNode.h"
#include "../shading/ShaderProgram.h"
#include "../scene/Camera.h"

#include <glad/glad.h>

class LightingScene : public SceneNode
{
public:
	void init() override;

	void setCamera(FlyCamera* cam);

private:
	void drawCurrent() override;
	void updateCurrent(float dt) override;

private:
	ShaderProgram lightSourceShader;
	ShaderProgram lightingShader;

	FlyCamera* camera = nullptr;

	GLuint cubeVAO;
	GLuint lightVAO;

	glm::mat4 cubeModel;
	glm::mat4  lightSourceModel;


	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	float deltaTime = 0;
	float elapsedTime = 0;

	// for rotation 
	float currentAngle = 0;
};


#endif