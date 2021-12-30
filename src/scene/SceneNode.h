#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include <memory>

class SceneNode
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


private:	
	virtual void drawCurrent();
	virtual void updateCurrent(float dt);

	void drawChildren();
	void updateChildren(float dt);

private:
	std::vector<NodePtr> mChildren;
	SceneNode* mParent;

};

#endif

