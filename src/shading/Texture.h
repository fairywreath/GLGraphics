#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glad/glad.h>

class Texture
{
public:
	enum class TYPE
	{
		DIFFUSE, 
		SPECULAR
	};

	
	Texture();
	virtual ~Texture();

	GLuint getID() const;

	bool load(const std::string& path);

public:
	TYPE Type = TYPE::DIFFUSE;

private:
	GLuint mID;

};

#endif