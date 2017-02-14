#include "TreeNode.h"

USING_NS_CC;


TreeNode* TreeNode::createTreeNode()
{
	auto treeNode = new TreeNode();
	treeNode->initTreeNode();

	return treeNode;
}

void TreeNode::initTreeNode()
{
	auto treeTrunk = Sprite::create("trunk.png");
	this->addChild(treeTrunk, 0, "trunk");

	auto treeBranch = Sprite::create("branch.png");
	this->addChild(treeBranch, 1, "branch");
	this->setContentSize(Size(treeTrunk->getContentSize().width, treeTrunk->getContentSize().height));
}

void TreeNode::setTreeBranchDirection(TreeBranchDirection direction)
{
	_TreeBranchDirection = direction;
	
	auto treeTrunk = this->getChildByName("trunk");
	auto treeBranch = this->getChildByName("branch");
	
	treeBranch->setVisible(direction != MIDDLE);
	switch (direction)
	{
	case MIDDLE:
		break;
	case LEFT:
		{
			treeBranch->setScaleX(-1.0f);
			treeBranch->setPositionX(-treeTrunk->getContentSize().width);
		}
		break;
	case RIGHT:
		{
			treeBranch->setScaleX(1.0f);
			treeBranch->setPositionX(treeTrunk->getContentSize().width);
		}
		break;
	default:
		break;
	}
}

TreeBranchDirection TreeNode::getTreeBranchDirection()
{
	return _TreeBranchDirection;
}


