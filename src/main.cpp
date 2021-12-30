#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "ShaderProgram.h"
#include "Texture.h"
#include "scene/SceneNode.h"

#include "content/SimpleTriangle.h"
#include "content/TexturedRectangle.h"


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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Simple Window", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);		// state machine, set current context window

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad.\n";
		return -1;
	}

	glViewport(0, 0, 1280, 720);	// lower left corner, 1280 x  720
	glfwSetFramebufferSizeCallback(window, frameResizeCallback);

	ShaderProgram simpleShader;
	simpleShader.load("shaders/simple_vs.glsl", "shaders/simple_fs.glsl");

	SceneNode sceneGraph;

	auto simpleTriangle = std::make_unique<SimpleTriangle>();
	simpleTriangle->init();
	//sceneGraph.attachChild(std::move(simpleTriangle));

	auto texturedRectangle = std::make_unique<TexturedRectangle>();
	texturedRectangle->setShaderProgram(simpleShader.getID());
	texturedRectangle->init();
	sceneGraph.attachChild(std::move(texturedRectangle));


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		//render();
		simpleShader.use();
		sceneGraph.draw();

		glfwSwapBuffers(window);		// swap color buffer for rendering to output screen, double buffer 
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}