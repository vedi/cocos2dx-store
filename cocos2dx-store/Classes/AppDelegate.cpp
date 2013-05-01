/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "AppDelegate.h"
#include "MainScene.h"
#include "StoreBridge/cocos2dx_StoreController.h"
#include "StoreBridge/cocos2dx_EventHandlers.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
	handler = new EventHandler();
}

AppDelegate::~AppDelegate() 
{
	cocos2dx_EventHandlers::getInstance()->removeHandler(handler);
	delete handler;
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    /**
     * The initialization of StoreController. This is the first and ONLY time it's initialized.
     **/
    cocos2dx_StoreController::initialize("ExampleCustomSecret");
	cocos2dx_EventHandlers::getInstance()->addHandler(handler);
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
	
    
    TargetPlatform target = getTargetPlatform();
	
	std::vector<std::string> searchPaths;
	searchPaths.push_back("iphonehd");
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    
    if (target == kTargetIpad)
    {
        // ipad
        // CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        
        // don't enable retina because we don't have ipad hd resource
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(720, 1280, kResolutionNoBorder);
    }
    else if (target == kTargetIphone)
    {
        // iphone
        
//        if (pDirector->enableRetinaDisplay(true))
//        {
            // iphone hd
            // CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
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
		
        // CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
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
