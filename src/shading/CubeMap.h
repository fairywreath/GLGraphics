#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "Texture.h"

#include <glad/glad.h>

#include <vector>

class CubeMap 
{
public:
	void loadCubeMap(const std::vector<std::string>& faces);
	
	GLuint getID() const;

private:
	GLuint mTextureID = 0;

};


#endif