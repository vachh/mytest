#include "AppDelegate.h"
#include "TmxTestScene.h"
USING_NS_CC;
#include<iostream>
using namespace std;
#include <string>
//nihao
class LifeCircleLogger{
	string m_msg;
public:
	LifeCircleLogger(){}
	LifeCircleLogger(const string& msg):m_msg(msg){
		CCLog("%s BEGINS",m_msg.c_str());
	}
	~LifeCircleLogger(){
		CCLog("%s ENDS",m_msg.c_str());
	}
};
#define  LOG_FUNCTION_LIFE LifeCircleLogger(__FUNCTION__);
AppDelegate::AppDelegate() {
	LOG_FUNCTION_LIFE
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {		//应用程序启动后将调用这个方法
	
	// initialize director初始化游戏引擎控制器CCDirector，以便启动游戏引擎
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this设置帧绘制时间
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = TmxTestScene::create();

    // run
    pDirector->runWithScene(pScene);
	LOG_FUNCTION_LIFE
    return true;

}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {	//暂停
    CCDirector::sharedDirector()->stopAnimation();
	LOG_FUNCTION_LIFE
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {	//恢复
    CCDirector::sharedDirector()->startAnimation();
	LOG_FUNCTION_LIFE
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
