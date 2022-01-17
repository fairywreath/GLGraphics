#ifndef SKYBOX_H
#define SKYBOX_H

#include "../shading/CubeMap.h"
#include "../shading//ShaderProgram.h"
#include "Camera.h"

class Skybox
{
public:
	void load(const std::vector<std::string>& faces);

	// drawn last!
	void draw() const;

	// public ptrs for now
	ShaderProgram* pShader = nullptr;
	CameraBase* pCamera = nullptr;

private:
	void init();

private:
	GLuint mVAO = 0;
	CubeMap mCubemap;


};

#endif