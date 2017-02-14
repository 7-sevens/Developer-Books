#include "GameScoreLayer.h"

USING_NS_CC;


GameScoreLayer* GameScoreLayer::createScoreLayer()
{
	auto gameScoreLayer = new GameScoreLayer();
	gameScoreLayer->initScoreLayer();
	gameScoreLayer->setScale(0.5f);

	return gameScoreLayer;
}

void GameScoreLayer::initScoreLayer()
{
	// init value
	_iGameScore = 0;
	_fSpeed = 0.02;
	_iAddPre = 20;
	_iGameLevelNum = 0;

	// background
	auto bg = cocos2d::Sprite::create("blood_bg.png");
	this->addChild(bg);

	// ProcessTimer
	_pProcessTimer = ProgressTimer::create(Sprite::create("blood.png"));
	_pProcessTimer->setType(ProgressTimer::Type::BAR);
	_pProcessTimer->setPercentage(100);
	_pProcessTimer->setMidpoint(Vec2(0,0));
	_pProcessTimer->setBarChangeRate(Vec2(1,0));
	this->addChild(_pProcessTimer);

	// Label
	_pScoreLabel = LabelBMFont::create("0", "fonts/font-issue.fnt");
	this->addChild(_pScoreLabel);

	_pGameLevel = Node::create();
	auto level = Sprite::create("level.png");
	_pGameLevel->addChild(level, 0);
	auto lab = LabelBMFont::create("0", "fonts/font-issue.fnt");
	lab->setPosition(level->getContentSize().width/2.0f + 50, 10);
	lab->setScale(1.5f);
	_pGameLevel->addChild(lab, 1, "level");
	this->addChild(_pGameLevel);
	_pGameLevel->setVisible(false);
}

void GameScoreLayer::setGameScore(int iScore)
{
	_iGameScore = iScore;

	int num = _iGameScore / 20;
	if (num > 20)
		num = 20;

	_pProcessTimer->stopAllActions();

	int pro = _pProcessTimer->getPercentage() + _iAddPre - num * 0.5;
	if (pro > 100)
		pro = 100;
	char value[12] = {0};
	sprintf(value, "%d", iScore);
	_pScoreLabel->setString(value);
	_pProcessTimer->setPercentage(pro);

	auto action = Sequence::create(ProgressTo::create(_fSpeed*pro,0), CallFunc::create(CC_CALLBACK_0(GameScoreLayer::callBack,this)), nullptr);
	_pProcessTimer->runAction(action);
	setGameLevel();
}

void GameScoreLayer::Reset()
{
	_iGameScore = 0;
	_fSpeed = 0.02;
	_iAddPre = 20;
	_iGameLevelNum = 0;

	_pProcessTimer->stopAllActions();
	_pProcessTimer->setPercentage(100);
	auto action = Sequence::create(ProgressTo::create(_fSpeed*100, 0), CallFunc::create(CC_CALLBACK_0(GameScoreLayer::callBack,this)), nullptr);
	_pProcessTimer->runAction(action);
	char value[12] = {0};
	sprintf(value, "%d", 0);
	_pScoreLabel->setString(value);
}

void GameScoreLayer::callBack()
{
	if (_cbFun)
		_cbFun();
}

void GameScoreLayer::setGameLevel()
{
	int	num = _iGameScore / 20;
	if (num > _iGameLevelNum)
	{
		_iGameLevelNum = _iGameScore / 20;
		auto lab = static_cast<LabelBMFont*>(_pGameLevel->getChildByName("level"));
		char value[12] = {0};
		sprintf(value, "%d", _iGameLevelNum);
		lab->setString(value);
		_pGameLevel->setPosition(Vec2(0, 0));
		_pGameLevel->setVisible(true);
		_pGameLevel->runAction(Sequence::create(MoveBy::create(0.7, Vec2(0,200)), Hide::create(), nullptr));
	}
}
