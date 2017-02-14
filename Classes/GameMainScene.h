/** @class  GameMainScene
  * @brief  ÓÎÏ·Ö÷³¡¾°
  * @author sevens
  * @date   2016/10/01
  * @blog   http://www.developer1024.com/
  */

#ifndef __GAME_MAINSCENE_H__
#define __GAME_MAINSCENE_H__

#include "cocos2d.h"
#include "GameScoreLayer.h"
#include "TimberMan.h"


class GameMainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	bool onTouchBegans(cocos2d::Touch* touch, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,cocos2d::Event* event);

	void gameOverCallback();

	CREATE_FUNC(GameMainScene);

protected:

private:
	bool checkGameIsOver();
	
	void reset();
	
	void gameOver();
	
	void playGame();

private:
	cocos2d::Sprite* _pBgFirst;
	cocos2d::Sprite* _pBgSecond;
	cocos2d::Sprite* _pGameLogo;

	int _iGameScoreNumber;

	cocos2d::Menu* _pGameMenu;
	
	GameScoreLayer*	_pGameScoreLayer;

	TimberMan* _pTimberMan;

	cocos2d::EventListenerTouchOneByOne* _pTouchEventListener;
};

#endif // __GAME_MAINSCENE_H__
