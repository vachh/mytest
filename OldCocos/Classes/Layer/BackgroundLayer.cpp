#include "BackgroundLayer.h"
USING_NS_CC;
bool BackgroundLayer::init()
{
	if(CCLayer::init()){
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		//	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pSprite = CCSprite::create("background.png",CCRectMake(0, 0, 320, 480));//�������鲢��ӵ���
		pSprite->setPosition(ccp(origin.x + visibleSize.width/2 ,
			origin.y+visibleSize.height /2));
		this->addChild(pSprite, 0);
		return true;
	}
	return false;
}

