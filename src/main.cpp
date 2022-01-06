#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "shading/ShaderProgram.h"
#include "shading/Texture.h"
#include "scene/SceneNode.h"
#include "scene/Camera.h"
#include "core/Window.h"
#include "core/CameraController.h"

#include "content/SimpleTriangle.h"
#include "content/TexturedRectangle.h"
#include "content/RotatingCube.h"
#include "content/LightingScene.h"


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

	auto lightingScene = std::make_unique<LightingScene>();
	lightingScene->init();
	lightingScene->setCamera(&flyCam);
	sceneGraph.attachChild(std::move(lightingScene));

	float currentFrame;
	float deltaTime = 0.f;
	float lastFrame = 0.f;

	window.setCursorMode(GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	while (!window.shouldClose())
	{
		currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window.getWindowHandle());
		camCtrl.update(deltaTime);
		flyCam.update(deltaTime);


		sceneGraph.draw();
		sceneGraph.update(deltaTime);

		window.nextFrame();
	}

	window.destroy();

	glfwTerminate();

	return 0;
}