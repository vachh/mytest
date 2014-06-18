#include "StartScene.h"
#include "Layer/BackgroundLayer.h"
#include "GameScene.h"
USING_NS_CC;
#include <iostream>
using namespace std;
//hehe
CCScene* StartScene::scene()
{
	CCScene *scene = CCScene::create();
	StartScene *layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCMenuItemFont::setFontSize(24);
	string helpstr="HELP";

	CCMenuItemFont *help=CCMenuItemFont::create(helpstr.c_str(),this,menu_selector(StartScene::ToHelpScene));
	help->setPosition(ccp(origin.x + visibleSize.width/2 ,
		origin.y + visibleSize.height /2-20));

	CCMenuItemFont *highscores=CCMenuItemFont::create("HIGHSCORES",this,menu_selector(StartScene::ToHelpScene));
	highscores->setPosition(ccp(origin.x + visibleSize.width/2 ,
		origin.y + visibleSize.height /2-20+help->getContentSize().height+10));

	CCMenuItemFont *begin=CCMenuItemFont::create("BEGIN",this,menu_selector(StartScene::ToGameScene));
	begin->setPosition(ccp(origin.x + visibleSize.width/2 ,
		origin.y + visibleSize.height /2-20+help->getContentSize().height+highscores->getContentSize().height+20));



	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(help,highscores,begin,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);//创建菜单并添加到层


	CCLabelTTF* pLabel = CCLabelTTF::create("SUPER", "Arial", 30);//创建helloworld并添加到层
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2-pLabel->getContentSize().width/2-10,
		origin.y + visibleSize.height - pLabel->getContentSize().height*2));
	this->addChild(pLabel, 1);

	CCLabelTTF* pLabel2= CCLabelTTF::create("JUMPER", "Arial", 30);//创建helloworld并添加到层
	pLabel2->setPosition(ccp(origin.x + visibleSize.width/2+pLabel2->getContentSize().width/2+10,
		origin.y + visibleSize.height - pLabel2->getContentSize().height*2));
	this->addChild(pLabel2, 1);



	// add "HelloWorld" splash screen"
	_backgroundLayer=BackgroundLayer::create();
	_walkman=walkman::create();
	this->addChild(_walkman,2);
	this->addChild(_backgroundLayer,0);
	//this->scheduleUpdate();
	return true;
}

void StartScene::ToHelpScene(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
void StartScene::ToGameScene(CCObject* pSender)
{
	CCScene *gameScene = GameScene::create();
	CCLog("gameScene's count:		");
	CCLog("%d",gameScene->retainCount());
	CCDirector::sharedDirector()->replaceScene(gameScene);
}
