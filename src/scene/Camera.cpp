#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

FlyCamera::FlyCamera(float aspectRatio) :
	mYaw(0),
	mPitch(0),
	mFront(glm::vec3(0.0f, 0.0f, 0.0f)),
	mUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	mPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	mFov(45.f),
	mAspectRatio(aspectRatio),
	mProjection(glm::mat4(1.0f)),
	mView(glm::mat4(1.0f)),
	mShouldUpdateView(false)
{
	computeViewMatrix();
	computeProjectionMatrix();
}


const glm::mat4& FlyCamera::getViewMatrix()
{
	return mView;
}

const glm::mat4& FlyCamera::getProjectionMatrix()
{
	return mProjection;
}

const glm::vec3& FlyCamera::getPosition() const
{
	return mPosition;
}

const glm::vec3& FlyCamera::getDirection() const
{
	return mFront;
}

void FlyCamera::update(float dt)
{
	if (mShouldUpdateView) {
		computeViewMatrix();
		mShouldUpdateView = false;
	}

	if (mShouldUpdateProjection) {
		computeProjectionMatrix();
		mShouldUpdateProjection = false;
	}
}

void FlyCamera::walk(float amount)
{
	mPosition += amount * mFront;
	mShouldUpdateView = true;
}

void FlyCamera::strafe(float amount)
{
	mPosition += glm::normalize(glm::cross(mFront, mUp)) * amount;
	mShouldUpdateView = true;
}

void FlyCamera::lift(float amount)
{
	mPosition += amount * mUp;
	mShouldUpdateView = true;
}

void FlyCamera::zoom(float amount)
{
	mFov += amount;
	if (mFov < 1.0f)
	{
		mFov = 1.0f;
	}
	if (mFov > 45.0f)
	{
		mFov = 45.0f;
	}

	mShouldUpdateProjection = true;
}

void FlyCamera::setYaw(float yaw)
{
	mYaw = yaw;
	mShouldUpdateView = true;
}

void FlyCamera::setPitch(float pitch)
{
	mPitch = pitch;
	mShouldUpdateView = true;
}

float FlyCamera::getYaw() const
{
	return mYaw;
}

float FlyCamera::getPitch() const
{
	return mPitch;
}

void FlyCamera::computeViewMatrix()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	direction.y = sin(glm::radians(mPitch));
	direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	
	mFront = glm::normalize(direction);
	mView = glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void FlyCamera::computeProjectionMatrix()
{
	mProjection = glm::perspective(glm::radians(mFov), mAspectRatio, 0.1f, 10000000.f);		// last two args are near and far clip planes
}
