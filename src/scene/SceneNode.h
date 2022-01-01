#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "Transformable.h"

class SceneNode : public Transformable
{
public:
	using NodePtr = std::unique_ptr<SceneNode>;

	SceneNode();
	virtual ~SceneNode();

	SceneNode(const SceneNode&) = delete;
	SceneNode& operator=(const SceneNode&) = delete;

	virtual void init();
	void draw();
	void update(float dt);

	void attachChild(NodePtr child);
	NodePtr detachChild(const SceneNode& child);

	SceneNode* getParent() const;
	SceneNode* getRoot();

	const glm::mat4& getGlobalTransform();
	void forceComputeTransform();

	void decomposeGlobalMatrix(glm::vec3& position, glm::quat& rotation, glm::vec3& scale);
	glm::vec3 getAbsolutePosition();

private:	
	virtual void drawCurrent();
	virtual void updateCurrent(float dt);

	void drawChildren();
	void updateChildren(float dt);

	void setParentGlobalTransform(const glm::mat4 transform);

protected:
	glm::mat4 mGlobalTransform;
	glm::mat4 mParentGlobalTransform;
	bool mGlobalTransformDirty;

private:
	std::vector<NodePtr> mChildren;
	SceneNode* mParent;

};

#endif

