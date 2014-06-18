#include "Layer/TouchLayer.h"
#include "../GameScene.h"
#include "../TmxTestScene.h"
USING_NS_CC;
bool TouchLayer::init()
{
	this->setTouchEnabled(true);
	return true;
}

GameScene* TouchLayer::getGameScene(){
	return (GameScene*)this->getParent();
}
TmxTestScene* TouchLayer::getTmxTestScene(){
	return (TmxTestScene*)this->getParent();
}
bool TouchLayer::ccTouchBegan(CCTouch* touch,CCEvent* event)
{
	//todo
	return true;
}
void TouchLayer::ccTouchMoved(CCTouch* touch,CCEvent* event)
{
	CCPoint pp=touch->getPreviousLocation();//获取之前的点  
	CCPoint np=touch->getLocation();//获取现在的点  
	CCPoint dp=ccpSub(np,pp);//获取差  
	//	this->getTmxTestScene()->moveMap(dp);
}
void TouchLayer::ccTouchEnded(CCTouch* touch,CCEvent* event)
{
	this->getTmxTestScene()->moveHero(this->locationFromTouch(touch));
	//this->getGameScene()->shootTo(this->locationFromTouch(touch));
}
void TouchLayer::setTouchEnabled(bool flag)
{
	if(flag){
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	}else{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
}
CCPoint TouchLayer::locationFromTouch(CCTouch* touch)
{
	//把点从UI坐标系转到GL坐标系
	return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}