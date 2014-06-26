#include "kongming.h"
USING_NS_CC;
kongming* kongming::create(CCPoint point)
{
	kongming* _kongming = new kongming();
	_kongming->init(point);
	_kongming->autorelease();
	return _kongming;
	
}
bool kongming::init(CCPoint point)
{	
	CCLog("%s BEGINS",__FUNCTION__);
	state=right;
	winSize = CCDirector::sharedDirector()->getWinSize();
	aniCache=CCAnimationCache::sharedAnimationCache();
	///////////////////////
	frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("kongming.plist");

    //spriteSheet=CCSpriteBatchNode::create("kongming.png");
	//this->addChild(spriteSheet);
	
	for (int i=1;i<=4;i++)
	{	
		CCArray *walkAnimFrames = CCArray::createWithCapacity(4); 
		CCLog("%s BEGINS","spriteSheet_after");
			for(int j = 1; j <= 4; j++) { 
				char str[20]={0};
				sprintf(str,"kongming_0%d.png", j+(i-1)*4);
				CCLog("%s BEGINS","spriteSheet_add");
				walkAnimFrames->addObject(frameCache->spriteFrameByName(str));
				CCLog("%s BEGINS","spriteSheet_add_object");
			} 
			
			CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames, 0.2f); 
			char str_be[20];
			sprintf(str_be,"kongming_0%d.png", 1+(i-1)*4);
			if (i==down)
			{
				aniCache->addAnimation(walkAnim,"down");
				spriteDown=CCSprite::createWithSpriteFrame( frameCache->spriteFrameByName(str_be));
				spriteDown->setPosition(ccp(0,0));
				CC_SAFE_RETAIN(spriteDown);
			}
			else if (i==left)
			{
				aniCache->addAnimation(walkAnim,"left");
				spriteLeft=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be));
				spriteLeft->setPosition(ccp(0,0));
				CC_SAFE_RETAIN(spriteLeft);
			}
			else if (i==right)
			{
				aniCache->addAnimation(walkAnim,"right");
				spriteRight=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be)) ;
				spriteRight->setPosition(point);
				CC_SAFE_RETAIN(spriteRight);
			}
			else if (i==up)
			{
				aniCache->addAnimation(walkAnim,"up");
				spriteUp=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be));
				spriteUp->setPosition(ccp(0,0));
				CC_SAFE_RETAIN(spriteUp);
			}
			
	//	walkAnimFrames->removeAllObjects();

	}
	CCAnimate* animate=CCAnimate::create(aniCache->animationByName("right"));
	this->addChild(spriteRight);
	spriteRight->runAction(CCRepeatForever::create(animate));
	_speedX=-70.0f;
	return true;
}
void kongming::setPos(CCPoint point){
	if (state==down)
	{
		this->getSpriteDown()->setPosition(point);
	}
	else	if (state==left)
	{
		this->getSpriteLeft()->setPosition(point);
	}
	else if (state==right)
	{
		this->getSpriteRight()->setPosition(point);
	}
	else if (state==up)
	{
		this->getSpriteUp()->setPosition(point);
	}
}
CCPoint kongming::getPos(){
	if (state==down)
	{
		return this->getSpriteDown()->getPosition();
	}
	else	if (state==left)
	{
		return this->getSpriteLeft()->getPosition();
	}
	else if (state==right)
	{
		return this->getSpriteRight()->getPosition();
	}
	else if (state==up)
	{
		return this->getSpriteUp()->getPosition();
	}
}
void kongming::ToDown(){
	CCPoint point=this->getPos();
	state=down;
	this->removeAllChildren();
	CCAnimate* animate=CCAnimate::create(aniCache->animationByName("down"));
	spriteDown->setPosition(point);
	this->addChild(spriteDown);
	spriteDown->runAction(CCRepeatForever::create(animate));
}
void kongming::ToLeft(){
	CCPoint point=this->getPos();
	state=left;
	this->removeAllChildren();
	CCAnimate* animate=CCAnimate::create(aniCache->animationByName("left"));
	spriteLeft->setPosition(point);
	this->addChild(spriteLeft);
	spriteLeft->runAction(CCRepeatForever::create(animate));
}
void kongming::ToRight(){
	CCPoint point=this->getPos();
	this->removeAllChildrenWithCleanup(false);
	state=right;
	CCAnimate* animate=CCAnimate::create(aniCache->animationByName("right"));
	spriteRight->setPosition(point);
	this->addChild(spriteRight);
	spriteRight->runAction(CCRepeatForever::create(animate));
}
void kongming::ToUp(){
	cocos2d::CCPoint point=this->getPos();
	this->removeAllChildrenWithCleanup(false);
	state=up;
	CCAnimate* animate=CCAnimate::create(aniCache->animationByName("up"));
	spriteUp->setPosition(point);
	this->addChild(spriteUp);
	spriteUp->runAction(CCRepeatForever::create(animate));
}
kongming::~kongming(){
	CCAnimationCache::purgeSharedAnimationCache();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	CC_SAFE_RELEASE(spriteUp);
	CC_SAFE_RELEASE(spriteLeft);
	CC_SAFE_RELEASE(spriteDown);
	CC_SAFE_RELEASE(spriteRight);
}