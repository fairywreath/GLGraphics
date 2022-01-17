#include "SceneNode.h"

#include <glm/gtx/matrix_decompose.hpp>

#include <iostream>
#include <cassert>

SceneNode::SceneNode() :
	mParent(nullptr),
	mGlobalTransform(1.0f),
	mParentGlobalTransform(1.0f),
	mGlobalTransformDirty(false)
{
}

SceneNode::~SceneNode()
{
	for (auto& child : mChildren) {
		child->mParent = nullptr;
	}

	if (mParent != nullptr) {
		mParent->detachChild(*this);
	}
}

void SceneNode::init()
{
}

void SceneNode::draw()
{
	drawCurrent();
	drawChildren();
}

void SceneNode::update(float dt)
{
	forceComputeTransform();
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::attachChild(NodePtr child)
{
	child->mParent = this;
	child->setParentGlobalTransform(getGlobalTransform());
	mChildren.push_back(std::move(child));		// move and attach chi
}


SceneNode::NodePtr SceneNode::detachChild(const SceneNode& child)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](NodePtr& p) -> bool { return p.get() == &child; });	


	assert(found != mChildren.end());

	NodePtr result = std::move(*found);			
	result->mParent = nullptr;
	result->setParentGlobalTransform(glm::mat4(1.f));
	mChildren.erase(found);				

	std::cout << "detached child\n";

	return result;
}


SceneNode* SceneNode::getParent() const
{
	return mParent;
}

SceneNode* SceneNode::getRoot() 
{
	SceneNode* root = this;
	while (root->mParent != nullptr) {
		root = root->mParent;
	}
	
	return root;
}

const glm::mat4& SceneNode::getGlobalTransform()
{
	return mGlobalTransform;
}

void SceneNode::forceComputeTransform()
{
	if (getShouldUpdateTransform()) {
		updateWorldMatrix();
		mGlobalTransformDirty = true;
	}  
	if (mGlobalTransformDirty) {
		mGlobalTransform = mParentGlobalTransform * getTransform();
	}

	for (auto& child : mChildren) {
		if (mGlobalTransformDirty) {
			child->setParentGlobalTransform(getGlobalTransform());
		}
	}

	setDoneUpdateTransform();
	mGlobalTransformDirty = false;
}

void SceneNode::decomposeGlobalMatrix(glm::vec3& position, glm::quat& rotation, glm::vec3& scale)
{
	auto& matrix = getGlobalTransform();
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(matrix, scale, rotation, position, skew, perspective);
}

glm::vec3 SceneNode::getAbsolutePosition()
{
	auto& matrix = getGlobalTransform();
	glm::vec4 pos = matrix * glm::vec4(0, 0, 0, 1.f);
	return glm::vec3(pos);
}

void SceneNode::drawCurrent()
{
}

void SceneNode::updateCurrent(float dt)
{

}


void SceneNode::drawChildren()
{
	for (auto& node : mChildren)
	{
		node->draw();
	}
}

void SceneNode::updateChildren(float dt)
{
	for (auto& node : mChildren)
	{
		node->update(dt);
	}
}

void SceneNode::setParentGlobalTransform(const glm::mat4 transform)
{
	mParentGlobalTransform = transform;
	mGlobalTransformDirty = true;
}
