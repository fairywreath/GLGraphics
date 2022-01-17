#ifndef FRAMEBUFFERSSCENE_H
#define FRAMEBUFFERSSCENE_H

#include "../../scene/SceneNode.h"
#include "../../shading/ShaderProgram.h"
#include "../../scene/Camera.h"
#include "../../shading/Texture.h"
#include "../../mesh/Cube.h"
#include "../../mesh/Quad.h"
#include "../../mesh/Model.h"

#include <glad/glad.h>

class FrameBuffersScene : public SceneNode
{
public:
	void init() override;
	void setCamera(FlyCamera* cam);

private:
	void drawCurrent() override;
	void updateCurrent(float dt) override;

private:
	GLuint fbo = 0;
	GLuint textureColorbuffer = 0;
	GLuint rbo = 0;

	const int windowWidth = 1600;
	const int windowHeight = 900;

	ShaderProgram sceneShader;
	ShaderProgram screenShader;

	std::vector<Cube> cubes;
	Texture cubeTexture;

	Quad screenQuad;

	FlyCamera* camera = nullptr;
	glm::mat4 model = glm::mat4(1.0f);

	Model sponza;
	Model backpack;
};


#endif