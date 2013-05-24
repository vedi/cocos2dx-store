//
// Created by Fedor Shubin on 5/21/13.
//

#ifndef __CCStoreInventory_H_
#define __CCStoreInventory_H_

#include "cocos2d.h"
#include "CCSoomlaError.h"

namespace soomla {
    class CCStoreInventory: public cocos2d::CCObject {
    public:
        static CCStoreInventory* sharedStoreInventory();
        CCStoreInventory(void);
        virtual ~CCStoreInventory(void);
        virtual bool init();

        void buyItem(const char *itemId, CCSoomlaError **soomlaError);

        int getItemBalance(const char *itemId, CCSoomlaError **soomlaError);
        void giveItem(const char *itemId, int amount, CCSoomlaError **soomlaError);
        void takeItem(const char *itemId, int amount, CCSoomlaError **soomlaError);

        void equipVirtualGood(const char *itemId, CCSoomlaError **soomlaError);
        void unEquipVirtualGood(const char *itemId, CCSoomlaError **soomlaError);
        bool isVirtualGoodEquipped(const char *itemId, CCSoomlaError **soomlaError);

        int getGoodUpgradeLevel(const char *goodItemId, CCSoomlaError **soomlaError);
        std::string getGoodCurrentUpgrade(const char *goodItemId, CCSoomlaError **soomlaError);
        void upgradeGood(const char *goodItemId, CCSoomlaError **soomlaError);
        void removeGoodUpgrades(const char *goodItemId, CCSoomlaError **soomlaError);

        bool nonConsumableItemExists(const char *nonConsItemId, CCSoomlaError **soomlaError);
        void addNonConsumableItem(const char *nonConsItemId, CCSoomlaError **soomlaError);
        void removeNonConsumableItem(const char *nonConsItemId, CCSoomlaError **soomlaError);
    };
};

#endif //__CCStoreInventory_H_
