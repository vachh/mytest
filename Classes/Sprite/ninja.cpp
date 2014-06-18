#include "ninja.h"

USING_NS_CC;
ninja* ninja::create()
{
	ninja* _ninja = new ninja();
	_ninja->init();
	_ninja->autorelease();
	return _ninja;
}
bool ninja::init()
{	
	winSize = CCDirector::sharedDirector()->getWinSize();
	_ninjaSprite = CCSprite::create("renzhe.png",CCRectMake(0, 0, 27, 40));
	_ninjaSprite->setPosition(ccp(_ninjaSprite->getContentSize().width/2,winSize.height/2));
	_ninjaSprite->setTag(10);
	this->addChild(_ninjaSprite);

	return true;
}
ninja::~ninja(){
}