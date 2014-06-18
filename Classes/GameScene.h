
#ifndef __MyGame__GameScene__
#define  __MyGame__GameScene__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/TouchLayer.h"
#include "Sprite/ninja.h"
#include "Sprite/ghost.h"
#include "Sprite/bullet.h"
#include "Sprite/walkman.h"
#include "Util/Box2dHandler.h"
typedef enum{
	k_Operate_Pause = 0,
	k_Operate_Resume
}OperateFlag;

class GameScene : public cocos2d::CCScene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
	~GameScene();
protected:
	Box2dHandler* box2dHandler;
	BackgroundLayer* _backgroundLayer;
	TouchLayer* _touchLayer;
	ninja* _ninja;
	walkman* _walkman;

	CC_SYNTHESIZE_READONLY(cocos2d::CCSpriteBatchNode*, batch, Batch);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, _ghosts, Ghosts);
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, _bullets, Bullets);
	void addSpriteToBox2d();
	void update(float delta);

	void shootTo(cocos2d::CCPoint target);
	cocos2d::CCPoint getBulletSpeed(cocos2d::CCPoint position,cocos2d::CCPoint target);
	//Åö×²¼ì²âÏà¹Ø
	void checkOutCollision();
};

#endif /* defined(__FishingJoy__GameScene__) */