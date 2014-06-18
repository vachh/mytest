#ifndef __MyGame__bullet__
#define __MyGame__bullet__
#include "cocos2d.h"
class bullet:public cocos2d::CCNode{
public:
	static bullet* create(cocos2d::CCPoint point);
	bool init(cocos2d::CCPoint point);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, _bulletSprite, BulletSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
protected:

};

#endif