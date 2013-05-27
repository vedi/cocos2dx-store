//
//  PurchaseTypeX.h
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#ifndef __cocos2dx_store__PurchaseTypeX__
#define __cocos2dx_store__PurchaseTypeX__

#include "cocos2d.h"

namespace soomla {
    
    class CCPurchaseType : public cocos2d::CCObject {
    public:
        CCPurchaseType() {}
        
        virtual bool init();
        
        static CCPurchaseType * create();
        
        virtual ~CCPurchaseType();
    };
    
}

#endif /* defined(__cocos2dx_store__PurchaseTypeX__) */
