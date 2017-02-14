#include "TreeModel.h"

USING_NS_CC;


static TreeModel* g_pTreeModel = nullptr;
TreeModel* TreeModel::getInstance()
{
	if (!g_pTreeModel)
	{
		g_pTreeModel = new TreeModel();
		g_pTreeModel->initTree();
		g_pTreeModel->setScale(0.5f);
	}

	return g_pTreeModel;
}

void TreeModel::initTree()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto treeBase = Sprite::create("base.png");
	treeBase->setPosition(3, treeBase->getContentSize().height/2.0f);
	this->addChild(treeBase);

	_treeTrunk = Node::create();
	_treeTrunk->setPositionY(treeBase->getContentSize().height);
	this->addChild(_treeTrunk);

	createTreeModel();

	scheduleUpdate();
}

void TreeModel::createTreeModel()
{
	_treeTrunk->removeAllChildren();
	_vecTreeQueue.clear();
	_vecTreeCache.clear();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float yPos = 0;
	bool bTreeBase = true;

	while (visibleSize.height*2 > yPos)
	{
		auto treeNode = TreeNode::createTreeNode();
		treeNode->setTreeBranchDirection(this->getTreeBranchDirection());
		if (bTreeBase)
		{
			yPos += treeNode->getContentSize().height/2.0f;
			bTreeBase = false;
		}
		else
		{
			yPos += treeNode->getContentSize().height;
		}

		treeNode->setPositionY(yPos);
		_treeTrunk->addChild(treeNode);
		_vecTreeQueue.pushBack(treeNode);
	}
}

TreeNode* TreeModel::getTreeHeadNode()
{
	return nullptr;
}

TreeNode* TreeModel::deleteTreeHeadNode()
{
	auto treeNode = _vecTreeQueue.at(0);
	_vecTreeQueue.erase(0);
	_vecTreeCache.pushBack(treeNode);

	TreeNode* pNextTreeNode;
	if (_vecTreeCache.size() > 10)
	{
		pNextTreeNode = _vecTreeCache.at(0);
		_treeTrunk->removeChild(pNextTreeNode);
		_vecTreeCache.erase(0);
		pNextTreeNode->setPositionX(0.0f);
		pNextTreeNode->setRotation3D(Vec3(0,0,0));
	}
	else
	{
		pNextTreeNode = TreeNode::createTreeNode();
	}

	_treeTrunk->addChild(pNextTreeNode);
	pNextTreeNode->setTreeBranchDirection(this->getTreeBranchDirection());
	_vecTreeQueue.pushBack(pNextTreeNode);
	_treeTrunk->reorderChild(treeNode, _treeTrunk->getChildrenCount()+10);
	auto head = _vecTreeQueue.at(0);
	head->runAction(Sequence::create(MoveTo::create(0.06, Vec2(0, treeNode->getPositionY())), nullptr));

	return treeNode;
}

TreeBranchDirection TreeModel::getFirstTreeBranchDirection()
{
	return _vecTreeQueue.front()->getTreeBranchDirection();
}

TreeBranchDirection TreeModel::getTreeBranchDirection()
{
	auto bBranch = CCRANDOM_0_1()*10 < 7;
	if (_vecTreeQueue.size() == 0)
		return MIDDLE;

	if (!bBranch)
		return MIDDLE;

	auto proTree = _vecTreeQueue.at(_vecTreeQueue.size()-1);
	switch (proTree->getTreeBranchDirection())
	{
	case MIDDLE:
		return getTreeBranchDirectionAgain();
		break;
	case RIGHT:
		return (CCRANDOM_0_1()*10 < 5) ? MIDDLE : RIGHT;
		break;
	case LEFT:
		return (CCRANDOM_0_1()*10 < 5) ? MIDDLE : LEFT;
		break;
	default:
		return MIDDLE;
		break;
	}
}

TreeBranchDirection TreeModel::getTreeBranchDirectionAgain()
{
	if (_vecTreeQueue.size() < 2)
		return MIDDLE;

	auto proTree = _vecTreeQueue.at(_vecTreeQueue.size()-2);
	switch (proTree->getTreeBranchDirection())
	{
	case MIDDLE:
		return (CCRANDOM_0_1()*10 < 4) ? LEFT : RIGHT;
		break;
	case RIGHT:
		return (CCRANDOM_0_1()*10 < 6) ? LEFT : RIGHT;
		break;
	case LEFT:
		return (CCRANDOM_0_1()*10 < 6) ? RIGHT : LEFT;
		break;
	default:
		return MIDDLE;
		break;
	}
}

void TreeModel::Reset()
{
	createTreeModel();
}

void TreeModel::update(float time)
{
	for (int index = 1; index < _vecTreeQueue.size(); ++index)
	{
		auto proTree = _vecTreeQueue.at(index-1);
		auto tree = _vecTreeQueue.at(index);
		tree->setPositionY(proTree->getPositionY() + proTree->getContentSize().height);
	}
}





