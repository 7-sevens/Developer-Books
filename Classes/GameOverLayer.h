/** @class  GameOverLayer
  * @brief  游戏结束
  * @author sevens
  * @date   2016/10/01
  * @blog   http://www.developer1024.com/
  */

#ifndef __GAME_OVER_LAYER_H__
#define __GAME_OVER_LAYER_H__

#include "cocos2d.h"


class GameOverLayer : public cocos2d::Layer
{
public:
	static GameOverLayer* getInstance();
	
	/**
	* 设置游戏分数
	* @param[in] iScore 游戏分数
	* @return void	无返回值
	*/
	void setGameScore(int iScore);

	std::function<void()> _cbFun;

protected:
	void initGameOverLayer();
		
private:
	void onMenuCallBack();
	
private:
	cocos2d::Sprite*		_pNewScoreSprite;
	cocos2d::LabelBMFont*	_pNewScoreLabel;
	cocos2d::LabelBMFont*	_pBestScoreLabel;
};

#endif // __GAME_OVER_LAYER_H__