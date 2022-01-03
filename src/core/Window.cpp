#include "Window.h"

#include <iostream>
#include <cassert>


Window::Window(int width, int height, const std::string& title) :
    mDefaultWidth(width),
    mDefaultHeight(height),
    mTitle(title),
    mWindow(nullptr)
{
}

Window::~Window()
{
    destroy();
}

bool Window::init()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(mDefaultWidth, mDefaultHeight, mTitle.c_str(), nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(mWindow, this);

    glfwSetCursorPosCallback(mWindow, onCursorPosCallback);
    glfwSetMouseButtonCallback(mWindow, onMouseButtonCallback);
    glfwSetKeyCallback(mWindow, onKeyCallback);
    glfwSetFramebufferSizeCallback(mWindow, onResizeCallback);
    glfwSetScrollCallback(mWindow, onScrollCallback);

    setContextCurrent();
    return true;
}

void Window::destroy()
{
    if (mWindow != nullptr)
    {
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
    }
}

void Window::close()
{
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
}

void Window::nextFrame()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

bool Window::isContextCurrent() const
{
    return (glfwGetCurrentContext() == mWindow);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(mWindow);
}

void Window::setContextCurrent()
{
    glfwMakeContextCurrent(mWindow);
}

void Window::setCursorMode(int mode)
{
    glfwSetInputMode(mWindow, GLFW_CURSOR, mode);
}

glm::dvec2 Window::getCursorPosition() const
{
    glm::dvec2 ret;
    glfwGetCursorPos(mWindow, &ret.x, &ret.y);
    return ret;
}

void Window::addObserver(WindowObserver* observer)
{
    mObservers.push_back(observer);
}

void Window::removeObserver(WindowObserver* observer)
{
    auto found = std::find_if(mObservers.begin(), mObservers.end(),
        [&](WindowObserver* p) -> bool { return p == observer; });


    assert(found != mObservers.end());

    mObservers.erase(found);
}

GLFWwindow* Window::getWindowHandle() const
{
    return mWindow;
}

int Window::getWidth() const
{
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return width;
}

int Window::getHeight() const
{
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return height;
}

glm::ivec2 Window::getDimensions() const
{
    glm::ivec2 ret;
    glfwGetWindowSize(mWindow, &ret.x, &ret.y);
    return ret;
}

void Window::onCursorPos(double x, double y)
{
    for (auto observer : mObservers)
    {
        observer->onCursorPos(x, y);
    }
}

void Window::onMouseButton(int key, int action, int mods)
{
    for (auto observer : mObservers)
    {
        observer->onMouseButton(key, action, mods);
    }
}

void Window::onKey(int key, int scancode, int action, int mods)
{
    for (auto observer : mObservers)
    {
        observer->onKey(key, scancode, action, mods);
    }
}

void Window::onResize(int width, int height)
{
    for (auto observer : mObservers)
    {
        observer->onResize(width, height);
    }
}

void Window::onScroll(double xoffset, double yoffset)
{
    for (auto observer : mObservers)
    {
        observer->onScroll(xoffset, yoffset);
    }
}


void Window::onCursorPosCallback(GLFWwindow* window, double x, double y)
{
    static_cast<Window*>(glfwGetWindowUserPointer(window))->onCursorPos(x, y);
}

void Window::onMouseButtonCallback(GLFWwindow* window, int key, int action, int mods)
{
    static_cast<Window*>(glfwGetWindowUserPointer(window))->onMouseButton(key, action, mods);
}

void Window::onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static_cast<Window*>(glfwGetWindowUserPointer(window))->onKey(key, scancode, action, mods);
}

void Window::onResizeCallback(GLFWwindow* window, int width, int height)
{
    static_cast<Window*>(glfwGetWindowUserPointer(window))->onResize(width, height);
}

void Window::onScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    static_cast<Window*>(glfwGetWindowUserPointer(window))->onScroll(xoffset, yoffset);
}
