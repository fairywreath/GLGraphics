#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shading/ShaderProgram.h"
#include "shading/Texture.h"
#include "scene/SceneNode.h"
#include "scene/Camera.h"
#include "core/Window.h"
#include "core/CameraController.h"
#include "mesh/Model.h"

#include "content/SimpleTriangle.h"
#include "content/TexturedRectangle.h"
#include "content/RotatingCube.h"
#include "content/LightingScene.h"
#include "content/LightingScene2.h"
#include "content/LightingScene3.h"
#include "content/Framebuffers/FrameBuffersScene.h"




/* glfw callbacks */
void frameResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();

	Window window(1600, 900, "Simple Window");
	window.init();
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad.\n";
		return -1;
	}

	glViewport(0, 0, window.getWidth(), window.getHeight());	
	glfwSetFramebufferSizeCallback(window.getWindowHandle(), frameResizeCallback); 

	SceneNode sceneGraph;
	FlyCamera flyCam((float)1600 / (float)900);
	FlyCameraController camCtrl(&window, &flyCam);

	auto lightingScene = std::make_unique<LightingScene3>();
	lightingScene->init();
	lightingScene->setCamera(&flyCam);
	//sceneGraph.attachChild(std::move(lightingScene));

	float currentFrame;
	float deltaTime = 0.f;
	float lastFrame = 0.f;

	ShaderProgram modelShader("shaders/model_loading.vs.glsl", "shaders/model_loading.fs.glsl");

	//Model backpack("resources/models/backpack/backpack.obj");
	//backpack.pShader = &modelShader;
	//backpack.init();

	//Model sponza("resources/models/sponza/sponza.obj");
	//sponza.pShader = &modelShader;
	//sponza.init();

	glm::mat4 model = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);		// default depth test, discard higher z values

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);		// enable writing to stencil buffer, set all 1s
	glStencilFunc(GL_EQUAL, 0, 0xFF);		// function for pass or fail
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);			// action to take if pass/fail; this is the default, do not replace stencil buffer

	// blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// faceculling
/*	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);	*/	
	
	// face to cut/cull
	glFrontFace(GL_CCW);		// winding order of front face, by defaut CCW

	FrameBuffersScene fboScene;
	fboScene.init();
	fboScene.setCamera(&flyCam);

	window.setCursorMode(GLFW_CURSOR_DISABLED);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.shouldClose())
	{
		currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		processInput(window.getWindowHandle());
		camCtrl.update(deltaTime);
		flyCam.update(deltaTime);

		fboScene.draw();

		//modelShader.use();
		//modelShader.setMat4("model", glm::mat4(1.0f));
		//modelShader.setMat4("projection", flyCam.getProjectionMatrix());
		//modelShader.setMat4("view", flyCam.getViewMatrix());


		//backpack.update(deltaTime);
		//modelShader.setMat4("model", backpack.getTransform());
		//backpack.draw();

		//sponza.setPosition(glm::vec3(0.0f, -4.f, 0.0f));
		//sponza.setScale(glm::vec3(0.04f, 0.04f, 0.04f));
		//sponza.update(deltaTime);
		//modelShader.setMat4("model", sponza.getTransform());
		//sponza.draw();

		//sceneGraph.draw();
		//sceneGraph.update(deltaTime);

		window.nextFrame();
	}

	window.destroy();

	glfwTerminate();

	return 0;
}