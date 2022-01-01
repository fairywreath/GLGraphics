#include "Transformable.h"

Transformable::Transformable() :
	mModelMatrix(glm::mat4(1.0f)),
	mPositionMatrix(glm::mat4(1.0f)),
	mRotationMatrix(glm::mat4(1.0f)),
	mScaleMatrix(glm::mat4(1.0f)),
	mOriginMatrix(glm::mat4(1.0f)),
	mPosition(glm::vec3(0)),
	mRotationQuaternion(glm::quat(0, 0, 0, 1)),
	mScale(glm::vec3(1.f)),
	mOrigin(glm::vec3(0.f)),
	mShouldUpdateModelMatrix(false)
{
}

Transformable::~Transformable()
{
}

void Transformable::setPosition(const glm::vec3& pos)
{
	mPosition = pos;
	updatePositionMatrix();
	mShouldUpdateModelMatrix = true;
}

void Transformable::setScale(const glm::vec3& scale)
{
	mScale = scale;
	updateScaleMatrix();
	mShouldUpdateModelMatrix = true;
}

void Transformable::setRotationQuaternion(const glm::quat& rotationQuaternion)
{
	mRotationQuaternion = rotationQuaternion;
	updateRotationMatrix();
	mShouldUpdateModelMatrix = true;
}

void Transformable::setOrigin(const glm::vec3& origin)
{
	// todo
}

const glm::vec3& Transformable::getPosition() const
{
	return mPosition;
}

const glm::vec3& Transformable::getScale() const
{
	return mScale;
}

const glm::quat& Transformable::getRotationQuaternion() const
{
	return mRotationQuaternion;
}

const glm::vec3& Transformable::getOrigin() const
{
	return mOrigin;
}

const glm::mat4& Transformable::getTransform() const
{
	return mModelMatrix;
}

bool Transformable::getShouldUpdateTransform() const
{
	return mShouldUpdateModelMatrix;
}

void Transformable::setDoneUpdateTransform()
{
	mShouldUpdateModelMatrix = false;
}

void Transformable::updateWorldMatrix()
{
	mModelMatrix = mPositionMatrix * mRotationMatrix * mScaleMatrix;
}

void Transformable::updatePositionMatrix()
{
	mPositionMatrix = glm::translate(mPosition);
}

void Transformable::updateScaleMatrix()
{
	mScaleMatrix = glm::scale(mScale);
}

void Transformable::updateRotationMatrix()
{
	mRotationMatrix = glm::toMat4(mRotationQuaternion);
}
