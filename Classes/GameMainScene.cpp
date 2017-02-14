#include "GameMainScene.h"
#include "GameOverLayer.h"
#include "TreeModel.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


cocos2d::Scene* GameMainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMainScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	//绑定回调函数
	listener->onKeyReleased = CC_CALLBACK_2(GameMainScene::onKeyReleased, this);
	//添加到事件分发器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_iGameScoreNumber = 0;

	//add backgroup
	_pBgFirst = Sprite::create("bg1.png");
	_pBgFirst->setPosition(visibleSize.width/2.0f+origin.x, visibleSize.height/2.0f+origin.y);
	this->addChild(_pBgFirst);
	_pBgSecond = Sprite::create("bg2.png");
	_pBgSecond->setPosition(visibleSize.width/2.0f+origin.x, visibleSize.height/2.0f+origin.y);
	this->addChild(_pBgSecond);

	// add tree model
	auto treeModel = TreeModel::getInstance();
	treeModel->setPosition(visibleSize.width/2.0f, 100);
	this->addChild(treeModel);

	// add TimberMan
	_pTimberMan = TimberMan::createTimberMan();
	_pTimberMan->setPosition(visibleSize.width/2.0f-_pTimberMan->getContentSize().width/2.0f-20, 150);
	this->addChild(_pTimberMan);

	_pTouchEventListener = EventListenerTouchOneByOne::create();
	_pTouchEventListener->onTouchBegan = CC_CALLBACK_2(GameMainScene::onTouchBegans, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_pTouchEventListener, this);
	_pTouchEventListener->setEnabled(false);

	// add game score layer
	_pGameScoreLayer =GameScoreLayer::createScoreLayer();
	_pGameScoreLayer->setPosition(visibleSize/2.0f);
	this->addChild(_pGameScoreLayer);
	_pGameScoreLayer->_cbFun = CC_CALLBACK_0(GameMainScene::gameOverCallback, this);

	// add tab menu
	auto leftItem = Sprite::create("left.png");
	leftItem->setScale(0.5f);
	leftItem->setPosition(leftItem->getContentSize().width/2.0f, 50);
	this->addChild(leftItem);
	auto rightItem = Sprite::create("right.png");
	rightItem->setScale(0.5f);
	rightItem->setPosition(visibleSize.width-rightItem->getContentSize().width/2.0f, 50);
	this->addChild(rightItem);

	auto pGameOverLayer = GameOverLayer::getInstance();
	this->addChild(pGameOverLayer);
	pGameOverLayer->_cbFun = CC_CALLBACK_0(GameMainScene::reset,this);
	pGameOverLayer->setAnchorPoint(Vec2(0,0.5));
	pGameOverLayer->setVisible(false);
	pGameOverLayer->setPosition(visibleSize.width/2, visibleSize.height+pGameOverLayer->getContentSize().height/2);

	// play
	auto play = MenuItemImage::create("play.png","play.png", CC_CALLBACK_0(GameMainScene::playGame, this));
	play->setScale(0.5);
	_pGameMenu = Menu::create(play, NULL);
	this->addChild(_pGameMenu);
	_pGameMenu->setPosition(visibleSize.width/2, play->getContentSize().height*2);

	// game logo
	_pGameLogo = Sprite::create("logo.png");
	_pGameLogo->setPosition(visibleSize.width/2, visibleSize.height/2+_pGameLogo->getContentSize().height);
	this->addChild(_pGameLogo);

	// audio
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgmusic.mp3",true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

	// particle
	ParticleSystem* pl = ParticleSnow::create();
	pl->setTexture(Director::getInstance()->getTextureCache()->addImage("particle.png"));
	pl->setPosition(visibleSize.width/2,visibleSize.height);
	this->addChild(pl,10);

	return true;
}

bool GameMainScene::onTouchBegans(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto pos = touch->getLocation();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto model = TreeModel::getInstance();

	auto isRight = pos.x > visibleSize.width/2;
	_pTimberMan->playAction(isRight ? RIGHT : LEFT);
	if(isRight)
	{
		_pTimberMan->setPosition(visibleSize.width/2+_pTimberMan->getContentSize().width/2+20,150);
	}
	else
	{
		_pTimberMan->setPosition(visibleSize.width/2-_pTimberMan->getContentSize().width/2-20,150);
	}

	if(checkGameIsOver())
	{
		_pTimberMan->setTimberManDie();
		gameOver();

		return false;
	}

	auto dic = visibleSize.width*2;
	auto time = 0.5;
	auto tree = model->deleteTreeHeadNode();
	if( isRight )
	{
		tree->runAction(Spawn::create(RotateBy::create(time,-180),MoveBy::create(time,Vec2(-dic,0)),nullptr));
	}
	else
	{
		tree->runAction(Spawn::create(RotateBy::create(time,180),MoveBy::create(time,Vec2(dic,0)),nullptr));
	}

	_iGameScoreNumber++;
	_pGameScoreLayer->setGameScore(_iGameScoreNumber);
	if(checkGameIsOver())
	{
		_pTimberMan->setTimberManDie();
		gameOver();
	}

	return true;
}

void GameMainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,cocos2d::Event* event)
{
	Director::getInstance()->end(); 
}

void GameMainScene::gameOverCallback()
{
	if(!GameOverLayer::getInstance()->isVisible())
	{
		gameOver();
	}
}

bool GameMainScene::checkGameIsOver()
{
	auto model = TreeModel::getInstance();

	if(model->getFirstTreeBranchDirection() == _pTimberMan->getTimberManDirection()) 
		return true;

	return false;
}

void GameMainScene::reset()
{
	_iGameScoreNumber = 0;

	TreeModel::getInstance()->Reset();
	_pGameScoreLayer->Reset();
	_pTimberMan->Reset();

	_pTouchEventListener->setEnabled(true);

	auto bBgShow = (CCRANDOM_0_1()*10 < 5);
	_pBgFirst->setVisible(bBgShow);
	_pBgSecond->setVisible(!bBgShow);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_pTimberMan->setPosition(visibleSize.width/2-_pTimberMan->getContentSize().width/2-20, 150);
}

void GameMainScene::gameOver()
{
	_pTouchEventListener->setEnabled(false);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto pGameOverLayer = GameOverLayer::getInstance();
	pGameOverLayer->setGameScore(_iGameScoreNumber);
	pGameOverLayer->setPositionY(visibleSize.height + pGameOverLayer->getContentSize().height/2);
	pGameOverLayer->setVisible(true);
	pGameOverLayer->runAction(MoveBy::create(0.5,Vec2(0, -pGameOverLayer->getContentSize().height)));
}

void GameMainScene::playGame()
{
	_pGameMenu->removeFromParent();
	_pGameLogo->removeFromParent();
	_pTouchEventListener->setEnabled(true);
	_pGameScoreLayer->Reset();
}