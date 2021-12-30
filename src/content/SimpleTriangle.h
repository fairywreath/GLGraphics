#ifndef SIMPLETRIANGLE_H
#define SIMPLETRIANGLE_H

#include <glad/glad.h>

#include "../scene/SceneNode.h"

class SimpleTriangle : public SceneNode
{
public:
	void init() override;

private:
	void drawCurrent() override;

private:
	GLuint VAO;
	GLuint VBO;

};

#endif

