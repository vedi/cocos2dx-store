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

#include "StoreAScene.h"
#include "GameMenuItem.h"
#include "MainScene.h"
#include "StoreBScene.h"
#include "Soomla/PurchaseTypes/CCPurchaseWithMarket.h"
#include "Soomla/CCStoreController.h"
#include "Soomla/domain/CCPurchasableVirtualItem.h"
#include "Soomla/CCStoreInventory.h"
#include "Soomla/CCStoreUtils.h"
#include "Soomla/data/CCStoreInfo.h"
#include "Soomla/PurchaseTypes/CCPurchaseWithVirtualItem.h"

USING_NS_CC;
using namespace soomla;

/**
 * This is the first scene (the window where the VirtualGoods are shown).
 * In this file you can find example calls to the store's interfaces.
 **/


CCLabelTTF* StoreAScene::goodsPriceBalanceLabels[];
CCLabelTTF* StoreAScene::pLabelBalance;

CCScene* StoreAScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    StoreAScene *layer = StoreAScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StoreAScene::init()
{
    CCStoreController::sharedStoreController()->storeOpening();

    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(255,255,255,255)))
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCLabelTTF* pLabelTitleTest = CCLabelTTF::create("Soomla Test Store", "GoodDog.otf", 34);
    pLabelTitleTest->setColor(ccc3(255,0,0));
    pLabelTitleTest->setPosition(ccp(pLabelTitleTest->boundingBox().size.width/2 + origin.x + 20, visibleSize.height - 30 + origin.y));
    this->addChild(pLabelTitleTest, 1);

    CCLabelTTF* pLabelTitle = CCLabelTTF::create("Virtual Goods", "GoodDog.otf", 54);
    pLabelTitle->setColor(ccc3(0,0,0));
    pLabelTitle->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height - 100 + origin.y));
    this->addChild(pLabelTitle, 1);


    CCSprite* pSpriteMuffin = CCSprite::create("muffin.png");
    pSpriteMuffin->setScale(0.5f);
    pSpriteMuffin->setPosition(ccp(origin.x + visibleSize.width - 90, visibleSize.height + origin.y - 50));
    this->addChild(pSpriteMuffin, 0);

    pLabelBalance = CCLabelTTF::create("0", "GoodDog.otf", 34);
    pLabelBalance->setColor(ccc3(0,255,255));
    pLabelBalance->setPosition(ccp(origin.x + visibleSize.width - 40, visibleSize.height + origin.y - 50));
    this->addChild(pLabelBalance, 1);
    setCurrencyBalanceLabel();

    GameMenuItem* getMoreItem = GameMenuItem::itemWithLabel(
            CCSprite::create("get_more.png"),
            this,
            menu_selector(StoreAScene::menuGetMoreCallback));

    getMoreItem->setPosition(ccp(origin.x + visibleSize.width/2 + (getMoreItem->boundingBox().size.width /2) + 10, 110));


    GameMenuItem* backItem = GameMenuItem::itemWithLabel(
            CCSprite::create("back.png"),
            this,
            menu_selector(StoreAScene::menuBackCallback));

    backItem->setPosition(ccp(origin.x + visibleSize.width/2 - (backItem->boundingBox().size.width /2) - 10 , 110));

    // In Game Menu
    CCMenu* menu = CCMenu::create(getMoreItem, backItem, NULL);

    createListViewItem(origin, menu, visibleSize, 0, "fruit_cake.png");
    createListViewItem(origin, menu, visibleSize, 1, "pavlova.png");
    createListViewItem(origin, menu, visibleSize, 2, "cream_cup.png");
    createListViewItem(origin, menu, visibleSize, 3, "chocolate_cake.png");

    menu->setPosition(CCPointZero);
    this->addChild(menu);

    this->setKeypadEnabled(true);

    return true;
}

void StoreAScene::menuBackCallback(CCObject* pSender)
{
    CCStoreController::sharedStoreController()->storeClosing();

    CCScene *s = MainScene::scene();
    CCDirector::sharedDirector()->setDepthTest(true);
    CCTransitionScene *transition = CCTransitionMoveInL::create(0.8f, s);

    CCDirector::sharedDirector()->replaceScene(transition);
}

void StoreAScene::menuGetMoreCallback(CCObject* pSender)
{
    CCScene *s = StoreBScene::scene();
    CCDirector::sharedDirector()->setDepthTest(true);
    CCTransitionScene *transition = CCTransitionMoveInR::create(0.8f, s);

    CCDirector::sharedDirector()->replaceScene(transition);
}

void StoreAScene::menuChooseCallback(CCObject* pSender)
{
    if (pSender) {
        GameMenuItem* item = (GameMenuItem*)pSender;

        CCSoomlaError *soomlaError = NULL;
        CCPurchasableVirtualItem *purchasableVirtualItem = (CCPurchasableVirtualItem *)item->getUserObject();
        CCStoreInventory::sharedStoreInventory()->buyItem(
                purchasableVirtualItem->getItemId()->getCString(), &soomlaError);
        if (soomlaError) {
            CCStoreUtils::logException("StoreAScene::menuChooseCallback", soomlaError);
        }
    }
}

void StoreAScene::createListViewItem(CCPoint& origin, CCMenu* menu, CCSize& visibleSize, int tag, const char* img) {
    GameMenuItem *pChooseItem = GameMenuItem::itemWithLabel(
            CCSprite::create("button.png"),
            this,
            menu_selector(StoreAScene::menuChooseCallback));

    string itemId = itemIdFromTag(tag);

    CCSoomlaError *soomlaError = NULL;
    CCVirtualItem *virtualItem = CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId.c_str(), &soomlaError);
    if (soomlaError) {
        CCStoreUtils::logException("StoreAScene::createListViewItem", soomlaError);
        return;
    }
    CC_ASSERT(virtualItem);
    string nameS = virtualItem->getName()->getCString();
    string infoS = virtualItem->getDescription()->getCString();
    CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(virtualItem);
    CC_ASSERT(purchasableVirtualItem);
    CCPurchaseWithVirtualItem *purchaseWithVirtualItem = dynamic_cast<CCPurchaseWithVirtualItem *>(purchasableVirtualItem->getPurchaseType());
    CC_ASSERT(purchaseWithVirtualItem);
    int price = purchaseWithVirtualItem->getAmount()->getValue();
    pChooseItem->setUserObject(purchasableVirtualItem);

    int balance = 0;
    const char * name = nameS.c_str();
    const char * info = infoS.c_str();

    float yOffset = - 200;

    pChooseItem->setPosition(ccp(origin.x + visibleSize.width/2, yOffset + origin.y + visibleSize.height - 100 - (tag * pChooseItem->boundingBox().size.height)));
    pChooseItem->setTag(tag);


    CCSprite* pSpritePic = CCSprite::create(img);
    pSpritePic->setPosition(ccp(pSpritePic->boundingBox().size.width/2 + 20, pChooseItem->boundingBox().size.height/2));
    pChooseItem->addChild(pSpritePic, 0);


    CCLabelTTF* pLabelName = CCLabelTTF::create(name, "GoodDog.otf", 44);
    pLabelName->setColor(ccc3(0,0,0));
    pLabelName->setPosition(ccp(pSpritePic->getPositionX() + (pSpritePic->boundingBox().size.width / 2) + (pLabelName->boundingBox().size.width / 2) + 20 , pChooseItem->boundingBox().size.height/2));
    pChooseItem->addChild(pLabelName);


    CCLabelTTF* pLabelInfo = CCLabelTTF::create(info, "GoodDog.otf", 20);
    pLabelInfo->setColor(ccc3(50,50,50));
    pLabelInfo->setPosition(ccp(pSpritePic->getPositionX() + (pSpritePic->boundingBox().size.width / 2) + (pLabelInfo->boundingBox().size.width / 2) + 20 , -50 + (pChooseItem->boundingBox().size.height/2)));
    pChooseItem->addChild(pLabelInfo);


    CCLabelTTF* pLabelClickToBuy = CCLabelTTF::create("Click to Buy", "GoodDog.otf", 24);
    pLabelClickToBuy->setColor(ccc3(0,255,255));
    pLabelClickToBuy->setPosition(ccp(pChooseItem->boundingBox().size.width - (pLabelClickToBuy->boundingBox().size.width / 2) - 20 , 60 + pChooseItem->boundingBox().size.height/2));
    pChooseItem->addChild(pLabelClickToBuy);

    char buffer[512];

    snprintf(buffer, sizeof(buffer), "price: %d blanace: %d",  price, balance);

    goodsPriceBalanceLabels[tag] = CCLabelTTF::create(buffer, "GoodDog.otf", 24);
    goodsPriceBalanceLabels[tag]->setColor(ccc3(0,255,255));
    goodsPriceBalanceLabels[tag]->setPosition(ccp(pChooseItem->boundingBox().size.width - (goodsPriceBalanceLabels[tag]->boundingBox().size.width / 2) - 20 , 60));
    pChooseItem->addChild(goodsPriceBalanceLabels[tag]);

    menu->addChild(pChooseItem, 1);

    setPriceBalanceLabel(itemId.c_str());
}

void StoreAScene::setCurrencyBalanceLabel() {
    if (!pLabelBalance) {
        return;
    }

    CCSoomlaError *soomlaError = NULL;
    int balance = CCStoreInventory::sharedStoreInventory()->getItemBalance("currency_muffin", &soomlaError);
    if (soomlaError) {
        CCStoreUtils::logException("StoreAScene::setCurrencyBalanceLabel", soomlaError);
        balance = 0;
    }

    ostringstream convert;
    convert << balance;
    pLabelBalance->setString(convert.str().c_str());
}

void StoreAScene::setPriceBalanceLabel(const char* itemId) {
    int tag = tagFromItemId(itemId);
    CCSoomlaError *soomlaError = NULL;
    int balance = CCStoreInventory::sharedStoreInventory()->getItemBalance(itemId, &soomlaError);
    if (soomlaError) {
        CCStoreUtils::logException("StoreAScene::setPriceBalanceLabel", soomlaError);
        balance = 0;
    }

    ostringstream convert;
    convert << balance;

    const char* priceBalanceCA = goodsPriceBalanceLabels[tag]->getString();
    string priceBalance(priceBalanceCA);
    size_t found = priceBalance.find_last_of(":");
    priceBalance = priceBalance.substr(0, found+2);
    priceBalance += convert.str();

    goodsPriceBalanceLabels[tag]->setString(priceBalance.c_str());
}

int StoreAScene::tagFromItemId(const char* itemId) {
    string itemIdStr(itemId);
    if (itemIdStr == "fruit_cake") return 0;
    if (itemIdStr == "pavlova") return 1;
    if (itemIdStr == "cream_cup") return 2;
    if (itemIdStr == "chocolate_cake") return 3;

    return 0;
}

string StoreAScene::itemIdFromTag(int tag) {
    string ret;
    switch (tag) {
        case 0:
            ret = "fruit_cake";
            return ret;
        case 1:
            ret = "pavlova";
            return ret;
        case 2:
            ret = "cream_cup";
            return ret;
        case 3:
            ret = "chocolate_cake";
            return ret;
        default:
            ret = "ERROR";
            return ret;
    }
}



