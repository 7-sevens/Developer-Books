#include "GameOverLayer.h"

USING_NS_CC;


static GameOverLayer* g_pGameOverLayer = nullptr;
GameOverLayer* GameOverLayer::getInstance()
{
	if (!g_pGameOverLayer)
	{
		g_pGameOverLayer = new GameOverLayer();
		g_pGameOverLayer->initGameOverLayer();
		g_pGameOverLayer->setScale(0.5f);
	}

	return g_pGameOverLayer;
}

void GameOverLayer::initGameOverLayer()
{
	// background
	auto bg = Sprite::create("over.png");
	this->setContentSize(Size(bg->getContentSize().width, bg->getContentSize().height));
	this->addChild(bg);

	// new score label
	_pNewScoreLabel = LabelBMFont::create("0", "fonts/font-issue.fnt");
	this->addChild(_pNewScoreLabel);
	// best score label
	_pBestScoreLabel = LabelBMFont::create("9999", "fonts/font-issue.fnt");
	_pBestScoreLabel->setPositionY(-100);
	this->addChild(_pBestScoreLabel);

	// new score sprite
	auto _pNewScoreSprite = Sprite::create("newScore.png");
	_pNewScoreSprite->setPositionY(_pNewScoreSprite->getContentSize().width/3.0f);
	this->addChild(_pNewScoreSprite);

	// menu
	auto playItem = MenuItemImage::create("play.png", "play.png", CC_CALLBACK_0(GameOverLayer::onMenuCallBack, this));
	auto menu = Menu::create(playItem, nullptr);
	menu->setPosition(0, playItem->getContentSize().height - bg->getContentSize().height/2.0f);
	this->addChild(menu);

}

void GameOverLayer::setGameScore(int iScore)
{
	int iMaxScore = iScore;
	char value[50] = {0};
	sprintf(value, "Score %d", iScore);
	_pNewScoreLabel->setString(value);

	iMaxScore = UserDefault::getInstance()->getIntegerForKey("maxScore");
	if (iMaxScore < iScore)
	{
		UserDefault::getInstance()->setIntegerForKey("maxScore",iMaxScore);
	}

	_pNewScoreSprite->setVisible(( iMaxScore < iScore ));
	char str2[50] = {0};
	sprintf(str2, "Max Score %d", ( iMaxScore < iScore ) ? iScore : iMaxScore);
	_pBestScoreLabel->setString(str2);

	UserDefault::getInstance()->flush();
}

void GameOverLayer::onMenuCallBack()
{
	if (_cbFun)
		_cbFun();

	this->setVisible(false);
}

