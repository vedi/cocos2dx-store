//
//  VirtualCurrencyX.cpp
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#include "CCVirtualCurrency.h"

namespace soomla {
    
    VirtualCurrency* VirtualCurrency::create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId) {
        VirtualCurrency* pRet = new VirtualCurrency();
        if (pRet) {
            pRet->autorelease();
            pRet->init(name, description, itemId);
        }
        return pRet;
    }
    
    VirtualCurrency* VirtualCurrency::createWithDictionary(cocos2d::CCDictionary* dict) {
        VirtualCurrency* pRet = new VirtualCurrency();
        if (pRet) {
            pRet->autorelease();
            pRet->initWithDictionary(dict);
        }
        return pRet;
    }
}