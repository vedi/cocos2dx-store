#include "AppDelegate.h"
#include "MainScene.h"
#include "StoreBridge/cocos2dx_StoreController.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    cocos2dx_StoreController::initialize(true);
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
	
    
    TargetPlatform target = getTargetPlatform();
    
    if (target == kTargetIpad)
    {
        // ipad
        
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        
        // don't enable retina because we don't have ipad hd resource
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionNoBorder);
    }
    else if (target == kTargetIphone)
    {
        // iphone
        
//        if (pDirector->enableRetinaDisplay(true))
//        {
            // iphone hd
            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
//        }
//        else
//        {
//            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
//        }
        
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(720, 1280, kResolutionNoBorder);
    }
    else 
    {
        // android, windows, blackberry, linux or mac
        // use 960*640 resources as design resolution size
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(720, 1280, kResolutionNoBorder);
    }

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = MainScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
