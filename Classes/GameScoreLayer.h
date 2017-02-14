/** @class  GameScoreLayer
  * @brief  游戏得分
  * @author sevens
  * @date   2016/10/01
  * @blog   http://www.developer1024.com/
  */

#ifndef __GAME_SCORE_LAYER_H__
#define __GAME_SCORE_LAYER_H__

#include "cocos2d.h"


class GameScoreLayer : public cocos2d::Layer
{
public:
	static GameScoreLayer* createScoreLayer();
	void initScoreLayer();

	/**
	* 设置游戏分数
	* @param[in] iScore 游戏分数
	* @return void	无返回值
	*/
	void setGameScore(int iScore);

	/**
	* 重置
	* @return void	无返回值
	*/
	void Reset();

	std::function<void()> _cbFun;

protected:

private:
	void callBack();

	void setGameLevel();

private:	
	int						_iGameScore;
	float					_fSpeed;
	int						_iAddPre;
	int						_iGameLevelNum;
	
	cocos2d::Sprite*		_pBlood;
	cocos2d::Node*			_pGameLevel;

	cocos2d::LabelBMFont*	_pScoreLabel;
	cocos2d::ProgressTimer* _pProcessTimer;
};

#endif // __GAME_SCORE_LAYER_H__