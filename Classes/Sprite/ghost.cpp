#include "ghost.h"
USING_NS_CC;
ghost* ghost::create(CCTexture2D* texture)
{
	ghost* _ghost = new ghost();
	_ghost->init(texture);
	_ghost->autorelease();
	return _ghost;
}
bool ghost::init(CCTexture2D* texture)
{	
	winSize = CCDirector::sharedDirector()->getWinSize();
	_ghostSprite = CCSprite::createWithTexture(texture); 

	float minX = _ghostSprite->getContentSize().width/2;
	float maxX = winSize.width-_ghostSprite->getContentSize().width/2;
	float rangeX = maxX - minX;
	float actualX = ( rand() % (int)rangeX ) + minX;

	float minY = _ghostSprite->getContentSize().height/2;
	float maxY = winSize.height-_ghostSprite->getContentSize().height/2;
	float rangeY = maxY - minY;
	float actualY = ( rand() % (int)rangeY ) + minY;

	CCLog("x	:	%f;	y :		%f	;",actualX,actualY);
	_ghostSprite->setPosition(ccp(actualX,actualY));
	_ghostSprite->setTag(0);
	//this->addChild(_ghostSprite);
	return true;
}
ghost::~ghost(){
}