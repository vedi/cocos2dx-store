//
//  cocos2dx_StoreInventory.mm
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/27/12.
//
//

#include "cocos2dx_StoreInventory.h"
#import "StoreInventory.h"
#import "VirtualItemNotFoundException.h"


/**
 * This implementation is used to let cocos2dx functions perform actions on StoreInventory.
 *
 * You can see the documentation of every function in StoreInventory.
 */


int cocos2dx_StoreInventory::getCurrencyBalance(string currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString * str = [[NSString alloc] initWithBytes:currencyItemId.c_str() length:strlen(currencyItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory getCurrencyBalance:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::addCurrencyAmount(string currencyItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString * str = [[NSString alloc] initWithBytes:currencyItemId.c_str() length:strlen(currencyItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory addAmount:amount toCurrency:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::removeCurrencyAmount(string currencyItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString * str = [[NSString alloc] initWithBytes:currencyItemId.c_str() length:strlen(currencyItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory removeAmount:amount fromCurrency:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::getGoodBalance(string goodItemId) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory getGoodBalance:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::addGoodAmount(string goodItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory addAmount:amount toGood:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

int cocos2dx_StoreInventory::removeGoodAmount(string goodItemId, int amount) throw (cocos2dx_VirtualItemNotFoundException&){
    @try {
        NSString * str = [[NSString alloc] initWithBytes:goodItemId.c_str() length:strlen(goodItemId.c_str()) encoding:NSUTF8StringEncoding];
        return [StoreInventory removeAmount:amount fromGood:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}
