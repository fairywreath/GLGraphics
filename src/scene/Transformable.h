#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class Transformable
{
public:
	Transformable();
	virtual ~Transformable();

	void setPosition(const glm::vec3& pos);
	void setScale(const glm::vec3& scale);
	void setRotationQuaternion(const glm::quat& rotationQuaternion);

	const glm::vec3& getPosition() const;
	const glm::vec3& getScale() const;
	const glm::quat& getRotationQuaternion() const;

	const glm::mat4& getTransform() const;

	bool getShouldUpdateTransform() const;
	void setDoneUpdateTransform();

	// todo
	void setOrigin(const glm::vec3& origin);
	const glm::vec3& getOrigin() const;

protected:
	void updateWorldMatrix();
	void updatePositionMatrix();
	void updateScaleMatrix();
	void updateRotationMatrix();

private:
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::quat mRotationQuaternion;

	// cached
	bool mShouldUpdateModelMatrix;
	glm::mat4 mModelMatrix;
	glm::mat4 mPositionMatrix;
	glm::mat4 mScaleMatrix;
	glm::mat4 mRotationMatrix;

	// todo
	glm::vec3 mOrigin;
	glm::mat4 mOriginMatrix;

};


#endif