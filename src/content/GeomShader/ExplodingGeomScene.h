#ifndef EXPLODINGGEOMSCENE_H
#define EXPLODINGGEOMSCENE_H

#include "../../scene/SceneNode.h"
#include "../../shading/ShaderProgram.h"
#include "../../scene/Camera.h"
#include "../../shading/Texture.h"
#include "../../mesh/Model.h"

#include <glad/glad.h>

class ExplodingGeomScene : public SceneNode
{
public:
	ExplodingGeomScene();

	void init() override;

	void setCamera(FlyCamera* cam);

private:
	void drawCurrent() override;
	void updateCurrent(float dt) override;

private:
	ShaderProgram shader;

	FlyCamera* flyCam = nullptr ;

	Model model;

	float elapsedTime = 0;


};






#endif