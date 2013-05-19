//
//  PurchaseTypeX.cpp
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#include "PurchaseTypeX.h"

namespace soomla {
    
    bool PurchaseType::init() {
        return true;
    }
    
    PurchaseType* PurchaseType::create() {
        PurchaseType* pRet = new PurchaseType();
        if (pRet) {
            pRet->autorelease();
            pRet->init();
        }
        return pRet;
    }
    
    PurchaseType::~PurchaseType() {}
}