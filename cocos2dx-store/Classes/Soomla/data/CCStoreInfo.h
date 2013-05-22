//
// Created by Fedor Shubin on 5/21/13.
//


#ifndef __CCStoreInfo_H_
#define __CCStoreInfo_H_

#include "cocos2d.h"
#include "CCIStoreAssets.h"
#include "CCVirtualItem.h"
#include "CCUpgradeVGX.h"
#include "CCVirtualCategory.h"

namespace soomla {
    class CCStoreInfo: cocos2d::CCObject {
    public:
        static CCStoreInfo *sharedStoreController();
        static void createShared(CCIStoreAssets *storeAssets);
        virtual bool init(CCIStoreAssets *storeAssets);

        CCVirtualItem *getItemByItemId(const char *itemId);
        CCPurchasableVirtualItem *getPurchasableItemWithProductId(const char *productId);
        CCVirtualCategory *getCategoryForVirtualGood(const char *goodItemId);
        CCUpgradeVG *getFirstUpgradeForVirtualGood(const char *goodItemId);
        CCUpgradeVG *getLastUpgradeForVirtualGood(const char *goodItemId);
        cocos2d::CCArray *getUpgradesForVirtualGood(const char *goodItemId);
        cocos2d::CCArray *getVirtualCurrencies();
        cocos2d::CCArray *getVirtualGoods();
        cocos2d::CCArray *getVirtualCurrencyPacks();
        cocos2d::CCArray *getNonConsumableItems();
        cocos2d::CCArray *getVirtualCategories();

    };
};

#endif //__CCStoreInfo_H_
