//
//  cocos2dx_EventDispatcher.m
//  Trying
//
//  Created by Refael Dakar on 12/03/13.
//
//

#include <iostream>
#include <string>
#import "cocos2dx_EventDispatcher.h"
#import "EventHandling.h"
#import "cocos2dx_EventHandlers.h"
#import "VirtualCurrencyPack.h"
#import "AppStoreItem.h"
#import "VirtualGood.h"
#import "VirtualCurrency.h"

@implementation cocos2dx_EventDispatcher


+ (void)initialize {
    static cocos2dx_EventDispatcher* instance = nil;
    
    if (!instance) {
        instance = [[cocos2dx_EventDispatcher alloc] init];
    }
}

- (id) init {
    if (self = [super init]) {
        [EventHandling observeAllEventsWithObserver:self withSelector:@selector(eventFired:)];
    }
    
    return self;
}

- (void)eventFired:(NSNotification*)notification{
    if ([notification.name isEqualToString:EVENT_APPSTORE_PURCHASED]) {
        AppStoreItem* apItem = (AppStoreItem*)[notification.userInfo objectForKey:@"AppStoreItem"];
        string productId([apItem.productId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->marketPurchase(productId);
    }
    else if ([notification.name isEqualToString:EVENT_VIRTUAL_GOOD_PURCHASED]) {
        VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:@"VirtualGood"];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->virtualGoodPurchased(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_VIRTUAL_GOOD_EQUIPPED]) {
        VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:@"VirtualGood"];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->virtualGoodEquipped(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_VIRTUAL_GOOD_UNEQUIPPED]) {
        VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:@"VirtualGood"];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->virtualGoodUnequipped(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_BILLING_SUPPORTED]) {
        cocos2dx_EventHandlers::getInstance()->billingSupported();
    }
    else if ([notification.name isEqualToString:EVENT_BILLING_NOT_SUPPORTED]) {
        cocos2dx_EventHandlers::getInstance()->billingNotSupported();
    }
    else if ([notification.name isEqualToString:EVENT_MARKET_PURCHASE_STARTED]) {
        AppStoreItem* asi = (AppStoreItem*)[notification.userInfo objectForKey:@"AppStoreItem"];
        string productId([asi.productId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->marketPurchaseProcessStarted(productId);
    }
    else if ([notification.name isEqualToString:EVENT_MARKET_PURCHASE_CANCELLED]) {
        AppStoreItem* asi = (AppStoreItem*)[notification.userInfo objectForKey:@"AppStoreItem"];
        string productId([asi.productId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->marketPurchaseCancelled(productId);
    }
    else if ([notification.name isEqualToString:EVENT_GOODS_PURCHASE_STARTED]) {
        cocos2dx_EventHandlers::getInstance()->goodsPurchaseProcessStarted();
    }
    else if ([notification.name isEqualToString:EVENT_CLOSING_STORE]) {
        cocos2dx_EventHandlers::getInstance()->closingStore();
    }
    else if ([notification.name isEqualToString:EVENT_OPENING_STORE]) {
        cocos2dx_EventHandlers::getInstance()->openingStore();
    }
    else if ([notification.name isEqualToString:EVENT_UNEXPECTED_ERROR_IN_STORE]) {
        cocos2dx_EventHandlers::getInstance()->unexpectedErrorInStore();
    }
    else if ([notification.name isEqualToString:EVENT_CHANGED_CURRENCY_BALANCE]) {
		int balance = [(NSNumber*)[notification.userInfo objectForKey:@"balance"] intValue];
		VirtualCurrency* currency = (VirtualCurrency*)[notification.userInfo objectForKey:@"VirtualCurrency"];
		string itemId([currency.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->currencyBalanceChanged(itemId, balance);
    }
    else if ([notification.name isEqualToString:EVENT_CHANGED_GOOD_BALANCE]) {
		int balance = [(NSNumber*)[notification.userInfo objectForKey:@"balance"] intValue];
		VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:@"VirtualGood"];
		string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->goodBalanceChanged(itemId, balance);
    }
}


@end
