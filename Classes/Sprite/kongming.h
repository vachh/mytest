#ifndef __MyGame__kongming__
#define __MyGame__kongming__
#include "cocos2d.h"
struct hero_dir{
	const static int down=1;
	const static int	left=2;
	const static int	right=3;
	const static int	up=4;
};
class kongming:public cocos2d::CCNode{
public:
	hero_dir kongming_dir;
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

	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSpriteFrameCache*,frameCache,FrameCache);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSpriteBatchNode*,spriteSheet,SpriteSheet);
	//CC_SYNTHESIZE_READONLY(cocos2d::CCTexture2D*, texture, Texture);
	CC_SYNTHESIZE_READONLY(cocos2d::CCAnimationCache*, aniCache, AniCache);

	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, spriteDown, SpriteDown);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, spriteLeft, SpriteLeft);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, spriteRight, SpriteRight);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, spriteUp, SpriteUp);



protected:

};
#endif	