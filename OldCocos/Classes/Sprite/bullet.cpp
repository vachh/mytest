#include "bullet.h"
USING_NS_CC;

bullet* bullet::create(CCPoint point)
{
	bullet* _bullet = new bullet();
	_bullet->init(point);
	_bullet->autorelease();
	return _bullet;
}
bool bullet::init(CCPoint point)
{	
	winSize = CCDirector::sharedDirector()->getWinSize();
	_bulletSprite = CCSprite::create("feibiao.png",CCRectMake(0, 0, 20, 20));
	_bulletSprite->setPosition(point);
	_bulletSprite->setTag(1);
	this->addChild(_bulletSprite);
	return true;
}