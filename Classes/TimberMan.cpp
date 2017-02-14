#include "TimberMan.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


TimberMan* TimberMan::createTimberMan()
{
	auto timberMan = new TimberMan();
	timberMan->initTimberMan();
	timberMan->setScale(0.5f);

	return timberMan;
}

void TimberMan::initTimberMan()
{
	_pGameRole = Sprite::create("role.png");
	this->addChild(_pGameRole);

	auto animationCache = AnimationCache::getInstance();

	Vector<SpriteFrame*> roleFrames(2);
	roleFrames.pushBack(SpriteFrame::create("att_left.png",Rect(0,0,303,210)));
	roleFrames.pushBack(SpriteFrame::create("role.png",Rect(0,0,196,257)));
	animationCache->addAnimation(Animation::createWithSpriteFrames(roleFrames,0.1f),"left");

	roleFrames.clear();
	roleFrames.pushBack(SpriteFrame::create("att_right.png",Rect(0,0,303,210)));
	roleFrames.pushBack(SpriteFrame::create("role.png",Rect(0,0,196,257)));
	animationCache->addAnimation(Animation::createWithSpriteFrames(roleFrames,0.1f),"right");

	roleFrames.clear();
	roleFrames.pushBack(SpriteFrame::create("die.png",Rect(0,0,104,110)));
	animationCache->addAnimation(Animation::createWithSpriteFrames(roleFrames,0.1f),"die");


	this->setContentSize(Size(_pGameRole->getContentSize().width, _pGameRole->getContentSize().height));
}

void TimberMan::playAction(TreeBranchDirection direction)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/famu.mp3");

	auto animationCache = AnimationCache::getInstance();
	_pGameRole->stopAllActions();
	switch (direction)
	{
	case LEFT:
		_pGameRole->runAction(Animate::create(animationCache->getAnimation("left")));
		break;
	case RIGHT:
		_pGameRole->runAction(Animate::create(animationCache->getAnimation("right")));
		break;
	}

	_iDirection = direction;
}

void TimberMan::setTimberManDie()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/death.mp3");

	auto aCache = AnimationCache::getInstance();
	_pGameRole->stopAllActions();
	_pGameRole->runAction(Animate::create(aCache->getAnimation("die")));
}

TreeBranchDirection TimberMan::getTimberManDirection()
{
	return _iDirection;
}

void TimberMan::Reset()
{
	_pGameRole->stopAllActions();
	_pGameRole->setSpriteFrame(SpriteFrame::create("role.png",Rect(0,0,196,257)));
}
