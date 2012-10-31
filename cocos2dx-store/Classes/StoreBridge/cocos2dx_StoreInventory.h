//
//  cocos2dx_StoreInventory.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/24/12.
//
//

#ifndef __cocos2dx_store__cocos2dx_StoreInventory__
#define __cocos2dx_store__cocos2dx_StoreInventory__

#include <iostream>
#include <string>
#include "cocos2dx_VirtualItemNotFoundException.h"

using namespace std;

class cocos2dx_StoreInventory {

public:
    
    static int getCurrencyBalance(string currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static int addCurrencyAmount(string currencyItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&);
    static int removeCurrencyAmount(string currencyItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&);
    static int getGoodBalance(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static int addGoodAmount(string goodItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&);
    static int removeGoodAmount(string goodItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&);
    
};

#endif
