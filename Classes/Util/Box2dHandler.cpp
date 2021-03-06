#include "Box2dHandler.h"
USING_NS_CC;
Box2dHandler* Box2dHandler::create(){
	Box2dHandler* box2dHandler = new Box2dHandler();
	box2dHandler->initBox2d();
	//	box2dHandler->autorelease();
	return box2dHandler;
	CCLog("%s",__FUNCTION__);
}
bool Box2dHandler::initBox2d(){
	winSize = CCDirector::sharedDirector()->getWinSize();
	b2Vec2 gravity=b2Vec2(0.0f,0.0f);
	_world=new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);
	_world->SetContactListener(this);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
	b2Body* _groundBody=_world->CreateBody(&groundBodyDef);

	b2EdgeShape groundBox;
	b2FixtureDef groundShapeDef;
	groundShapeDef.filter.categoryBits=1;
	groundShapeDef.filter.maskBits=7;

	groundShapeDef.shape=&groundBox;

	// bottom 
	groundBox.Set(b2Vec2(0,0), b2Vec2(winSize.width/PTM_RATIO,0)); 
	_groundBody->CreateFixture(&groundBox, 0); 
	// top 
	groundBox.Set(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO)); 
	_groundBody->CreateFixture(&groundBox, 0); 
	// left 
	groundBox.Set(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(0,0)); 
	_groundBody->CreateFixture(&groundBox, 0); 
	// right 
	groundBox.Set(b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,0)); 
	_groundBody->CreateFixture(&groundBox, 0); 
	CCLog("%s",__FUNCTION__);
	return true;
}
void Box2dHandler::addBodyForSprite(CCSprite* sprite,b2Vec2* volicity,float density,int cate,int mask){
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type=b2_dynamicBody;
	spriteBodyDef.position.Set(sprite->getPositionX()/PTM_RATIO,sprite->getPositionY()/PTM_RATIO);
	spriteBodyDef.userData=sprite;

	b2Body* ninBody=_world->CreateBody(&spriteBodyDef);
	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width/PTM_RATIO/2,sprite->getContentSize().height/PTM_RATIO/2);

	b2FixtureDef spriteShapeDef;
	spriteShapeDef.filter.categoryBits=cate;
	spriteShapeDef.filter.maskBits=mask;

	spriteShapeDef.shape=&spriteShape;
	spriteShapeDef.density=density;
	spriteShapeDef.friction=0.f;			//摩擦力
	spriteShapeDef.restitution=1.0f;		//回复力，完全弹性碰撞
	ninBody->CreateFixture(&spriteShapeDef);

	ninBody->SetLinearVelocity(b2Vec2(volicity->x/PTM_RATIO,volicity->y/PTM_RATIO));

}
void Box2dHandler::BeginContact(b2Contact* contact){

	if (contact)
	{
		MyContact mc;
		mc.fixtureA=contact->GetFixtureA();
		mc.fixtureB=contact->GetFixtureB();
		contact_list.push_back(mc);
	}
	B2_NOT_USED(contact);
}
void Box2dHandler::EndContact(b2Contact* contact){
	contact_list.clear();
	B2_NOT_USED(contact);
}
void Box2dHandler::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
}
void Box2dHandler::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	B2_NOT_USED(contact);
	B2_NOT_USED(impulse);
}
void Box2dHandler::update(float delta){
	_world->Step(delta, 5, 5); 
	for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) { 
		if (b->GetUserData() != NULL) {
			CCSprite *sprite = (CCSprite *)b->GetUserData(); 
			sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
			sprite->setRotation(-1* CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}
Box2dHandler::~Box2dHandler(){
	CC_SAFE_DELETE(_world);
}