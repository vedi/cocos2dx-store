//
// Created by Fedor Shubin on 5/20/13.
//



#include "cocoa/CCArray.h"

#ifndef __CCIStoreAssets_H_
#define __CCIStoreAssets_H_

namespace soomla {
    class CCIStoreAssets: public cocos2d::CCObject {
    public:
        virtual int getVersion() = 0;

        virtual cocos2d::CCArray *getCurrencies() = 0;
        virtual cocos2d::CCArray *getGoods() = 0;
        virtual cocos2d::CCArray *getCurrencyPacks() = 0;
        virtual cocos2d::CCArray *getCategories() = 0;
        virtual cocos2d::CCArray *getNonConsumableItems() = 0;
    };
};

#endif //__CCIStoreAssets_H_
