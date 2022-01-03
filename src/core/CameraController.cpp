#include "CameraController.h"

#include <iostream>

FlyCameraController::FlyCameraController(Window* window, FlyCamera* camera) :
	mWindow(window),
	mCamera(camera),
	mLastX(0.f),
	mLastY(0.f),
	mCameraSpeed(0),
	mBaseCameraSpeed(2.5f),
	mFirstMouse(true),
	mSensitivity(0.01f),
	mRollSensitivity(0.01f)
{
	if (window == nullptr || camera == nullptr) {
		std::cout << "Invalid arguments for camera controller.";
	}

	if (window != nullptr) {
		window->addObserver(this);
	}
}

void FlyCameraController::update(float dt)
{
	mCameraSpeed = dt * mBaseCameraSpeed;

	if (mGoForward)
	{
		mCamera->walk(mCameraSpeed);
	}

	if (mGoBackward)
	{
		mCamera->walk(-mCameraSpeed);
	}

	if (mGoLeft)
	{
		mCamera->strafe(-mCameraSpeed);
	}

	if (mGoRight)
	{
		mCamera->strafe(mCameraSpeed);
	}

	if (mGoUp) 
	{
		mCamera->lift(mCameraSpeed);
	}

	if (mGoDown) 
	{
		mCamera->lift(-mCameraSpeed);
	}
}

void FlyCameraController::onCursorPos(double x, double y)
{
	if (mFirstMouse)
	{
		mLastX = (float)x;
		mLastY = (float)y;
		mFirstMouse = false;
	}

	float xoffset = (float)(x - mLastX);
	float yoffset = (float)(mLastY - y);
	mLastX = (float)x;
	mLastY = (float)y;

	xoffset *= mSensitivity;
	yoffset *= mSensitivity;

	mCamera->setYaw(mCamera->getYaw() + xoffset);
	mCamera->setPitch(mCamera->getPitch() + yoffset);

	if (mCamera->getPitch() > 89.0f)
	{
		mCamera->setPitch(89.0f);
	}
	if (mCamera->getYaw() < -89.0f)
	{
		mCamera->setYaw(-89.0f);
	}
}

void FlyCameraController::onMouseButton(int key, int action, int mods)
{
}

void FlyCameraController::onKey(int key, int scancode, int action, int mods)
{
	bool flag = false;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		flag = true;
	}
	else if (action == GLFW_RELEASE)
	{
		flag = false;
	}

	// key events here...
	switch (key)
	{
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		mGoForward = flag;
		break;

	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		mGoBackward = flag;
		break;

	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		mGoLeft = flag;
		break;

	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		mGoRight = flag;
		break;

	case GLFW_KEY_SPACE:
		mGoUp = flag;
		break;

	case GLFW_KEY_X:
		mGoDown = flag;
		break;
	}
	
}

void FlyCameraController::onResize(int width, int height)
{
}

void FlyCameraController::onScroll(double xoffset, double yoffset)
{
	mCamera->zoom((float)-yoffset/2.0f);
}

void FlyCameraController::setCameraSpeed(float speed)
{
	mBaseCameraSpeed = speed;
}
