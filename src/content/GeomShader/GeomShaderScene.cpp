#include "GeomShaderScene.h"

GeomShaderScene::GeomShaderScene()
{
	float points[] = {
	// position	  // color
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	shader.load(
		"src/content/GeomShader/simple_geom_scene.vert", 
		"src/content/GeomShader/simple_geom_scene.geom",
		"src/content/GeomShader/simple_geom_scene.frag");
}

void GeomShaderScene::init()
{
}

void GeomShaderScene::setCamera(FlyCamera* cam)
{
}

void GeomShaderScene::drawCurrent()
{
	shader.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 4);
}

void GeomShaderScene::updateCurrent(float dt)
{
}
