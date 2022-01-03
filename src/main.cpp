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


/* glfw callbacks */
void frameResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

FlyCameraController* flyCCp;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	flyCCp->onCursorPos(xpos, ypos);
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

	ShaderProgram simpleShader;
	simpleShader.load("shaders/simple_vs.glsl", "shaders/simple_fs.glsl");

	SceneNode sceneGraph;
	FlyCamera flyCam((float)1600 / (float)900);
	FlyCameraController camCtrl(&window, &flyCam);

	ShaderProgram shader;
	shader.load("shaders/transform_vs.glsl", "shaders/simple_fs.glsl");
	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);
	
	auto rotatingCube = std::make_unique<RotatingCube>();
	rotatingCube->init();
	rotatingCube->setCamera(&flyCam);
	
	auto rotatingCube2 = std::make_unique<RotatingCube>();
	rotatingCube2->init();
	rotatingCube2->setCamera(&flyCam);
	rotatingCube2->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	rotatingCube2->setScale(glm::vec3(0.25f, 0.25f, 0.25f));

	rotatingCube->setShaderProgram(&shader);
	rotatingCube2->setShaderProgram(&shader);


	rotatingCube->attachChild(std::move(rotatingCube2));
	sceneGraph.attachChild(std::move(rotatingCube));

	float currentFrame;
	float deltaTime = 0.f;
	float lastFrame = 0.f;

	flyCCp = &camCtrl;
	//glfwSetCursorPosCallback(window.getWindowHandle(), mouse_callback);


	window.setCursorMode(GLFW_CURSOR_DISABLED);

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


		shader.setMat4("view", flyCam.getViewMatrix());
		shader.setMat4("projection", flyCam.getProjectionMatrix());

		sceneGraph.draw();
		sceneGraph.update(deltaTime);


		window.nextFrame();
	}

	window.destroy();

	glfwTerminate();

	return 0;
}