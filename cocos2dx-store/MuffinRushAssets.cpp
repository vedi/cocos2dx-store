//
// Created by Fedor Shubin on 5/24/13.
//


#include "MuffinRushAssets.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCPurchaseWithMarket.h"
#include "CCVirtualGood.h"
#include "CCSingleUseVG.h"
#include "CCPurchaseWithVirtualItem.h"
#include "CCVirtualCategory.h"
#include "CCNonConsumableItem.h"

USING_NS_CC;
using namespace soomla;

#define MUFFIN_CURRENCY_ITEM_ID "currency_muffin"
#define TENMUFF_PACK_PRODUCT_ID "android.test.refunded"
#define FIFTYMUFF_PACK_PRODUCT_ID "android.test.canceled"
#define FOURHUNDMUFF_PACK_PRODUCT_ID "android.test.purchased"
#define THOUSANDMUFF_PACK_PRODUCT_ID "android.test.item_unavailable"
#define NO_ADDS_NONCONS_PRODUCT_ID "no_ads"

#define MUFFINCAKE_ITEM_ID "fruit_cake"
#define PAVLOVA_ITEM_ID "pavlova"
#define CHOCLATECAKE_ITEM_ID "chocolate_cake"
#define CREAMCUP_ITEM_ID "cream_cup"


MuffinRushAssets *MuffinRushAssets::create() {
    MuffinRushAssets *ret = new MuffinRushAssets();
    ret->autorelease();
    ret->init();

    return ret;
}

bool MuffinRushAssets::init() {
    /** Virtual Currencies **/
    CCVirtualCurrency *muffinCurrency = CCVirtualCurrency::create(
            CCString::create("Muffins"),
            CCString::create(""),
            CCString::create(MUFFIN_CURRENCY_ITEM_ID)
    );


    /** Virtual Currency Packs **/

    CCVirtualCurrencyPack *tenmuffPack = CCVirtualCurrencyPack::create(
            CCString::create("10 Muffins"),                                   // name
            CCString::create("Test refund of an item"),                       // description
            CCString::create("muffins_10"),                                   // item id
            CCInteger::create(10),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(TENMUFF_PACK_PRODUCT_ID), CCDouble::create(0.99))
    );

    CCVirtualCurrencyPack *fiftymuffPack = CCVirtualCurrencyPack::create(
            CCString::create("50 Muffins"),                                   // name
            CCString::create("Test cancellation of an item"),                 // description
            CCString::create("muffins_50"),                                   // item id
            CCInteger::create(50),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(FIFTYMUFF_PACK_PRODUCT_ID), CCDouble::create(1.99))
    );

    CCVirtualCurrencyPack *fourhundmuffPack = CCVirtualCurrencyPack::create(
            CCString::create("50 Muffins"),                                   // name
            CCString::create("Test purchase of an item"),                 // description
            CCString::create("muffins_400"),                                   // item id
            CCInteger::create(400),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(FOURHUNDMUFF_PACK_PRODUCT_ID), CCDouble::create(4.99))
    );

    CCVirtualCurrencyPack *thousandmuffPack = CCVirtualCurrencyPack::create(
            CCString::create("1000 Muffins"),                                   // name
            CCString::create("Test item unavailable"),                 // description
            CCString::create("muffins_1000"),                                   // item id
            CCInteger::create(1000),												// number of currencies in the pack
            CCString::create(MUFFIN_CURRENCY_ITEM_ID),                        // the currency associated with this pack
            CCPurchaseWithMarket::create(CCString::create(THOUSANDMUFF_PACK_PRODUCT_ID), CCDouble::create(8.99))
    );

    /** Virtual Goods **/

    CCVirtualGood *muffincakeGood = CCSingleUseVG::create(
            CCString::create("Fruit Cake"),                                       // name
            CCString::create("Customers buy a double portion on each purchase of this cake"), // description
            CCString::create("fruit_cake"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(225)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *pavlovaGood = CCSingleUseVG::create(
            CCString::create("Pavlova"),                                       // name
            CCString::create("Gives customers a sugar rush and they call their friends"), // description
            CCString::create("pavlova"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(175)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *choclatecakeGood = CCSingleUseVG::create(
            CCString::create("Chocolate Cake"),                                       // name
            CCString::create("A classic cake to maximize customer satisfaction"), // description
            CCString::create("chocolate_cake"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(250)
            ) // the way this virtual good is purchased
    );

    CCVirtualGood *creamcupGood = CCSingleUseVG::create(
            CCString::create("Cream Cup"),                                       // name
            CCString::create("Increase bakery reputation with this original pastry"), // description
            CCString::create("cream_cup"),                                       // item id
            CCPurchaseWithVirtualItem::create(
                    CCString::create(MUFFIN_CURRENCY_ITEM_ID), CCInteger::create(50)
            ) // the way this virtual good is purchased
    );

    /** Virtual Categories **/
    // The muffin rush theme doesn't support categories, so we just put everything under a general category.
    CCVirtualCategory *generalCategory = CCVirtualCategory::create(
            CCString::create("General"),
            CCArray::create(
                    CCString::create(MUFFINCAKE_ITEM_ID),
                    CCString::create(PAVLOVA_ITEM_ID),
                    CCString::create(CHOCLATECAKE_ITEM_ID),
                    CCString::create(CREAMCUP_ITEM_ID),
                    NULL
            ));


    /** Google MANAGED Items **/

    CCNonConsumableItem *noAdsNoncons = CCNonConsumableItem::create(
            CCString::create("No Ads"),
            CCString::create("Test purchase of MANAGED item."),
            CCString::create("no_ads"),
            CCPurchaseWithMarket::createWithMarketItem(CCMarketItem::create(
                    CCString::create(NO_ADDS_NONCONS_PRODUCT_ID),
                    CCInteger::create(CCMarketItem::NONCONSUMABLE), CCDouble::create(1.99))
            )
    );

    mCurrencies = CCArray::create(muffinCurrency, NULL);
    mCurrencies->retain();

    mGoods = CCArray::create(muffincakeGood, pavlovaGood, choclatecakeGood, creamcupGood, NULL);
    mGoods->retain();

    mCurrencyPacks = CCArray::create(tenmuffPack, fiftymuffPack, fourhundmuffPack, thousandmuffPack, NULL);
    mCurrencyPacks->retain();

    mCategories = CCArray::create(generalCategory, NULL);
    mCategories->retain();

    mNonConsumableItems = CCArray::create(noAdsNoncons, NULL);
    mNonConsumableItems->retain();

    return true;
}

MuffinRushAssets::~MuffinRushAssets() {
    CC_SAFE_RELEASE(mCurrencies);
    CC_SAFE_RELEASE(mGoods);
    CC_SAFE_RELEASE(mCurrencyPacks);
    CC_SAFE_RELEASE(mCategories);
    CC_SAFE_RELEASE(mNonConsumableItems);
}

int MuffinRushAssets::getVersion() {
    return 0;
}

cocos2d::CCArray *MuffinRushAssets::getCurrencies() {
    return mCurrencies;
}

cocos2d::CCArray *MuffinRushAssets::getGoods() {
    return mGoods;
}

cocos2d::CCArray *MuffinRushAssets::getCurrencyPacks() {
    return mCurrencyPacks;
}

cocos2d::CCArray *MuffinRushAssets::getCategories() {
    return mCategories;
}

cocos2d::CCArray *MuffinRushAssets::getNonConsumableItems() {
    return mNonConsumableItems;
}

