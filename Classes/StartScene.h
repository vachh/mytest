#ifndef __MyGame_StartScene__
#define __MyGame_StartScene__

#include "cocos2d.h"
#include "Layer/BackgroundLayer.h"
#include "Sprite/walkman.h"
class StartScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();
	// a selector callback
	void ToHelpScene(CCObject* pSender);
	void ToGameScene(CCObject* pSender);
	// implement the "static node()" method manually
	CREATE_FUNC(StartScene); //CREATE_FUNC实际上就是create函数，准确的说，是重写了CCLayer里的create函数,让create函数返回子类对象
protected:
	BackgroundLayer* _backgroundLayer;
	walkman* _walkman;
};

#endif // __HELLOWORLD_SCENE_H__
