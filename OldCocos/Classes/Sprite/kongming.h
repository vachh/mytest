#ifndef __MyGame__kongming__
#define __MyGame__kongming__
#include "cocos2d.h"

const static char* const plistName="kongming.plist";
const static char*	const aniDownCacheName="down";
const static char* const	aniLeftCacheName="left";
const static char* const	aniRightCacheName="right";
const static char*	 const aniUpCacheName="up";
enum dir{
	DOWN=1,
	LEFT,
	RIGHT,
	UP
};
class kongming:public cocos2d::CCNode{
public:
	
	int state;
	float spriteWidth;
	float spriteHeight;
	float _speed;
	static kongming* create(cocos2d::CCPoint point);
	bool init(cocos2d::CCPoint point);
	~kongming();
	cocos2d::CCPoint getPos();
	void update(float delta);
	void _setPos(float s);
	void Turn(int dir);

	cocos2d::CCSize winSize;
	cocos2d::CCSpriteFrameCache* frameCache;

	cocos2d::CCSprite* spriteDown;
	cocos2d::CCSprite* spriteLeft;
	cocos2d::CCSprite* spriteRight;
	cocos2d::CCSprite* spriteUp;

protected:

};
#endif	