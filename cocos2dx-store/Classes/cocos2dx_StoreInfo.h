//
//  cocos2dx_StoreInfo.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/28/12.
//
//

#ifndef __cocos2dx_store__cocos2dx_StoreInfo__
#define __cocos2dx_store__cocos2dx_StoreInfo__

#include <iostream>
#include "cocos2dx_VirtualItemNotFoundException.h"
#include <string>

using namespace std;

class cocos2dx_StoreInfo {
public:
    
    static string getPackProductId(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static string getPackName(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static string getPackDescription(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static double getPackPrice(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static string getGoodName(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static string getGoodDescription(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&);
    static int getGoodPriceForCurrency(const char* goodItemId, const char* currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&);

};


#endif /* defined(__cocos2dx_store__cocos2dx_StoreInfo__) */
