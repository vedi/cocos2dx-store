#import "MuffinRushAssets.h"
#import "VirtualCategory.h"
#import "VirtualCurrency.h"
#import "VirtualGood.h"
#import "VirtualCurrencyPack.h"
#import "NonConsumableItem.h"
#import "SingleUseVG.h"
#import "PurchaseWithMarket.h"
#import "PurchaseWithVirtualItem.h"


NSString* const MUFFINS_CURRENCY_ITEM_ID = @"currency_muffin";

NSString* const FRUIT_CAKE_GOOD_ITEM_ID = @"fruit_cake";
NSString* const PAVLOVA_GOOD_ITEM_ID = @"pavlova";
NSString* const CHOCO_CAKE_GOOD_ITEM_ID = @"chocolate_cake";
NSString* const CREAM_CUP_GOOD_ITEM_ID = @"cream_cup";

NSString* const _10_MUFFINS_PACK_ITEM_ID = @"muffins_10";
NSString* const _50_MUFFINS_PACK_ITEM_ID = @"muffins_50";
NSString* const _400_MUFFINS_PACK_ITEM_ID = @"muffins_400";
NSString* const _1000_MUFFINS_PACK_ITEM_ID = @"muffins_1000";

NSString* const _10_MUFFINS_PACK_PRODUCT_ID = @"muffins_10";
NSString* const _50_MUFFINS_PACK_PRODUCT_ID = @"muffins_50";
NSString* const _400_MUFFINS_PACK_PRODUCT_ID = @"muffins_400";
NSString* const _1000_MUFFINS_PACK_PRODUCT_ID = @"com.soomla.SoomlaiOSStoreExampleDevice.second_test";

NSString* const NO_ADDS_NONCONS_PRODUCT_ID = @"no_ads";



/**
 * This class represents a single game's metadata.
 * Use this protocol to create your assets class that will be transferred to StoreInfo
 * upon initialization.
 */
@implementation MuffinRushAssets

VirtualCategory* GENERAL_CATEGORY;

VirtualCurrency* MUFFINS_CURRENCY;

SingleUseVG* FRUIT_CAKE_GOOD;
SingleUseVG* PAVLOVA_GOOD;
SingleUseVG* CHOCO_CAKE_GOOD;
SingleUseVG* CREAM_CUP_GOOD;

VirtualCurrencyPack* _10_MUFFINS_PACK;
VirtualCurrencyPack* _50_MUFFINS_PACK;
VirtualCurrencyPack* _400_MUFFINS_PACK;
VirtualCurrencyPack* _1000_MUFFINS_PACK;

NonConsumableItem* NO_ADDS_NON_CONS;

+ (void)initialize{
    
    /** Virtual Currencies **/
    
    MUFFINS_CURRENCY = [[VirtualCurrency alloc] initWithName:@"Muffins" andDescription:@"" andItemId:MUFFINS_CURRENCY_ITEM_ID];
    
    
    
    /** Virtual Currency Pack **/
    
    _10_MUFFINS_PACK = [[VirtualCurrencyPack alloc] initWithName:@"10 Muffins" andDescription:@"" andItemId:_10_MUFFINS_PACK_ITEM_ID andCurrencyAmount:10 andCurrency:MUFFINS_CURRENCY_ITEM_ID andPurchaseType:[[PurchaseWithMarket alloc] initWithProductId:_10_MUFFINS_PACK_PRODUCT_ID andPrice:0.99]];
    _50_MUFFINS_PACK = [[VirtualCurrencyPack alloc] initWithName:@"50 Muffins" andDescription:@"" andItemId:_50_MUFFINS_PACK_ITEM_ID andCurrencyAmount:50 andCurrency:MUFFINS_CURRENCY_ITEM_ID andPurchaseType:[[PurchaseWithMarket alloc] initWithProductId:_50_MUFFINS_PACK_PRODUCT_ID andPrice:1.99]];
    _400_MUFFINS_PACK = [[VirtualCurrencyPack alloc] initWithName:@"400 Muffins" andDescription:@"" andItemId:_400_MUFFINS_PACK_ITEM_ID andCurrencyAmount:400 andCurrency:MUFFINS_CURRENCY_ITEM_ID andPurchaseType:[[PurchaseWithMarket alloc] initWithProductId:_400_MUFFINS_PACK_PRODUCT_ID andPrice:4.99]];
    _1000_MUFFINS_PACK = [[VirtualCurrencyPack alloc] initWithName:@"1000 Muffins" andDescription:@"" andItemId:_1000_MUFFINS_PACK_ITEM_ID andCurrencyAmount:1000 andCurrency:MUFFINS_CURRENCY_ITEM_ID andPurchaseType:[[PurchaseWithMarket alloc] initWithProductId:_1000_MUFFINS_PACK_PRODUCT_ID andPrice:8.99]];
    
    
    
    /** Virtual Goods **/
    
    FRUIT_CAKE_GOOD = [[SingleUseVG alloc] initWithName:@"Fruit Cake" andDescription:@"Customers buy a double portion on each purchase of this cake" andItemId:FRUIT_CAKE_GOOD_ITEM_ID andPurchaseType:[[PurchaseWithVirtualItem alloc] initWithVirtualItem:MUFFINS_CURRENCY_ITEM_ID andAmount:220]];
    
    PAVLOVA_GOOD = [[SingleUseVG alloc] initWithName:@"Pavlova" andDescription:@"Gives customers a sugar rush and they call their friends" andItemId:PAVLOVA_GOOD_ITEM_ID andPurchaseType:[[PurchaseWithVirtualItem alloc] initWithVirtualItem:MUFFINS_CURRENCY_ITEM_ID andAmount:175]];
    
    CHOCO_CAKE_GOOD = [[SingleUseVG alloc] initWithName:@"Choco-Cake" andDescription:@"A classic cake to maximize customer satisfaction" andItemId:CHOCO_CAKE_GOOD_ITEM_ID andPurchaseType:[[PurchaseWithVirtualItem alloc] initWithVirtualItem:MUFFINS_CURRENCY_ITEM_ID andAmount:250]];
    
    CREAM_CUP_GOOD = [[SingleUseVG alloc] initWithName:@"Cream Cup" andDescription:@"Increase bakery reputation with this original pastry" andItemId:CREAM_CUP_GOOD_ITEM_ID andPurchaseType:[[PurchaseWithVirtualItem alloc] initWithVirtualItem:MUFFINS_CURRENCY_ITEM_ID andAmount:50]];
    
    
    
    /** Virtual Categories **/
    
    GENERAL_CATEGORY = [[VirtualCategory alloc] initWithName:@"General" andGoodsItemIds:@[FRUIT_CAKE_GOOD_ITEM_ID, PAVLOVA_GOOD_ITEM_ID, CHOCO_CAKE_GOOD_ITEM_ID, CREAM_CUP_GOOD_ITEM_ID]];
    
    
    
    /** Non Consumables **/
    
    NO_ADDS_NON_CONS = [[NonConsumableItem alloc] initWithName:@"No Ads" andDescription:@"" andItemId:@"no_ads" andPurchaseType:[[PurchaseWithMarket alloc] initWithProductId:NO_ADDS_NONCONS_PRODUCT_ID andPrice:1.99]];
}

/**
 * A version for your specific game's store assets
 *
 * This value will determine if the saved data in the database will be deleted or not.
 * Bump the version every time you want to delete the old data in the DB.
 * If you don't bump this value, you won't be able to see changes you've made to the objects in this file.
 *
 * NOTE: You can NOT bump this value and just delete the app from your device to see changes. You can't do this after
 * you publish your application on the market.
 *
 * For example: If you previously created a VirtualGood with name "Hat" and you published your application,
 * the name "Hat will be saved in any of your users' databases. If you want to change the name to "Green Hat"
 * than you'll also have to bump the version (from 0 to 1). Now the new "Green Hat" name will replace the old one.
 */
- (int)getVersion {
    return 0;
}

/**
 * A representation of your game's virtual currency.
 */
- (NSArray*)virtualCurrencies{
    return @[MUFFINS_CURRENCY];
}

/**
 * An array of all virtual goods served by your store (all kinds in one array). If you have UpgradeVGs, they must appear in the order of levels.
 */
- (NSArray*)virtualGoods{
    return @[FRUIT_CAKE_GOOD, PAVLOVA_GOOD, CHOCO_CAKE_GOOD, CREAM_CUP_GOOD];
}

/**
 * An array of all virtual currency packs served by your store.
 */
- (NSArray*)virtualCurrencyPacks{
    return @[_10_MUFFINS_PACK, _50_MUFFINS_PACK, _400_MUFFINS_PACK, _1000_MUFFINS_PACK];
}

/**
 * An array of all virtual categories served by your store.
 */
- (NSArray*)virtualCategories{
    return @[GENERAL_CATEGORY];
}

/**
 * You can define non consumable items that you'd like to use for your needs.
 * CONSUMABLE items are usually just currency packs.
 * NON-CONSUMABLE items are usually used to let users purchase a "no-ads" token.
 */
- (NSArray*)nonConsumableItems{
    return @[NO_ADDS_NON_CONS];
}

@end