#ifndef __MyGame__ghost__
#define __MyGame__ghost__
#include "cocos2d.h"
class ghost:public cocos2d::CCNode{
public:
	static ghost* create(cocos2d::CCTexture2D* texture);
	~ghost();
	bool init(cocos2d::CCTexture2D* texture);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, _ghostSprite, GhostSprite);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
protected:

};
#endif	