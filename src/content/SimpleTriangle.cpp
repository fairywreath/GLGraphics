#include "SimpleTriangle.h"

void SimpleTriangle::init()
{
	float triangleVertices[] = {
		-0.5f , -0.5f, 0.0f,
		0.5f , -0.5f, 0.0f,
		0.0f , 0.5f, 0.0f
	};

	float triangleTexCoords[] = {
		0.0f, 0.0f,  // lower-left corner  
		1.0f, 0.0f,  // lower-right corner
		0.5f, 1.0f   // top-center corner
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SimpleTriangle::drawCurrent()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
