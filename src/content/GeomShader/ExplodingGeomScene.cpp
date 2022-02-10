#include "ExplodingGeomScene.h"

#include <iostream>

ExplodingGeomScene::ExplodingGeomScene()
{
	shader.load(
		"src/content/GeomShader/exploding.vert",
		"src/content/GeomShader/exploding.geom",
		"src/content/GeomShader/exploding.frag"
	);

	model.loadModel("resources/models/backpack/backpack.obj");
	model.pShader = &modelShader;
	model.init();
}

void ExplodingGeomScene::init()
{
}

void ExplodingGeomScene::setCamera(FlyCamera* cam)
{
	flyCam = cam;
}

void ExplodingGeomScene::drawCurrent()
{
	if (flyCam == nullptr) {
		return;
	}

	shader.use();
	shader.setFloat("time", elapsedTime);
	shader.setMat4("model", glm::mat4(1.0f));
	shader.setMat4("projection", flyCam->getProjectionMatrix());
	shader.setMat4("view", flyCam->getViewMatrix());

	model.draw();
}

void ExplodingGeomScene::updateCurrent(float dt)
{
	elapsedTime = dt;
}
