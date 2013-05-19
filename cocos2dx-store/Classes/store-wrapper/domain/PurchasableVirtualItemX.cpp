//
//  PurchasableVirtualItem.cpp
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#include "PurchasableVirtualItemX.h"
#include "PurchaseWithVirtualItemX.h"
#include "PurchaseWithMarketX.h"
#include "MarketItemX.h"

namespace soomla {
    
    using namespace cocos2d;
    
    bool PurchasableVirtualItem::init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, PurchaseType* purchaseType) {
        bool bRet = VirtualItem::init(name, description, itemId);
        if (bRet) {
            setPurchaseType(purchaseType);
        }
        return bRet;
    }
    
    bool PurchasableVirtualItem::initWithDictionary(cocos2d::CCDictionary* dict) {
        bool bRet = VirtualItem::initWithDictionary(dict);
        if (bRet) {
            fillPurchaseTypeFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    PurchasableVirtualItem* PurchasableVirtualItem::create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, PurchaseType* purchaseType) {
        PurchasableVirtualItem* pRet = new PurchasableVirtualItem();
        if (pRet) {
            pRet->autorelease();
            pRet->init(name, description, itemId, purchaseType);
        }
        return pRet;
    }

    PurchasableVirtualItem* PurchasableVirtualItem::createWithDictionary(cocos2d::CCDictionary* dict) {
        PurchasableVirtualItem* pRet = new PurchasableVirtualItem();
        if (pRet) {
            pRet->autorelease();
            pRet->initWithDictionary(dict);
        }
        return pRet;
    }
    
    PurchasableVirtualItem::~PurchasableVirtualItem() {
        CC_SAFE_RELEASE(mPurchaseType);
    }
    
    cocos2d::CCDictionary* PurchasableVirtualItem::toDictionary() {
        CCDictionary* dict = VirtualItem::toDictionary();

        putPurchaseTypeToDict(dict);

        return dict;
    }

    void PurchasableVirtualItem::fillPurchaseTypeFromDict(CCDictionary *dict) {
        CCString* purchaseTypeStr = dynamic_cast<CCString *>(dict->objectForKey(JSON_PURCHASE_TYPE));
        CCAssert(purchaseTypeStr == NULL, "invalid object type in dictionary");
        CCDictionary *purchasableDict = dynamic_cast<CCDictionary *>(dict->objectForKey(JSON_PURCHASABLE_ITEM));
        CC_ASSERT(purchasableDict);
        if (purchaseTypeStr->compare(JSON_PURCHASE_TYPE_MARKET) == 0) {
            CCDictionary *marketItemDict = dynamic_cast<CCDictionary *>(purchasableDict->objectForKey(JSON_PURCHASE_MARKET_ITEM));
            CC_ASSERT(marketItemDict);
            setPurchaseType(PurchaseWithMarket::create(MarketItem::createWithDictionary(marketItemDict)));
        } else if (purchaseTypeStr->compare(JSON_PURCHASE_TYPE_VI) == 0) {
            CCString *itemId = dynamic_cast<CCString *>(purchasableDict->objectForKey(JSON_PURCHASE_VI_ITEMID));
            CC_ASSERT(itemId);
            CCInteger *amount = dynamic_cast<CCInteger *>(purchasableDict->objectForKey(JSON_PURCHASE_VI_AMOUNT));
            CC_ASSERT(amount);

            setPurchaseType(PurchaseWithVirtualItem::create(itemId, amount));
        } else {
            CCLog("Couldn't determine what type of class is the given purchaseType.");
        }
    }

    void PurchasableVirtualItem::putPurchaseTypeToDict(CCDictionary *dict) {
        CCDictionary *purchasableObj = CCDictionary::create();

        if (dynamic_cast<PurchaseWithMarket *>(mPurchaseType)) {
            purchasableObj->setObject(CCString::create(JSON_PURCHASE_TYPE_MARKET), JSON_PURCHASE_TYPE);

            PurchaseWithMarket *purchaseWithMarket = (PurchaseWithMarket *)mPurchaseType;
            MarketItem *mi = purchaseWithMarket->getMarketItem();
            purchasableObj->setObject(mi->toDictionary(), JSON_PURCHASE_MARKET_ITEM);
        }
        else if (dynamic_cast<PurchaseWithVirtualItem *>(mPurchaseType)) {
            PurchaseWithVirtualItem *purchaseWithVirtualItem = (PurchaseWithVirtualItem *)mPurchaseType;
            purchasableObj->setObject(CCString::create(JSON_PURCHASE_TYPE_VI), JSON_PURCHASE_TYPE);
            purchasableObj->setObject(purchaseWithVirtualItem->getItemId(), JSON_PURCHASE_VI_ITEMID);
            purchasableObj->setObject(purchaseWithVirtualItem->getAmount(), JSON_PURCHASE_VI_AMOUNT);
        }

        dict->setObject(purchasableObj, JSON_PURCHASABLE_ITEM);
    }


}