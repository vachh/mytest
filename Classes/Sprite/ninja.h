#ifndef __MyGame__ninja_
#define __MyGame__ninja_
#include "cocos2d.h"
class ninja:public cocos2d::CCNode{
public:
	static ninja* create();
	~ninja();
	bool init();
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, _ninjaSprite, NinjaSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
protected:
};
#endif	