//
// Created by Fedor Shubin on 5/21/13.
//

#ifndef __CCStoreInventory_H_
#define __CCStoreInventory_H_

#include "cocos2d.h"

namespace soomla {
    class CCStoreInventory: public cocos2d::CCObject  {
    public:
        static CCStoreInventory* sharedStoreInventory();
        CCStoreInventory(void);
        virtual ~CCStoreInventory(void);
        virtual bool init();

        void buyItem(const char *itemId);

        int getItemBalance(const char *itemId);
        void giveItem(const char *itemId, int amount);
        void takeItem(const char *itemId, int amount);

        void equipVirtualGood(const char *itemId);
        void unEquipVirtualGood(const char *itemId);
        bool isVirtualGoodEquipped(const char *itemId);

        int getGoodUpgradeLevel(const char *goodItemId);
        std::string getGoodCurrentUpgrade(const char *goodItemId);
        void upgradeGood(const char *goodItemId);
        void removeGoodUpgrades(const char *goodItemId);

        bool nonConsumableItemExists(const char *nonConsItemId);
        void addNonConsumableItem(const char *nonConsItemId);
        void removeNonConsumableItem(const char *nonConsItemId);
    };
};

#endif //__CCStoreInventory_H_
