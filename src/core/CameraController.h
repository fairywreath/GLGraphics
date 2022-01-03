#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "../scene/Camera.h"
#include "Window.h"

class FlyCameraController : public WindowObserver
{
public:
	FlyCameraController(Window* window, FlyCamera* camera);

	void update(float dt);

	void onCursorPos(double x, double y) override;
	void onMouseButton(int key, int action, int mods) override;
	void onKey(int key, int scancode, int action, int mods) override;
	void onResize(int width, int height) override;
	void onScroll(double xoffset, double yoffset) override;

	void setCameraSpeed(float speed);

private:
	float mCameraSpeed;
	float mBaseCameraSpeed;

	float mRollSensitivity;	// degrees rolled for every turn

	bool mFirstMouse;
	float mLastX;
	float mLastY;
	float mSensitivity;

	bool mGoForward = false;
	bool mGoBackward = false;
	bool mGoLeft = false;
	bool mGoRight = false;
	bool mGoUp = false;
	bool mGoDown = false;

	// should camera be owned by controller, updated by controller?
	Window* mWindow;
	FlyCamera* mCamera;
};


#endif