#ifndef TEXTUREDRECTANGLE_H
#define TEXTUREDRECTANGLE_H

#include <glad/glad.h>

#include "../scene/SceneNode.h"
#include "../Texture.h"

class TexturedRectangle : public SceneNode
{
public:
	TexturedRectangle();

	void init() override;

private:
	void drawCurrent() override;

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	Texture texture;
};

#endif

