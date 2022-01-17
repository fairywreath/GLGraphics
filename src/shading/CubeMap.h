#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "Texture.h"

#include <glad/glad.h>

class CubeMap 
{
public:
	void init();


private:
	GLuint mTextureID;

};


#endif