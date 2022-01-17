#include "FrameBuffersScene.h"

#include <iostream>

void FrameBuffersScene::init()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// generate texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);	//allocate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach texture(color buffer attachment) to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// rbo for depth and stencil buffer
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);		// allocate storage
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// attach renderbuffer to framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// check if renderbuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not compelte.\n";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// initialize shaders
	sceneShader.load("src/content/Framebuffers/scene.vs.glsl", "src/content/Framebuffers/scene.fs.glsl");
	screenShader.load("src/content/Framebuffers/screen_shader.vs.glsl", "src/content/Framebuffers/screen_shader.fs.glsl");

	// cube texture
	cubeTexture.load("resources/textures/container2.png");
	cubeTexture.Type = Texture::TYPE::DIFFUSE;

	// initialize cube meshes
	cubes = std::vector<Cube>(3);
	for (auto& cube : cubes) {
		cube.pShader = &sceneShader;
		cube.Textures.push_back(cubeTexture);
	}

	// quad for screen
	screenQuad.pShader = &screenShader;		// screenShader not used directly in screenQuad

	// models
	backpack.loadModel("resources/models/backpack/backpack.obj");
	backpack.pShader = &sceneShader;
	backpack.init();
}

void FrameBuffersScene::setCamera(FlyCamera* cam)
{
	camera = cam;
}

void FrameBuffersScene::drawCurrent()
{
	if (camera == nullptr) {
		return;
	}

	// draw scene to framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST);

	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// draw the scene(cubes)
	sceneShader.use();
	model = glm::mat4(1.0f);
	sceneShader.setMat4("model", model);
	sceneShader.setMat4("view", camera->getViewMatrix());
	sceneShader.setMat4("projection", camera->getProjectionMatrix());

	backpack.draw();

	for (int i = 0; i < cubes.size(); i++) {
		model *= glm::translate(glm::vec3(2.0f, 0.0f, 2.0f));
		sceneShader.setMat4("model", model);
		cubes[i].draw();
	}




	// restore to defaults
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);		// ensure quad renders in front of everything else
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw to screen shader
	screenShader.use();
	glBindVertexArray(screenQuad.VAO);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void FrameBuffersScene::updateCurrent(float dt)
{
}
