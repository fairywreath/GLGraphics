#ifndef GEOMSHADERSCENE_H
#define GEOMSHADERSCENE_H

#include "../../scene/SceneNode.h"
#include "../../shading/ShaderProgram.h"
#include "../../scene/Camera.h"

#include <glad/glad.h>

class GeomShaderScene : public SceneNode
{
public:
	GeomShaderScene();

	void init() override;

	void setCamera(FlyCamera* cam);

private:
	void drawCurrent() override;
	void updateCurrent(float dt) override;

private:
	ShaderProgram shader;

	GLuint VBO;
	GLuint VAO;
};


#endif