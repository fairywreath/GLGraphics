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
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data == nullptr)
	{
		std::cout << "Failed to load texture: " << path << std::endl;
		return false;
	}


	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);		// unbind texture

	stbi_image_free(data);

	return true;
}

