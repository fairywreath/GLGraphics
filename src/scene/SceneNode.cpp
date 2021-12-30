#include "SceneNode.h"

#include <cassert>

SceneNode::SceneNode() :
	mParent(nullptr)
{
}

SceneNode::~SceneNode()
{
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
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::attachChild(NodePtr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));		// move and attach chi
}


SceneNode::NodePtr SceneNode::detachChild(const SceneNode& child)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](NodePtr& p) -> bool { return p.get() == &child; });	


	assert(found != mChildren.end());

	NodePtr result = std::move(*found);			
	result->mParent = nullptr;
	mChildren.erase(found);				

	return result;
}

SceneNode* SceneNode::getParent() const
{
	return mParent;
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
