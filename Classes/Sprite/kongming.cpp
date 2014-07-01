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
	_speed=70.0f;
	state=RIGHT;
	winSize = CCDirector::sharedDirector()->getWinSize();
	///////////////////////
	frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile(plistName);

	for (int i=1;i<=4;i++)
	{	
		CCArray *walkAnimFrames = CCArray::createWithCapacity(4); 
		CCLog("%s BEGINS","spriteSheet_after");
			for(int j = 1; j <= 4; j++) { 
				char str[20]={0};
				sprintf(str,"kongming_0%d.png", j+(i-1)*4);
				walkAnimFrames->addObject(frameCache->spriteFrameByName(str));
			} 	
			CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames, 0.2f); 
			CCAnimate* animate=CCAnimate::create(walkAnim);
			char str_be[20];
			sprintf(str_be,"kongming_0%d.png", 1+(i-1)*4);
			switch(i){
				case DOWN:
					spriteDown=CCSprite::createWithSpriteFrame( frameCache->spriteFrameByName(str_be));	
					spriteDown->runAction(CCRepeatForever::create(animate));
					spriteDown->setVisible(false);
					this->addChild(spriteDown);
					CC_SAFE_RETAIN(spriteDown);
					break;
				case LEFT:
					spriteLeft=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be));
					spriteLeft->runAction(CCRepeatForever::create(animate));
					spriteLeft->setVisible(false);
					this->addChild(spriteLeft);
					CC_SAFE_RETAIN(spriteLeft);
					break;
				case RIGHT:
					spriteRight=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be)) ;		
					spriteRight->runAction(CCRepeatForever::create(animate));
					this->addChild(spriteRight);
					//spriteRight->setVisible(false);
					CC_SAFE_RETAIN(spriteRight);
					break;	
				case UP:	
					spriteUp=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be));		
					spriteUp->runAction(CCRepeatForever::create(animate));
					spriteUp->setVisible(false);
					this->addChild(spriteUp);
					CC_SAFE_RETAIN(spriteUp);
					break;
			}		
	}

	this->setPosition(point);
	spriteWidth=spriteRight->getContentSize().width;
	spriteHeight=spriteRight->getContentSize().height;
	return true;
}
void kongming::_setPos(float s){
	CCPoint pos=this->getPos();
	CCPoint nowPos;
	switch(state){
			case DOWN:
				nowPos=ccp(pos.x,pos.y-s);
				break;
			case LEFT:
				nowPos=ccp(pos.x-s,pos.y);
				break;
			case RIGHT:
				nowPos=ccp(pos.x+s,pos.y);
				break;
			case UP:
				nowPos=ccp(pos.x,pos.y+s);
				break;
	}
// 	if (nowPos.x<=this->spriteWidth/2||nowPos.x>=winSize.width-spriteWidth/2||
// 		nowPos.y<=spriteHeight/2||nowPos.y>=winSize.height-spriteHeight/2)
// 		return;
	if (nowPos.x<=this->spriteWidth/2||nowPos.x>=1280-spriteWidth/2||
		nowPos.y<=spriteHeight/2||nowPos.y>=960-spriteHeight/2)
		return;
		this->setPosition(nowPos);
}
CCPoint kongming::getPos(){
	return this->getPosition();
}
void kongming::Turn(int dir){
	CCSprite* stateSprite;
	CCSprite* tmpSprite;
	switch(state){
			case DOWN:
				stateSprite=spriteDown;
				break;
			case LEFT:
				stateSprite=spriteLeft;
				break;
			case RIGHT:
				stateSprite=spriteRight;
				break;
			case UP:
				stateSprite=spriteUp;
				break;
	}
	stateSprite->setVisible(false);
	switch (dir)
	{
			case DOWN:
				state=DOWN;
				tmpSprite=spriteDown;
				break;
			case LEFT:
				state=LEFT;
				tmpSprite=spriteLeft;
				break;
			case RIGHT:
				state=RIGHT;
				tmpSprite=spriteRight;
				break;
			case UP:
				state=UP;
				tmpSprite=spriteUp;
				break;
	}
	tmpSprite->setVisible(true);
}
void kongming::update(float s){
	this->_setPos(s);
}
kongming::~kongming(){
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	CC_SAFE_RELEASE(spriteUp);
	CC_SAFE_RELEASE(spriteLeft);
	CC_SAFE_RELEASE(spriteDown);
	CC_SAFE_RELEASE(spriteRight);
}
//aniCache->addAnimation(walkAnim,aniUpCacheName);
//CCAnimate* animate=CCAnimate::create(aniCache->animationByName(aniRightCacheName));
//CCAnimationCache::purgeSharedAnimationCache();