#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

bool GameScene::init()
{
	if(CCScene::init()){

		box2dHandler=Box2dHandler::create();

		_backgroundLayer=BackgroundLayer::create();
		_touchLayer=TouchLayer::create();
		_ninja=ninja::create();
		_walkman=walkman::create();
		this->addChild(_backgroundLayer,0);
		this->addChild(_ninja,1);
		this->addChild(_walkman,1);
		this->addChild(_touchLayer,2);

		int capacity = 20;
		_ghosts = CCArray::createWithCapacity(capacity);
		CC_SAFE_RETAIN(_ghosts);
		_bullets=CCArray::createWithCapacity(5);
		CC_SAFE_RETAIN(_bullets);
		winSize = CCDirector::sharedDirector()->getWinSize();

		batch=CCSpriteBatchNode::create("youling.png");
		CCTexture2D* texture=batch->getTexture();
		for(int i = 0;i < capacity;i++){
			int type = CCRANDOM_0_1()*2;
			ghost* _ghost = ghost::create(texture);
			_ghosts->addObject(_ghost);
			batch->addChild(_ghost->getGhostSprite(),1);
		}
		batch->setTag(100);
		this->addChild(batch,1);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("boom.wav");
		this->scheduleUpdate();
		addSpriteToBox2d();
		return true;
	}
	return false;
}
void GameScene::addSpriteToBox2d(){
	box2dHandler->addBodyForSprite(_ninja->getNinjaSprite(),new b2Vec2(0,100),2.0f,2,3);
	box2dHandler->addBodyForSprite(_walkman->getWalkmanSprite(),new b2Vec2(-80,0),2.0f,1,1);
	CCLog("_ninja->getNinjaSprite()->getTag():		%d",_ninja->getNinjaSprite()->getTag());
	CCObject* iterator;
	CCARRAY_FOREACH(_ghosts,  iterator){
		ghost* _ghost = (ghost*)iterator;
		box2dHandler->addBodyForSprite(_ghost->getGhostSprite(),new b2Vec2(100,80),2.0f,4,5);
	}
}
GameScene::~GameScene(){
	CC_SAFE_RELEASE(_ghosts);
	CC_SAFE_RELEASE(_bullets);
	CC_SAFE_DELETE(box2dHandler);
}
void GameScene::shootTo(CCPoint target)
{

	CCPoint speed=getBulletSpeed(_ninja->getNinjaSprite()->getPosition(),target);
	bullet* _bullet=bullet::create(ccp(_ninja->getNinjaSprite()->getContentSize().width/2,_ninja->getNinjaSprite()->getPositionY()));
	if (_bullets->count()<5)
	{
		_bullets->addObject(_bullet);
		this->addChild(_bullet,1);
		box2dHandler->addBodyForSprite(_bullet->getBulletSprite(),new b2Vec2(speed.x,speed.y),2.0f,4,4);
	}
}
CCPoint GameScene::getBulletSpeed(CCPoint position,CCPoint target)
{
	return ccp(target.x-position.x,target.y-position.y);
}
void GameScene::update(float delta){
	box2dHandler->update(delta);

	//_walkman->update(delta);
	checkOutCollision();
	if (_walkman->getWalkmanSprite()->getPositionX()<=_walkman->getWalkmanSprite()->getContentSize().width/2+1||
		_walkman->getWalkmanSprite()->getPositionX()>=winSize.width-_walkman->getWalkmanSprite()->getContentSize().width/2-1)
	{
		_walkman->_speedX=-_walkman->_speedX;
		if (_walkman->_speedX>0)
		{
			_walkman->getWalkmanSprite()->runAction(CCFlipX::create(true));
		}else{
			_walkman->getWalkmanSprite()->runAction(CCFlipX::create(false));
		}

	}
	CCObject* bIt;
	CCARRAY_FOREACH(_bullets, bIt){
		bullet* _bullet = (bullet*)bIt;
		if (_bullet)
		{
			float p_minX=_bullet->getBulletSprite()->getPositionX()-_bullet->getBulletSprite()->getContentSize().width/2;
			float p_maxX=_bullet->getBulletSprite()->getPositionX()+_bullet->getBulletSprite()->getContentSize().width/2;
			float p_minY=_bullet->getBulletSprite()->getPositionY()-_bullet->getBulletSprite()->getContentSize().height/2;
			float p_maxY=_bullet->getBulletSprite()->getPositionY()+_bullet->getBulletSprite()->getContentSize().height/2;
			if(p_minX<=0||p_maxX>=winSize.width||p_minY<=0||p_maxY>=winSize.height){
				_bullets->removeObject(_bullet,false);
				this->removeChild(_bullet);	
			}
		}
	}

}
void GameScene::checkOutCollision(){
	std::list<b2Body*> bulletDestroy_list;
	std::list<b2Body*> ghostDestroy_list;
	for(list<MyContact>::iterator it = box2dHandler->contact_list.begin(); 
		it != box2dHandler->contact_list.end();
		++it)
	{
		MyContact& contact = *it;
		b2Body* bodyA = contact.fixtureA->GetBody();
		b2Body* bodyB = contact.fixtureB->GetBody();
		CCSprite* sa = (CCSprite*)bodyA->GetUserData();
		CCSprite* sb = (CCSprite*)bodyB->GetUserData();
		if (sa && sb)
		{
			int ta=sa->getTag();
			int tb=sb->getTag();
			if (ta==0&&tb==1)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.wav");
				ghostDestroy_list.push_back(bodyA);
				bulletDestroy_list.push_back(bodyB);
			}
			else	if (ta==1&&tb==0)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.wav");
				ghostDestroy_list.push_back(bodyB);
				bulletDestroy_list.push_back(bodyA);
			}
		}
	}
	// Destroy contact item.
	std::list<b2Body*>::iterator it = bulletDestroy_list.begin();
	while(it != bulletDestroy_list.end())
	{
		if ((*it)->GetUserData() != NULL)
		{
			CCSprite* sprite = (CCSprite*)((*it)->GetUserData());
			if (sprite)
			{
				_bullets->removeObject((bullet*)sprite->getParent(),false);
				this->removeChild((bullet*)sprite->getParent(),true);		
			}
			box2dHandler->_world->DestroyBody(*it);
		}
		++it;
	}
	it = ghostDestroy_list.begin();
	while(it != ghostDestroy_list.end())
	{
		if ((*it)->GetUserData() != NULL)
		{
			CCSprite* sprite = (CCSprite*)((*it)->GetUserData());
			if (sprite)
			{
				_ghosts->removeObject(sprite->getParent(),false);
				batch->removeChild(sprite,true);
			}
			box2dHandler->_world->DestroyBody(*it);
		}
		++it;
	}
	bulletDestroy_list.clear();
	ghostDestroy_list.clear();
	box2dHandler->contact_list.clear();
}
