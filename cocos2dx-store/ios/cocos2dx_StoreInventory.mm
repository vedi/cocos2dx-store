//
//  cocos2dx_StoreInventory.mm
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/27/12.
//
//

#include "cocos2dx_StoreInventory.h"
#import "StoreInventory.h"
#import "AnalyticXStringUtil.h"
#import "VirtualItemNotFoundException.h"

int cocos2dx_StoreInventory::getCurrencyBalance(string currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString *str = [AnalyticXStringUtil nsstringFromCString:currencyItemId.c_str()];
        return [StoreInventory getCurrencyBalance:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::addCurrencyAmount(string currencyItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString *str = [AnalyticXStringUtil nsstringFromCString:currencyItemId.c_str()];
        return [StoreInventory addAmount:amount toCurrency:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::removeCurrencyAmount(string currencyItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString *str = [AnalyticXStringUtil nsstringFromCString:currencyItemId.c_str()];
        return [StoreInventory removeAmount:amount fromCurrency:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::getGoodBalance(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString *str = [AnalyticXStringUtil nsstringFromCString:goodItemId.c_str()];
        return [StoreInventory getGoodBalance:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::addGoodAmount(string goodItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString *str = [AnalyticXStringUtil nsstringFromCString:goodItemId.c_str()];
        return [StoreInventory addAmount:amount toGood:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::removeGoodAmount(string goodItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString *str = [AnalyticXStringUtil nsstringFromCString:goodItemId.c_str()];
        return [StoreInventory removeAmount:amount fromGood:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}
