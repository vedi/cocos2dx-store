
#include "cocos2dx_StoreController.h"
#import "StoreController.h"
#import "VirtualItemNotFoundException.h"
#import "InsufficientFundsException.h"
#import "NotEnoughGoodsException.h"
#import "MuffinRushAssets.h"

void cocos2dx_StoreController::storeOpening() {
    [[StoreController getInstance] storeOpening];
}

void cocos2dx_StoreController::storeClosing() {
    [[StoreController getInstance] storeClosing];
}

void cocos2dx_StoreController::initialize(bool debug) {
    /**
     * We initialize StoreController when the application loads !
     */
    [[StoreController getInstance] initializeWithStoreAssets:[[MuffinRushAssets alloc] init]];

}

void cocos2dx_StoreController::buyCurrencyPack(string productId) throw(cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:productId.c_str() length:strlen(productId.c_str()) encoding:NSUTF8StringEncoding];
        [[StoreController getInstance] buyCurrencyPackWithProcuctId:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}

void cocos2dx_StoreController::buyVirtualGood(string itemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        [[StoreController getInstance] buyVirtualGood:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
    @catch (InsufficientFundsException *exception) {
        throw cocos2dx_InsufficientFundsException();
    }
}

void cocos2dx_StoreController::buyManagedItem(string productId) throw(cocos2dx_VirtualItemNotFoundException&) {
    NSException *exception = [NSException exceptionWithName: NSInternalInconsistencyException
                                                     reason: @"MANAGED items are not supported in ios-store yet."
                                                   userInfo: nil];
    @throw exception;
}

void cocos2dx_StoreController::equipVirtualGood(string itemId) throw (cocos2dx_NotEnoughGoodsException&, cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        [[StoreController getInstance] equipVirtualGood:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
    @catch (NotEnoughGoodsException *exception) {
        throw cocos2dx_NotEnoughGoodsException();
    }
}

void cocos2dx_StoreController::unequipVirtualGood(string itemId) throw(cocos2dx_VirtualItemNotFoundException&) {
    @try {
        NSString * str = [[NSString alloc] initWithBytes:itemId.c_str() length:strlen(itemId.c_str()) encoding:NSUTF8StringEncoding];
        [[StoreController getInstance] unequipVirtualGood:str];
    }
    @catch (VirtualItemNotFoundException *exception) {
        throw cocos2dx_VirtualItemNotFoundException();
    }
}
