//
//  CCPurchasableVirtualItem.h
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#ifndef __cocos2dx_store__PurchasableVirtualItem__
#define __cocos2dx_store__PurchasableVirtualItem__

#include "CCVirtualItem.h"
#include "CCPurchaseType.h"

namespace soomla {
    
    class CCPurchasableVirtualItem : public CCVirtualItem {
        SL_SYNTHESIZE_RETAIN_WITH_DICT_DCL(CCPurchaseType*, mPurchaseType, PurchaseType);
    public:
        CCPurchasableVirtualItem(): CCVirtualItem(), mPurchaseType(NULL) {}

        static CCPurchasableVirtualItem * create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        static CCPurchasableVirtualItem * createWithDictionary(cocos2d::CCDictionary* dict);

        virtual bool init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);
        
        virtual ~CCPurchasableVirtualItem();
        
        virtual cocos2d::CCDictionary* toDictionary();
    };
}

#endif /* defined(__cocos2dx_store__PurchasableVirtualItem__) */
