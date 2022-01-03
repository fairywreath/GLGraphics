#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class CameraBase
{
public:
	virtual const glm::mat4& getViewMatrix() = 0;
	virtual const glm::mat4& getProjectionMatrix() = 0;

	virtual const glm::vec3& getPosition() const = 0;
	virtual const glm::vec3& getDirection() const = 0;

	virtual void update(float dt) = 0;

};

class FlyCamera : public CameraBase
{
public:
	FlyCamera(float aspectRatio);

	const glm::mat4& getViewMatrix() override;
	const glm::mat4& getProjectionMatrix() override;

	const glm::vec3& getPosition() const override;
	const glm::vec3& getDirection() const override;

	void update(float dt) override;

	void walk(float amount);
	void strafe(float amount);
	void lift(float amount);

	void zoom(float amount);		// change fov

	// change to set direction later on?
	void setYaw(float yaw);
	void setPitch(float pitch);
	float getYaw() const;
	float getPitch() const;

private:
	void computeViewMatrix();
	void computeProjectionMatrix();

private:
	glm::mat4 mView;
	glm::mat4 mProjection;

	glm::vec3 mPosition;
	glm::vec3 mFront;	// camera direction
	glm::vec3 mUp;


	float mYaw;
	float mPitch;
	float mFov;
	float mAspectRatio;

	bool mShouldUpdateView;
	bool mShouldUpdateProjection;
};


#endif