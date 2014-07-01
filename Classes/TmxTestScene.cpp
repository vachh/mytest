#include "TmxTestScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
//#include <list>
bool TmxTestScene::init()
{
	if(CCScene::init()){
		winSize=CCDirector::sharedDirector()->getWinSize();
		_tileMap=CCTMXTiledMap::create("theworld.tmx"); 
		this->addChild(_tileMap);
		CCLog("init_begin");
		_meta=_tileMap->layerNamed("Meta");
		_meta->setVisible(false);             //设置为不可见

		//解决地图抖动
		CCArray *pChildrenArray = _tileMap->getChildren();
		CCSpriteBatchNode *child = NULL;
		CCObject *pObject = NULL;
		CCARRAY_FOREACH(pChildrenArray,pObject){
			child = (CCSpriteBatchNode *)pObject;
			if(!child)
				break;
			child->getTexture()->setAntiAliasTexParameters();
		}	
		/////////
		map_offset=ccp(0,0);
		 map_size=_tileMap->getContentSize();
		 m_widthBoundary=(map_size.width-winSize.width);
		 m_heightBoundary=(map_size.height-winSize.height);
		/////////
		 map_tile_row=_tileMap->getMapSize().height;	//得到地图的高，行数
		 map_tile_col=_tileMap->getMapSize().width;
		 map_tile_size=_tileMap->getTileSize().width;

		// int world_height=map_tile_row*map_tile_size;
		 //int world_width=map_tile_col*map
		 /////////
		 CCTMXObjectGroup *objects=_tileMap->objectGroupNamed("hero");//取得对象层
		 CCDictionary *spanPoint=objects->objectNamed("kongming");		//取得对象
		 float px=spanPoint->valueForKey("x")->floatValue();//获取对象的坐标  
		 float py=spanPoint->valueForKey("y")->floatValue();  
		_kongming=kongming::create(ccp(px,py));
		_tileMap->addChild(_kongming,4);
		//this->addChild(_kongming);
		////////
		_touchLayer=TouchLayer::create();
		this->addChild(_touchLayer,2);
		CCLog("(first_>%d   %d)",map_tile_row,map_tile_col);
		this->scheduleUpdate();
		this->setNotPassArea();			//设置地图不可通过区域
		CCLog("init_success");
		return true;
		
	}
	return false;
}

//将坐标转换为tile坐标
CCPoint TmxTestScene::tileCoordForPosition(CCPoint position)
{
	//CCLog("(:::_>%d   %d)",map_tile_row,map_tile_size);
	//CCLog("(position: %f   %f)",position.x,position.y);
	float x = position.x / map_tile_size;
	float y = (map_tile_row*map_tile_size- position.y)/ map_tile_size;				//y坐标在上
	//CCLog("(x,y: %d   %d)",(int)x,(int)y);
	return  ccp((int)x,(int)y);
}
void TmxTestScene::setNotPassArea(){
	for (int row=0;row<map_tile_row;++row){
		for (int col=0;col<map_tile_col;++col){
			int tileGid = _meta->tileGIDAt(ccp(col,row));
			if (tileGid){
				CCDictionary *properties = _tileMap->propertiesForGID(tileGid);
				if (properties){
					const CCString *collision = properties->valueForKey("Collidable");
					if (collision && collision->compare("true") == 0){
						notPassList.push_back(ccp(col,row));									//把不可通过的区域缓存进vector
					}           
				}       
			}
		}
	}
}
bool TmxTestScene::isMove(CCPoint pos){
	
//	CCPoint opposite_pos=ccp(pos.x+map_offset.x,pos.y+map_offset.y);	//相对于地图的位置，因为地图可能有移动，要考虑
	//	CCLog("(hero_x,hero_y: %f   %f)",pos.x,pos.y);	
	//CCLog("(mapx,mapy: %f   %f)",map_offset.x,map_offset.y);
	//CCLog("(herox,heroy: %f   %f)",opposite_pos.x,opposite_pos.y);
	CCPoint tileCoord = this->tileCoordForPosition(pos);
	//sCCLog("(tilex,tiley: %f   %f)",tileCoord.x,tileCoord.y);
	vector<cocos2d::CCPoint>::iterator iter;  
	for (iter = notPassList.begin();iter != notPassList.end();++iter)  {  
		if (tileCoord.x==iter->x&&tileCoord.y==iter->y)
		{
			return false;
		}
	}  
	return true;
}
TmxTestScene::~TmxTestScene(){
	//CC_SAFE_RELEASE(_ghosts);
	notPassList.clear(); 
}
bool TmxTestScene::moveMap(CCPoint pos){
	CCPoint oldPoint=_tileMap->getPosition();


	float moveX=0,moveY=0;
	float m_leftBoundary=oldPoint.x>=0?oldPoint.x:-oldPoint.x;
	float m_rightBoundary=m_widthBoundary+oldPoint.x;
	float m_bottomBoundary=oldPoint.y>=0?oldPoint.y:-oldPoint.y;
	float m_topBoundary=m_heightBoundary+oldPoint.y;

	if (m_leftBoundary-pos.x<=m_widthBoundary&&m_rightBoundary+pos.x<=m_widthBoundary){
		moveX=pos.x;
	}else{
		moveX=0;
	}
	if (m_bottomBoundary-pos.y<m_heightBoundary&&m_topBoundary+pos.y<m_heightBoundary){
		moveY=pos.y;
	}else{
		moveY=0;
	}
	if (moveX==0&&moveY==0){
		return false;
	}
	_tileMap->setPosition(ccp(oldPoint.x+moveX,oldPoint.y+moveY));//移动地图  
	map_offset=ccp(oldPoint.x+moveX,oldPoint.y+moveY);
	return true;
}
void TmxTestScene::moveHero(cocos2d::CCPoint pp){
	
	CCLog("(touchx,touchy: %f   %f)",this->tileCoordForPosition(pp).x,this->tileCoordForPosition(pp).y);
	CCPoint point=_kongming->getPos();
	touchPos=pp;
	if(fabs(pp.x-point.x)>=fabs(pp.y-point.y))  
	{  
		if(pp.x>=point.x)  
		{  
			_kongming->Turn(RIGHT);
		}  
		else  
		{  
			_kongming->Turn(LEFT);
		}  
	}  
	else  
	{  
		if(pp.y>=point.y)  
		{  
			_kongming->Turn(UP);
		}  
		else  
		{  
			_kongming->Turn(DOWN);
		}  
	}  
}

void TmxTestScene::update(float delta){
	float s=_kongming->_speed*delta;
	CCPoint pos=_kongming->getPos();
	//CCLog("(hero_x,hero_y: %f   %f)",pos.x,pos.y);	
	CCPoint nowPos;
	CCPoint mapMoveDis;					//地图移动距离
	int now_state=_kongming->state;
	switch(now_state){
				case DOWN:
						nowPos=ccp(pos.x,pos.y-s);
						mapMoveDis=ccp(0,s/2);
						break;
				case LEFT:
						nowPos=ccp(pos.x-s,pos.y);
						mapMoveDis=ccp(s/2,0);
						break;
				case RIGHT:
						nowPos=ccp(pos.x+s,pos.y);
						mapMoveDis=ccp(-s/2,0);
						break;
				case UP:
						nowPos=ccp(pos.x,pos.y+s);
						mapMoveDis=ccp(0,-s/2);
						break;
	}
	if (isMove(nowPos))
	{
	       if (this->moveMap(mapMoveDis));
		  // _kongming->update(s/2);
		//   else
			_kongming->update(s);
	}
}
