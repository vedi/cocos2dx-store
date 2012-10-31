//
//  cocos2dx_StoreInfo.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/28/12.
//
//

#include "cocos2dx_StoreInfo.h"
#import "VirtualCurrencyPack.h"
#import "VirtualGood.h"
#import "StoreInfo.h"
#import "AppStoreItem.h"
#import "VirtualItemNotFoundException.h"

/**
 * This implementation is used to let cocos2dx functions retrieve data from StoreInfo.
 *
 * You can see the documentation of every function in StoreInfo.
 */


string cocos2dx_StoreInfo::getPackProductId(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId length:strlen(itemId) encoding:NSUTF8StringEncoding];
        VirtualCurrencyPack* pack = [[StoreInfo getInstance] currencyPackWithItemId:str];
        return [pack.appstoreItem.productId UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getPackName(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId length:strlen(itemId) encoding:NSUTF8StringEncoding];
        VirtualCurrencyPack* pack = [[StoreInfo getInstance] currencyPackWithItemId:str];
        return [pack.name UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getPackDescription(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId length:strlen(itemId) encoding:NSUTF8StringEncoding];
        VirtualCurrencyPack* pack = [[StoreInfo getInstance] currencyPackWithItemId:str];
        return [pack.description UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

double cocos2dx_StoreInfo::getPackPrice(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId length:strlen(itemId) encoding:NSUTF8StringEncoding];
        VirtualCurrencyPack* pack = [[StoreInfo getInstance] currencyPackWithItemId:str];
        return pack.price;
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getGoodName(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId length:strlen(itemId) encoding:NSUTF8StringEncoding];
        VirtualGood* good = [[StoreInfo getInstance] goodWithItemId:str];
        return [good.name UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

string cocos2dx_StoreInfo::getGoodDescription(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId length:strlen(itemId) encoding:NSUTF8StringEncoding];
        VirtualGood* good = [[StoreInfo getInstance] goodWithItemId:str];
        return [good.description UTF8String];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }

}

int cocos2dx_StoreInfo::getGoodPriceForCurrency(const char* goodItemId, const char* currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str1 = [[NSString alloc] initWithBytes:goodItemId length:strlen(goodItemId) encoding:NSUTF8StringEncoding];
        NSString * str2 = [[NSString alloc] initWithBytes:currencyItemId length:strlen(currencyItemId) encoding:NSUTF8StringEncoding];
        VirtualGood* good = [[StoreInfo getInstance] goodWithItemId:str1];
        return [(NSNumber*)[good.currencyValues objectForKey:str2] intValue];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}
