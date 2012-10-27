#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Soomla : public CCSprite, public CCTargetedTouchDelegate
{
public:

    static Soomla* create(const char *pszFileName, CCSprite* pSpriteBox);

	virtual void onEnter();
    virtual void onExit();
	CCRect rect();
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

private:

	CCSprite* mSpriteBox;
	CCPoint mOriginalPos;
};

class MainScene : public cocos2d::CCLayer
{
private:
	CCSprite* pRightBox;
	
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainScene);

	// The back key clicked
    virtual void keyBackClicked()
	{
		CCDirector::sharedDirector()->end();
	}
};

#endif // __MainScene_SCENE_H__
