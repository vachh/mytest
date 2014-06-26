#include "TmxTestScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool TmxTestScene::init()
{
	if(CCScene::init()){
		winSize=CCDirector::sharedDirector()->getWinSize();
		_tileMap=CCTMXTiledMap::create("theworld.tmx"); 
		this->addChild(_tileMap);
		CCLog("init_begin");
		_meta=_tileMap->layerNamed("Meta");
		_meta->setVisible(false);             //设置为不可见

		CCTMXObjectGroup *objects=_tileMap->objectGroupNamed("hero");//取得对象层
		CCDictionary *spanPoint=objects->objectNamed("kongming");		//取得对象
		float px=spanPoint->valueForKey("x")->floatValue();//获取对象的坐标  
		float py=spanPoint->valueForKey("y")->floatValue();  
		/////////

		_kongming=kongming::create(ccp(px,py));
		_tileMap->addChild(_kongming,4);
		//this->addChild(_kongming);
		////////
		_touchLayer=TouchLayer::create();
		this->addChild(_touchLayer,2);

		this->scheduleUpdate();
		CCLog("init_success");
		return true;
		
	}
	return false;
}

//将坐标转换为tile坐标
CCPoint TmxTestScene::tileCoordForPosition(CCPoint position)
{
	int row=_tileMap->getMapSize().height;	//得到地图的高，行数
	int tileSize=_tileMap->getTileSize().width;

	CCLog("(:::_>%d   %d)",row,tileSize);
	CCLog("(position: %f   %f)",position.x,position.y);
	float x = position.x / tileSize;
	float y = (row*tileSize- position.y)/ tileSize;				//y坐标在上
	CCLog("(x,y: %d   %d)",(int)x,(int)y);
	return ccp((int)x,(int)y);
}
bool TmxTestScene::isMove(CCPoint position){
		
	CCPoint tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->tileGIDAt(tileCoord);
	if (tileGid)
	{
		CCDictionary *properties = _tileMap->propertiesForGID(tileGid);
		if (properties)
		{
			const CCString *collision = properties->valueForKey("Collidable");
			if (collision && collision->compare("true") == 0)
			{
				return false;
			}           
		}       
	}
	return true;
}
TmxTestScene::~TmxTestScene(){
	//CC_SAFE_RELEASE(_ghosts);

}
void TmxTestScene::moveMap(CCPoint pos){
	CCPoint oldPoint=_tileMap->getPosition();
	float moveX=0,moveY=0;

	CCSize map_size=_tileMap->getContentSize();
	float m_widthBoundary=(map_size.width-winSize.width);
	float m_heightBoundary=(map_size.height-winSize.height);

	float m_leftBoundary=oldPoint.x>=0?oldPoint.x:-oldPoint.x;
	float m_rightBoundary=m_widthBoundary+oldPoint.x;
	float m_bottomBoundary=oldPoint.y>=0?oldPoint.y:-oldPoint.y;
	float m_topBoundary=m_heightBoundary+oldPoint.y;
	//	CCLog("/////////////////////////////////////////////");
	//CCLog(" m_widthBoundary:	%f",m_widthBoundary );
	//	CCLog("m_heightBoundary:	 %f", m_heightBoundary);
	//	CCLog(" m_leftBoundary:	%f", m_leftBoundary);
	//	CCLog(" m_rightBoundary:	%f", m_rightBoundary);
	//	CCLog(" m_bottomBoundary:	%f", m_bottomBoundary);
	//	CCLog(" m_topBoundary:		%f",m_topBoundary );
	if (m_leftBoundary-pos.x<=m_widthBoundary&&m_rightBoundary+pos.x<=m_widthBoundary)
	{
		moveX=pos.x;
	}else
	{
		moveX=0;
	}
	if (m_bottomBoundary-pos.y<m_heightBoundary&&m_topBoundary+pos.y<m_heightBoundary)
	{
		moveY=pos.y;
	}else
	{
		moveY=0;
	}
	_tileMap->setPosition(ccp(oldPoint.x+moveX,oldPoint.y+moveY));//移动地图  
}
void TmxTestScene::moveHero(cocos2d::CCPoint pp){
	CCPoint point=_kongming->getPos();

	if(fabs(pp.x-point.x)>=fabs(pp.y-point.y))  
	{  
		if(pp.x>=point.x)  
		{  
			_kongming->ToRight();

			CCPoint nowPos=ccp(point.x+16,point.y);
			CCPoint r_nowPos=ccp(point.x+16,point.y);
			if (isMove(r_nowPos))
			{
			_kongming->setPos(nowPos);
			moveMap(ccp(-16,0));
			}
		}  
		else  
		{  
			_kongming->ToLeft();
			CCPoint nowPos=ccp(point.x-16,point.y);
			CCPoint r_nowPos=ccp(point.x-16,point.y);
			if (isMove(r_nowPos))
			{
			_kongming->setPos(nowPos);
			moveMap(ccp(16,0));
			}		
		}  
	}  
	else  
	{  
		if(pp.y>=point.y)  
		{  
			_kongming->ToUp();
			CCPoint nowPos=ccp(point.x,point.y+16);
			CCPoint r_nowPos=ccp(point.x,point.y+16);
			if (isMove(r_nowPos))
			{
			_kongming->setPos(nowPos);
			moveMap(ccp(0,-16));
			}
		}  
		else  
		{  
			_kongming->ToDown();
			CCPoint nowPos=ccp(point.x,point.y-16);
			CCPoint r_nowPos=ccp(point.x,point.y-16);
			if (isMove(r_nowPos))
			{
			_kongming->setPos(nowPos); 
			moveMap(ccp(0,16));
			}
		}  
	}  
}

void TmxTestScene::update(float delta){
	//_walkman->update(delta);
}
