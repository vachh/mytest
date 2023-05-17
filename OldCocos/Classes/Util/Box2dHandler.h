#ifndef __MyGame__Box2dHandler__
#define  __MyGame__Box2dHandler__
#define PTM_RATIO 32
#include "cocos2d.h"
#include "Box2D/Box2D.h"
class MyContact{
public:
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
};
class Box2dHandler:public b2ContactListener{
public:
	b2World* _world;
	list<MyContact> contact_list;
	static Box2dHandler* create();
	bool initBox2d();
	void addBodyForSprite(cocos2d::CCSprite* sprite,b2Vec2* volicity,float density,int cate,int mask);
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	void update(float delta);
	~Box2dHandler();
	CC_SYNTHESIZE_READONLY(cocos2d::CCSize, winSize, WinSize);
protected:


};

#endif