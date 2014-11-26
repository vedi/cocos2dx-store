/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef __CCVirtualGoodsStorage_H__
#define __CCVirtualGoodsStorage_H__

#include "CCVirtualItemStorage.h"
#include "CCVirtualGood.h"
#include "CCUpgradeVG.h"
#include "CCEquippableVG.h"

namespace soomla {
    class CCVirtualGoodsStorage : public CCVirtualItemStorage {
    public:
        static CCVirtualGoodsStorage* getInstance();
        
        CCVirtualGoodsStorage();
        
        virtual ~CCVirtualGoodsStorage();
        
        virtual void removeUpgrades(CCVirtualGood *good, CCError **error = NULL) { removeUpgrades(good, true, error); }
        virtual void removeUpgrades(CCVirtualGood *good, bool notify, CCError **error = NULL);
        
        virtual void assignCurrentUpgrade(CCVirtualGood *good, CCUpgradeVG *upgradeVG, CCError **error = NULL) { assignCurrentUpgrade(good, upgradeVG, true, error); }
        virtual void assignCurrentUpgrade(CCVirtualGood *good, CCUpgradeVG *upgradeVG, bool notify, CCError **error = NULL);
        
        virtual CCUpgradeVG *getCurrentUpgrade(CCVirtualGood *good, CCError **error = NULL);
        virtual bool isEquipped(CCEquippableVG *good, CCError **error = NULL);
        
        virtual void equip(CCEquippableVG *good, CCError **error = NULL) { equip(good, true, error); }
        virtual void equip(CCEquippableVG *good, bool notify, CCError **error = NULL);
        
        virtual void unequip(CCEquippableVG *good, CCError **error = NULL) { unequip(good, true, error); }
        virtual void unequip(CCEquippableVG *good, bool notify, CCError **error = NULL);
        
    protected:
        virtual const char* keyBalance(const char *itemId) const;
        virtual void postBalanceChangeEvent(CCVirtualItem *item, int balance, int amountAdded);
        
    private:
        void equipPriv(CCEquippableVG *good, bool equip, bool notify, CCError **error = NULL);
        
        static const char *keyGoodBalance(const char *itemId);
        static const char *keyGoodEquipped(const char *itemId);
        static const char *keyGoodUpgrade(const char *itemId);
    };
}

#endif // __CCVirtualGoodsStorage_H__
