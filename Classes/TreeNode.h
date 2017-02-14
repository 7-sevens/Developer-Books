/** @class  TreeNode
  * @brief  树节点
  * @author sevens
  * @date   2016/10/01
  * @blog   http://www.developer1024.com/
  */

#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#include "cocos2d.h"


// 节点树枝方向枚举
enum TreeBranchDirection
{
	MIDDLE = 0,
	LEFT,
	RIGHT,
};

class TreeNode : public cocos2d::Node
{
public:
	static TreeNode* createTreeNode();

	/**
	* 设置节点树枝方向
	* @param[in] direction 节点树枝方向
	* @return void	无返回值
	*/
	void setTreeBranchDirection(TreeBranchDirection direction);
	
	/**
	* 获取节点树枝方向
	* @return TreeBranchDirection	节点树枝方向
	*/
	TreeBranchDirection getTreeBranchDirection();

protected:
	/**
	* 初始化树节点
	* @return void	无返回值
	*/
	void initTreeNode();


private:
	TreeBranchDirection _TreeBranchDirection;
};

#endif // __TREE_NODE_H__