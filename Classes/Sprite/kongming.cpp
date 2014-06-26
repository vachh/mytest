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
	state=kongming_dir.right;
	winSize = CCDirector::sharedDirector()->getWinSize();
	aniCache=CCAnimationCache::sharedAnimationCache();
	///////////////////////
	frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("kongming.plist");

	for (int i=1;i<=4;i++)
	{	
		CCArray *walkAnimFrames = CCArray::createWithCapacity(4); 
		CCLog("%s BEGINS","spriteSheet_after");
			for(int j = 1; j <= 4; j++) { 
				char str[20]={0};
				sprintf(str,"kongming_0%d.png", j+(i-1)*4);
				//CCLog("%s BEGINS","spriteSheet_add");
				walkAnimFrames->addObject(frameCache->spriteFrameByName(str));
				//CCLog("%s BEGINS","spriteSheet_add_object");
			} 	
			CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames, 0.2f); 
			char str_be[20];
			sprintf(str_be,"kongming_0%d.png", 1+(i-1)*4);
			switch(i){
				case kongming_dir.down:
					aniCache->addAnimation(walkAnim,"down");
					spriteDown=CCSprite::createWithSpriteFrame( frameCache->spriteFrameByName(str_be));
					CC_SAFE_RETAIN(spriteDown);
					break;
				case kongming_dir.left:
					aniCache->addAnimation(walkAnim,"left");
					spriteLeft=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be));
					CC_SAFE_RETAIN(spriteLeft);
					break;
				case kongming_dir.right:
					aniCache->addAnimation(walkAnim,"right");
					spriteRight=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be)) ;
					CC_SAFE_RETAIN(spriteRight);
					break;	
				case kongming_dir.up:	
					aniCache->addAnimation(walkAnim,"up");
					spriteUp=CCSprite::createWithSpriteFrame(frameCache->spriteFrameByName(str_be));
					CC_SAFE_RETAIN(spriteUp);
					break;
			}
			
	}
	CCAnimate* animate=CCAnimate::create(aniCache->animationByName("right"));
	spriteRight->setPosition(point);
	spriteWidth=spriteRight->getContentSize().width;
	spriteHeight=spriteRight->getContentSize().height;
	this->addChild(spriteRight);
	spriteRight->runAction(CCRepeatForever::create(animate));
	return true;
}
void kongming::_setPos(float s){
	CCPoint pos=this->getPos();
	CCPoint nowPos;
	CCSprite* tmpSprite;
	switch(state){
			case kongming_dir.down:
				nowPos=ccp(pos.x,pos.y-s);
				tmpSprite=this->getSpriteDown();
				break;
			case kongming_dir.left:
				tmpSprite=this->getSpriteLeft();
				nowPos=ccp(pos.x-s,pos.y);
				break;
			case kongming_dir.right:
				tmpSprite=this->getSpriteRight();
				nowPos=ccp(pos.x+s,pos.y);
				break;
			case kongming_dir.up:
				tmpSprite=this->getSpriteUp();
				nowPos=ccp(pos.x,pos.y+s);
				break;
	}
	if (nowPos.x<=this->spriteWidth/2||nowPos.x>=winSize.width-spriteWidth/2||
		nowPos.y<=spriteHeight/2||nowPos.y>=winSize.height-spriteHeight/2)
		return;
		tmpSprite->setPosition(nowPos);
}
CCPoint kongming::getPos(){
	switch(state){
	case kongming_dir.down:
		return this->getSpriteDown()->getPosition();
	case kongming_dir.left:
		return this->getSpriteLeft()->getPosition();
	case kongming_dir.right:
		return this->getSpriteRight()->getPosition();
	case kongming_dir.up:
		return this->getSpriteUp()->getPosition();
	}
}
void kongming::Turn(int dir){
	CCPoint pos=this->getPos();
	this->removeAllChildren();
	CCAnimate* animate;
	CCSprite* tmpSprite;
	switch (dir)
	{
	case kongming_dir.down:
		state=kongming_dir.down;
		animate=CCAnimate::create(aniCache->animationByName("down"));
		tmpSprite=this->getSpriteDown();
		break;
	case kongming_dir.left:
		state=kongming_dir.left;
		animate=CCAnimate::create(aniCache->animationByName("left"));
		tmpSprite=this->getSpriteLeft();
		break;
	case kongming_dir.right:
		state=kongming_dir.right;
		animate=CCAnimate::create(aniCache->animationByName("right"));
		tmpSprite=this->getSpriteRight();
		break;
	case kongming_dir.up:
		state=kongming_dir.up;
		animate=CCAnimate::create(aniCache->animationByName("up"));
		tmpSprite=this->getSpriteUp();
		break;
	}
	tmpSprite->setPosition(pos);
	this->addChild(tmpSprite);
	tmpSprite->runAction(CCRepeatForever::create(animate));
}
void kongming::update(float s){
	this->_setPos(s);
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