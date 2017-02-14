/** @class  GameMainScene
  * @brief  树节点
  * @author sevens
  * @date   2016/10/01
  * @blog   http://www.developer1024.com/
  */

#ifndef __TREE_MODEL_H__
#define __TREE_MODEL_H__

#include "cocos2d.h"
#include "TreeNode.h"


class TreeModel : public cocos2d::Layer
{
public:
	static TreeModel* getInstance();

	/**
	* 获取树节点队列头节点
	* @return TreeNode	节点对象
	*/
	TreeNode* getTreeHeadNode();

	/**
	* 删除树节点队列头节点
	* @return TreeNode	节点对象
	*/
	TreeNode* deleteTreeHeadNode();

	/**
	* 获取头节点树枝方向
	* @return TreeBranchDirection	节点树枝方向
	*/
	TreeBranchDirection getFirstTreeBranchDirection();

	/**
	* 重置Tree
	* @return void	无返回值
	*/
	void Reset();

protected:
	/**
	* 初始化Tree
	* @return void	无返回值
	*/
	void initTree();

	/**
	* 创建Tree
	* @return void	无返回值
	*/
	void createTreeModel();

private:
	TreeBranchDirection getTreeBranchDirection();
	TreeBranchDirection getTreeBranchDirectionAgain();

	void update(float time);

private:
	cocos2d::Node*				 _treeTrunk;

	cocos2d::Vector<TreeNode*>	_vecTreeQueue;	//树节点列表	
	cocos2d::Vector<TreeNode*>	_vecTreeCache;	//树节点缓存列表
};

#endif // __TREE_MODEL_H__