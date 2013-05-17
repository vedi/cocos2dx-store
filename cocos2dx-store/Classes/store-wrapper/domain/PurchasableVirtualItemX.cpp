//
//  PurchasableVirtualItem.cpp
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#include "PurchasableVirtualItemX.h"

namespace soomla {
    
    using namespace cocos2d;
    
    bool PurchasableVirtualItem::init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, PurchaseType* purchaseType) {
        bool bRet = VirtualItem::init(name, description, itemId);
        if (bRet) {
            setPurchaseType(purchaseType);
            mPurchaseType->mAssociatedItem = this;
        }
        return bRet;
    }
    
    bool PurchasableVirtualItem::initWithDictionary(cocos2d::CCDictionary* dict) {
        bool bRet = VirtualItem::initWithDictionary(dict);
        if (bRet) {
            //TODO: finish this
        }
        return bRet;
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
    
    cocos2d::CCDictionary* PurchasableVirtualItem::toDictionary() const {
        CCDictionary* dict = VirtualItem::toDictionary();
        //TODO: finish this
        return dict;
    }
}