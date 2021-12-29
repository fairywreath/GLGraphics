#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>


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


/* error checking and logging */
int success;
char infoLog[512];

/* shader compilation */
GLuint shaderProgram;

void compileShaders() {
	GLuint vs;
	GLuint fs;

	const char* vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShaderSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR: Vertex Shader Compilation Failed\n" << infoLog << "\n";
	}


	const char* fragmentShaderSource = "#version 460 core\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = vec4(0.7f, 0.7f, 0.1f, 1.0f);\n"
		"}\n";

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShaderSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment Shader Compilation Failed\n" << infoLog << "\n";
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: Shader Program Linking Failed\n" << infoLog << "\n";
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vs);
	glDeleteShader(fs);
}


/* simple triangle */
GLuint triangleVBO;
GLuint triangleVAO;

float triangleVertices[] = {
	0.5f , 0.5f, 0.0f,
	0.0f , 0.5f, 0.0f,
	0.5f , 0.0f, 0.0f
};

void setupTriangle() {
	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);

	glGenBuffers(1, &triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


/* rectangle using indexed drawing */
GLuint rectangleVBO;
GLuint rectangleEBO;
GLuint rectangleVAO;

float rectangleVertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int rectangleIndices[] = {
	0, 1, 3,	// first triangle: top right, top left, bottom right
	1, 2, 3		// second triangle: bottom right, bottom left, top left
};

void setupRectangle() {
	glGenVertexArrays(1, &rectangleVAO);
	glBindVertexArray(rectangleVAO);

	glGenBuffers(1, &rectangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &rectangleEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleEBO);	// NOTE: EBO is binded to the VAO here
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);
	/* NOTE: a VAO can only be binded with 1 index buffering or EBO */

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// NOTE: VBO binded to VAO here
	glEnableVertexAttribArray(0);


	// unbind, except for EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void render() {
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

	//glBindVertexArray(triangleVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(rectangleVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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


	compileShaders();
	setupTriangle();
	setupRectangle();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		render();

		glfwSwapBuffers(window);		// swap color buffer for rendering to output screen, double buffer 
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}