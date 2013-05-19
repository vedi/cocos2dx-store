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
    
    class PurchaseType : public cocos2d::CCObject {
    public:
        PurchaseType() {}
        
        virtual bool init();
        
        static PurchaseType* create();
        
        virtual ~PurchaseType();
    };
    
}

#endif /* defined(__cocos2dx_store__PurchaseTypeX__) */
