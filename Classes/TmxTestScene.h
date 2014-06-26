#ifndef __MyGame__TmxTestScene__
#define  __MyGame__TmxTestScene__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Layer/TouchLayer.h"
#include "Sprite/kongming.h"
USING_NS_CC;
class TmxTestScene : public cocos2d::CCScene
{
public:
	cocos2d::CCTMXTiledMap *_tileMap; 
	TouchLayer* _touchLayer;
	CREATE_FUNC(TmxTestScene);
	bool init();
	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
	bool isMove(cocos2d::CCPoint position);
	~TmxTestScene();
protected:
	kongming* _kongming;
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
	CC_SYNTHESIZE_READONLY(cocos2d::CCTMXLayer*, _meta, Meta);
	void update(float delta);
	void moveMap(cocos2d::CCPoint target);
	void moveHero(cocos2d::CCPoint target);
};

#endif /* defined(__FishingJoy__GameScene__) */