/** @class  TimberMan
  * @brief  游戏角色
  * @author sevens
  * @date   2016/10/01
  * @blog   http://www.developer1024.com/
  */

#ifndef __TIMBER_MAN_H__
#define __TIMBER_MAN_H__

#include "cocos2d.h"
#include "TreeModel.h"


class TimberMan : public cocos2d::Node
{
public:
	static TimberMan* createTimberMan();
	void initTimberMan();

	void playAction(TreeBranchDirection direction);

	void setTimberManDie();

	TreeBranchDirection getTimberManDirection();

	/**
	* 重置
	* @return void	无返回值
	*/
	void Reset();

protected:

private:
	cocos2d::Sprite*	_pGameRole;
	TreeBranchDirection _iDirection;
};

#endif // __TIMBER_MAN_H__