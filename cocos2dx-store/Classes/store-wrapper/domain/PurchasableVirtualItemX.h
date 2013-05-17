//
//  PurchasableVirtualItem.h
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#ifndef __cocos2dx_store__PurchasableVirtualItem__
#define __cocos2dx_store__PurchasableVirtualItem__

#include "VirtualItemX.h"
#include "PurchaseTypeX.h"

namespace soomla {
    
    class PurchasableVirtualItem : public VirtualItem {
        SL_SYNTHESIZE_RETAIN(PurchaseType*, mPurchaseType, PurchaseType);
        
    public:
        PurchasableVirtualItem(): VirtualItem(), mPurchaseType(NULL) {}
        
        virtual bool init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, PurchaseType* purchaseType);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);
        
        static PurchasableVirtualItem* create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId, PurchaseType* purchaseType);
        static PurchasableVirtualItem* createWithDictionary(cocos2d::CCDictionary* dict);
        
        virtual ~PurchasableVirtualItem();
        
        virtual cocos2d::CCDictionary* toDictionary() const;
    };
}

#endif /* defined(__cocos2dx_store__PurchasableVirtualItem__) */
