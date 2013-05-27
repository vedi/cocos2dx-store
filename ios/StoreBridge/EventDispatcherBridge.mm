//
//  EventDispatcherBridge.m
//  Trying
//
//  Created by Refael Dakar on 12/03/13.
//
//

#include <iostream>
#include <string>
#import "EventDispatcherBridge.h"
#import "EventHandling.h"
#import "CCEventHandler.h"
#import "VirtualCurrencyPack.h"
#import "AppStoreItem.h"
#import "VirtualGood.h"
#import "VirtualCurrency.h"
#import "UpgradeVG.h"
#import "EquippableVG.h"
#import "PurchasableVirtualItem.h"
#import "IOSNDKHelper.h"
#import "SoomlaEasyNDKGlue.h"

@implementation EventDispatcherBridge


+ (void)initialize {
    static EventDispatcherBridge * instance = nil;
    
    if (!instance) {
        instance = [[EventDispatcherBridge alloc] init];
    }
}

- (id) init {
    if (self = [super init]) {
        [EventHandling observeAllEventsWithObserver:self withSelector:@selector(eventFired:)];
    }
    
    return self;
}

- (void)eventFired:(NSNotification*)notification{
    [SoomlaEasyNDKGlue dispatchNDKCallback:notification];
}


@end
