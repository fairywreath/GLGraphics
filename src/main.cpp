#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "ShaderProgram.h"
#include "Texture.h"
#include "scene/SceneNode.h"
#include "core/Window.h"

#include "content/SimpleTriangle.h"
#include "content/TexturedRectangle.h"
#include "content/RotatingCube.h"


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

	ShaderProgram simpleShader;
	simpleShader.load("shaders/simple_vs.glsl", "shaders/simple_fs.glsl");

	SceneNode sceneGraph;

	auto simpleTriangle = std::make_unique<SimpleTriangle>();
	simpleTriangle->init();
	//sceneGraph.attachChild(std::move(simpleTriangle));

	auto texturedRectangle = std::make_unique<TexturedRectangle>();
	texturedRectangle->setShaderProgram(simpleShader.getID());
	texturedRectangle->init();
	//sceneGraph.attachChild(std::move(texturedRectangle));

	auto rotatingCube = std::make_unique<RotatingCube>();
	rotatingCube->init();
	sceneGraph.attachChild(std::move(rotatingCube));


	while (!window.shouldClose())
	{
		processInput(window.getWindowHandle());
		
		//render();
		//simpleShader.use();
		sceneGraph.draw();
		sceneGraph.update((float)glfwGetTime());

		window.nextFrame();
	}

	glfwTerminate();

	return 0;
}