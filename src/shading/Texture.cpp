#include "Texture.h"

#include <iostream>

#include <stb_image.h>

Texture::Texture() :
	mID(0)
{
}

Texture::~Texture()
{
}

GLuint Texture::getID() const
{
	return mID;
}

bool Texture::load(const std::string& path)
{
	int width, height, nrComponents;

	// opengl expects 0.0 to be bottom y, but images have 0.0 at the top 
	stbi_set_flip_vertically_on_load(true); 
	
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data == nullptr)
	{
		std::cout << "Failed to load texture: " << path << std::endl;
		return false;
	}

	GLenum format;
	if (nrComponents == 1)
		format = GL_RED;
	else if (nrComponents == 3)
		format = GL_RGB;
	else if (nrComponents == 4)
		format = GL_RGBA;

	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);		// unbind texture

	stbi_image_free(data);

	return true;
}

