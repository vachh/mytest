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
	CCPoint touchPos;
	cocos2d::CCTMXTiledMap *_tileMap; 
	TouchLayer* _touchLayer;
	CREATE_FUNC(TmxTestScene);
	bool init();
	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
	void setNotPassArea();
	bool isMove(cocos2d::CCPoint position);
	~TmxTestScene();
protected:
	kongming* _kongming;
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
	CC_SYNTHESIZE_READONLY(cocos2d::CCTMXLayer*, _meta, Meta);
	void update(float delta);
	bool moveMap(cocos2d::CCPoint mapMoveDis);
	void moveHero(cocos2d::CCPoint target);

	vector<cocos2d::CCPoint>	notPassList;		
	CCSize map_size;
	CCPoint map_offset;
	int map_tile_row;	//得到地图的高，行数
	int map_tile_col;//列数
	int map_tile_size;
	
	float m_widthBoundary;
	float m_heightBoundary;
};

#endif /* defined(__FishingJoy__GameScene__) */