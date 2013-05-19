//
//  VirtualCurrencyX.h
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#ifndef __cocos2dx_store__VirtualCurrencyX__
#define __cocos2dx_store__VirtualCurrencyX__

#include "CCVirtualItem.h"

namespace soomla {
    
    class VirtualCurrency : public CCVirtualItem {
    public:
        VirtualCurrency(): CCVirtualItem() {}
        
        static VirtualCurrency* create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId);
        static VirtualCurrency* createWithDictionary(cocos2d::CCDictionary* dict);
    };
}

#endif /* defined(__cocos2dx_store__VirtualCurrencyX__) */
