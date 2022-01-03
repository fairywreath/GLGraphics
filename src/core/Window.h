#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class WindowObserver
{
public:
	virtual void onCursorPos(double x, double y) = 0;
	virtual void onMouseButton(int key, int action, int mods) = 0;
	virtual void onKey(int key, int scancode, int action, int mods) = 0;
	virtual void onResize(int width, int height) = 0;
	virtual void onScroll(double xoffset, double yoffset) = 0;
};

class Window
{
public:
	Window(int width, int height, const std::string& title);
	virtual ~Window();

	bool init();
	void destroy();
	void close();
	void nextFrame();

	bool isContextCurrent() const;
	bool shouldClose() const;

	void setContextCurrent();
	void setCursorMode(int mode);
	
	glm::dvec2 getCursorPosition() const;

	void addObserver(WindowObserver* observer);
	void removeObserver(WindowObserver* observer);

	GLFWwindow* getWindowHandle() const;

	int getWidth() const;
	int getHeight() const;
	glm::ivec2 getDimensions() const;

private:
	void onCursorPos(double x, double y);
	void onMouseButton(int key, int action, int mods);
	void onKey(int key, int scancode, int action, int mods);
	void onResize(int width, int height);
	void onScroll(double xoffset, double yoffset);

	static void onCursorPosCallback(GLFWwindow* window, double x, double y);
	static void onMouseButtonCallback(GLFWwindow* window, int key, int action, int mods);
	static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void onResizeCallback(GLFWwindow* window, int width, int height);
	static void onScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	std::string mTitle;
	int mDefaultWidth;
	int mDefaultHeight;
	GLFWwindow* mWindow;

	std::vector<WindowObserver*> mObservers;

	static constexpr auto DefaultHeight = 920;
	static constexpr auto DefaultWidth = 1600;
};

#endif

