
#import "RootViewController.h"
#import "IOSNDKHelper.h"
#import "StoreController.h"
#import "cocos2dx_StoreController.h"
#import "cocos2dx_StoreInventory.h"
#import "cocos2dx_StoreAssets.h"
#import "VirtualItem.h"
#import "StoreInfo.h"
#import "VirtualItemNotFoundException.h"
#import "cocos2dx_StoreInfo.h"


@implementation RootViewController {
    cocos2dx_StoreAssets *storeAssets;
}

// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Tell NDKHelper that RootViewController will respond to messages
        // Coming from C++
        [IOSNDKHelper setNDKReceiver:self];
    }
    return self;
}

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/

- (BOOL)shouldAutorotate
{
    //returns true if want to allow orientation change
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations
{
    // return UIInterfaceOrientationMaskLandscape;
	
    // switch to this line if you want to set portrait view
    return UIInterfaceOrientationMaskPortrait;
}

// Override to allow orientations other than the default landscape orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // return UIInterfaceOrientationIsLandscape( interfaceOrientation );
    
    // switch to this line if you want to set portrait view
    return UIInterfaceOrientationIsPortrait( interfaceOrientation );
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

#pragma mark -
#pragma mark Easy NDK methods

- (NSObject *)soomla_easyNDKTest:(NSObject *)params {
    NSLog(@"soomla_easyNDKTest call");
    NSDictionary *parameters = (NSDictionary*) params;
    NSLog(@"Passed params are : %@", parameters);

    NSLog(@"Send them back to native code");
    [IOSNDKHelper sendMessage:@"soomla_easyNDKCallBackTest" withParameters:parameters];

    return nil;
}

- (NSObject *)soomla_easyNDK:(NSObject *)params {
    NSLog(@"soomla_easyNDK call");
    NSDictionary *parameters = (NSDictionary*) params;
    NSLog(@"Passed params are : %@", parameters);

    NSString *methodName = [parameters objectForKey:@"method"];

    NSDictionary *retParameters = [[NSDictionary alloc] autorelease];

    if ([methodName isEqualToString:@"StoreAssets::init"]) {
        NSNumber *version = (NSNumber *) [parameters objectForKey:@"version"];
        NSDictionary *storeAssetsDict = (NSDictionary *) [parameters objectForKey:@"storeAssets"];
        storeAssets = [[cocos2dx_StoreAssets alloc] initWithStoreAssetsDict:storeAssetsDict andVersion:version.intValue];
    }
    else if ([methodName isEqualToString:@"StoreController::init"]) {
        NSString *customSecret = (NSString *) [parameters objectForKey:@"customSecret"];

        [[StoreController getInstance] initializeWithStoreAssets:storeAssets
                                                 andCustomSecret:customSecret];
        // TODO: Implement event dispatcher: storeEventDispatcher = [[UnityStoreEventDispatcher alloc] init];
    }
    else if ([methodName isEqualToString:@"CCStoreController::buyMarketItem"]) {
        NSString *productId = (NSString *) [parameters objectForKey:@"productId"];
        cocos2dx_StoreController::buyMarketItem([productId UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreController::storeOpening"]) {
        cocos2dx_StoreController::storeOpening();
    }
    else if ([methodName isEqualToString:@"CCStoreController::storeClosing"]) {
        cocos2dx_StoreController::storeClosing();
    }
    else if ([methodName isEqualToString:@"CCStoreController::restoreTransactions"]) {
        cocos2dx_StoreController::restoreTransactions();
    }
    else if ([methodName isEqualToString:@"CCStoreController::transactionsAlreadyRestored"]) {
        bool res = cocos2dx_StoreController::transactionsAlreadyRestored();
        [retParameters setValue:[NSNumber numberWithBool:res] forKey:@"return"];
    }
    else if ([methodName isEqualToString:@"CCStoreController::setSoomSec"]) {
        NSString *soomSec = (NSString *) [parameters objectForKey:@"soomSec"];
        cocos2dx_StoreController::setSoomSec([soomSec UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::buyItem"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        cocos2dx_StoreInventory::buy([itemId UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::getItemBalance"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        int res = cocos2dx_StoreInventory::getItemBalance([itemId UTF8String]);
        [retParameters setValue:[NSNumber numberWithInt:res] forKey:@"return"];
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::giveItem"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        NSNumber *amount = (NSNumber *) [parameters objectForKey:@"amount"];
        cocos2dx_StoreInventory::giveItem([itemId UTF8String], [amount intValue]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::takeItem"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        NSNumber *amount = (NSNumber *) [parameters objectForKey:@"amount"];
        cocos2dx_StoreInventory::takeItem([itemId UTF8String], [amount intValue]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::equipVirtualGood"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        cocos2dx_StoreInventory::equipVirtualGood([itemId UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::unEquipVirtualGood"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        cocos2dx_StoreInventory::unEquipVirtualGood([itemId UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::isVirtualGoodEquipped"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        bool res = cocos2dx_StoreInventory::isVirtualGoodEquipped([itemId UTF8String]);
        [retParameters setValue:[NSNumber numberWithBool:res] forKey:@"return"];
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::getGoodUpgradeLevel"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        int res = cocos2dx_StoreInventory::getGoodUpgradeLevel([goodItemId UTF8String]);
        [retParameters setValue:[NSNumber numberWithInt:res] forKey:@"return"];
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::getGoodCurrentUpgrade"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        string res = cocos2dx_StoreInventory::getGoodCurrentUpgrade([goodItemId UTF8String]);
        [retParameters setValue:[NSString stringWithCString:res.c_str() encoding:NSUTF8StringEncoding] forKey:@"return"];
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::upgradeGood"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        cocos2dx_StoreInventory::upgradeVirtualGood([goodItemId UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::removeGoodUpgrades"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        cocos2dx_StoreInventory::removeUpgrades([goodItemId UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::nonConsumableItemExists"]) {
        NSString *nonConsItemId = (NSString *) [parameters objectForKey:@"nonConsItemId"];
        bool res = cocos2dx_StoreInventory::nonConsumableItemExists([nonConsItemId UTF8String]);
        [retParameters setValue:[NSNumber numberWithBool:res] forKey:@"return"];
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::addNonConsumableItem"]) {
        NSString *nonConsItemId = (NSString *) [parameters objectForKey:@"nonConsItemId"];
        cocos2dx_StoreInventory::addNonConsumableItem([nonConsItemId UTF8String]);
    }
    else if ([methodName isEqualToString:@"CCStoreInventory::removeNonConsumableItem"]) {
        NSString *nonConsItemId = (NSString *) [parameters objectForKey:@"nonConsItemId"];
        cocos2dx_StoreInventory::removeNonConsumableItem([nonConsItemId UTF8String]);
    }
    else if ([methodName isEqualToString:@"StoreInfo::getItemByItemId"]) {
        NSString *itemId = (NSString *) [parameters objectForKey:@"itemId"];
        NSDictionary *retParameters = cocos2dx_StoreInfo::getItemByItemId(itemId);
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getPurchasableItemWithProductId"]) {
        NSString *productId = (NSString *) [parameters objectForKey:@"productId"];
        NSDictionary *retParameters = cocos2dx_StoreInfo::getPurchasableItemWithProductId(productId);
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getCategoryForVirtualGood"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        NSDictionary *retParameters = cocos2dx_StoreInfo::getCategoryForVirtualGood(goodItemId);
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getFirstUpgradeForVirtualGood"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        NSDictionary *retParameters = cocos2dx_StoreInfo::getFirstUpgradeForVirtualGood(goodItemId);
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getLastUpgradeForVirtualGood"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        NSDictionary *retParameters = cocos2dx_StoreInfo::getLastUpgradeForVirtualGood(goodItemId);
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getUpgradesForVirtualGood"]) {
        NSString *goodItemId = (NSString *) [parameters objectForKey:@"goodItemId"];
        NSArray *retParameters = cocos2dx_StoreInfo::getUpgradesForVirtualGood(goodItemId);
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getVirtualCurrencies"]) {
        NSArray *retParameters = cocos2dx_StoreInfo::getVirtualCurrencies();
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getVirtualGoods"]) {
        NSArray *retParameters = cocos2dx_StoreInfo::getVirtualGoods();
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getVirtualCurrencyPacks"]) {
        NSArray *retParameters = cocos2dx_StoreInfo::getVirtualCurrencyPacks();
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getNonConsumableItems"]) {
        NSArray *retParameters = cocos2dx_StoreInfo::getNonConsumableItems();
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else if ([methodName isEqualToString:@"StoreInfo::getVirtualCategories"]) {
        NSArray *retParameters = cocos2dx_StoreInfo::getVirtualCategories();
        [retParameters setValue: retParameters forKey: @"return"];
    }
    else {

    }
    return retParameters;
}



@end
