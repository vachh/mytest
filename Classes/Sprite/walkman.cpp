#include "walkman.h"
USING_NS_CC;
walkman* walkman::create()
{
	walkman* _walkman = new walkman();
	_walkman->init();
	_walkman->autorelease();
	return _walkman;
}
bool walkman::init()
{	
	winSize = CCDirector::sharedDirector()->getWinSize();

	_walkmantexture=CCTextureCache::sharedTextureCache()->addImage("walkanim.png");
	float w=_walkmantexture->getContentSize().width/4;
	float h=_walkmantexture->getContentSize().height;
	_walkmanAnimation=CCAnimation::create();
	_walkmanAnimation->setDelayPerUnit(0.2f);
	for (int i=0;i<4;i++)
	{
		_walkmanAnimation->addSpriteFrameWithTexture(_walkmantexture,CCRectMake(i*w,0,w,h));
	}
	_walkmanAnimate=CCAnimate::create(_walkmanAnimation);
	_walkmanSprite=CCSprite::create("walkanim.png",CCRectMake(0,0,64,64));
	_walkmanSprite->setPosition(ccp(160,60));
	this->addChild(_walkmanSprite);
	_walkmanSprite->runAction(CCRepeatForever::create(_walkmanAnimate));
	_speedX=-70.0f;
	return true;
}