#include "MainScene.h"
#include "StoreAScene.h"
#include "cocos2dx_StoreController.h"

USING_NS_CC;

Soomla* Soomla::create(const char *pszFileName, CCSprite* pSpriteBox)
{
	Soomla *pobSprite = new Soomla();
	pobSprite->mSpriteBox = pSpriteBox;

	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void Soomla::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void Soomla::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}
CCRect Soomla::rect()
{
    CCSize s = this->getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool Soomla::containsTouchLocation(CCTouch* touch)
{
	 return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Soomla::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	mOriginalPos = this->getPosition();
	return true;
}

void Soomla::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocation();    
    setPosition(touchPoint);
}

void Soomla::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCRect rect1 = this->boundingBox();
	CCRect rect2 = this->mSpriteBox->boundingBox();
	
	if (rect1.intersectsRect(rect2))
	{		
		CCScene *s = StoreAScene::scene();
		CCDirector::sharedDirector()->setDepthTest(true);
		CCTransitionScene *transition = CCTransitionMoveInR::create(0.8f, s);
	
		CCDirector::sharedDirector()->replaceScene(transition);
	}
	else
	{
		// Snap
		this->runAction(CCMoveTo::create(0.2f, mOriginalPos));
	}
}

CCScene* MainScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MainScene *layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	CCSprite* bgSprite = CCSprite::create("img_direct.jpg");
	bgSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bgSprite);

	CCLabelTTF* pLabelTitle = CCLabelTTF::create("SOOMLA Store\nExample", "GoodDog.otf", 54);
	pLabelTitle->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height - 100 + origin.y));
	this->addChild(pLabelTitle, 1);

	CCLabelTTF* pLabelGame = CCLabelTTF::create("[YOUR GAME HERE]", "GoodDog.otf", 54);
	pLabelGame->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 - 0 + origin.y));
	this->addChild(pLabelGame, 1);

	pRightBox = CCSprite::create("right_bg.png");
	pRightBox->setScale(2.0f);
	pRightBox->setPosition(ccp(origin.x + visibleSize.width - (pRightBox->boundingBox().size.width / 2) - 50, 250 + origin.y));
	this->addChild(pRightBox, 0);

	Soomla* pSoomla = Soomla::create("soomla_logo_new.png", pRightBox);
	pSoomla->setScale(2.0f);
	pSoomla->setPosition(ccp(origin.x + (pSoomla->boundingBox().size.width / 2) + 50, 250 + origin.y));
	this->addChild(pSoomla, 0);


	CCLabelTTF* pLabelInstructions = CCLabelTTF::create("Drag the SooMLA-bot to the box top open store", "GoodDog.otf", 24);
	pLabelInstructions->setPosition(ccp(visibleSize.width/2 + origin.x, 100 + origin.y));
	this->addChild(pLabelInstructions, 1);

	this->setKeypadEnabled(true);

	return true;
}
