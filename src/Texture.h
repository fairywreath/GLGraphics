#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glad/glad.h>

class Texture
{
public:
	Texture();
	virtual ~Texture();

	GLuint getID() const;

	bool load(const std::string& path);


private:
	GLuint mID;

};

#endif