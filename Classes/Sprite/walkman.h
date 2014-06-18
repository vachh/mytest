#ifndef __MyGame__walkman__
#define __MyGame__walkman__
#include "cocos2d.h"
class walkman:public cocos2d::CCNode{
public:
	static walkman* create();
	bool init();
	float _speedX;
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, _walkmanSprite, WalkmanSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::CCTexture2D*, _walkmantexture, WalkmanTexture);
	CC_SYNTHESIZE_READONLY(cocos2d::CCAnimation*, _walkmanAnimation, WalkmanAnimation);
	CC_SYNTHESIZE_READONLY(cocos2d::CCAnimate*, _walkmanAnimate, WalkmanAnimate);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
protected:

};
#endif	