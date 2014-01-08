*This project is a part of [The SOOMLA Project](http://project.soom.la) which is a series of open source initiatives with a joint goal to help mobile game developers get better stores and more in-app purchases.*

Haven't you always wanted an in-app purchase one liner that looks like this?!

```cpp
soomla::CCStoreInventory::sharedStoreInventory()->buyItem("[itemId]");
```

# cocos2dx-store

**December ??, 2013**: Refunds have been added back in in **cocos2dx-store** for Android. They are now checked whenever `CCStoreController` is initialized.

**December 1, 2013**: Android in-app billing has been updated to use Google's in-app billing version 3.

**October 28, 2013**: iOS server side verification is added. This feature is not activated by default. [learn more](https://github.com/soomla/cocos2dx-store#ios-server-side-verification)

**October 27, 2013**: cocos2dx-store has been updated since its last version. Everything has been rewritten from scratch and is much more Cocos2d-x friendly. cocos2dx-store allows your Cocos2d-x game to use SOOMLA's in app purchasing services and storage. cocos2dx-store has also been updated to use the third version of our economy model: modelV3.

> cocos2dx-store currently supports all Cocos2d-x 2.x versions. Support for version 3.x (alpha) is experimental.

The current virtual economny model is called **modelV3**. Want to learn more about it? Try these links:
* [Economy Model Objects](https://github.com/soomla/cocos2dx-store/wiki/Economy-Model-Objects)
* [Handling Store Operations](https://github.com/soomla/cocos2dx-store/wiki/Handling-Store-Operations)

The cocos2dx-store is the Cocos2d-x flavour of The SOOMLA Project. This project uses [android-store](https://github.com/soomla/android-store) and [ios-store](https://github.com/soomla/ios-store) in order to provide game developers with in-app billing for their **cocos2d-x** projects.

>If you also want to create a **Storefront** you can do that using SOOMLA's [In-App Purchase Store Designer](http://dashboard.soom.la).

## Example Project

There's an example project that shows how to use cocos2dx-store at http://github.com/soomla/cocos2dx-store-example .

The example project is still under developement but it already has some important aspects of the framework you can learn and implement in your application.

## Getting Started

1. As with all Cocos2d-x projects, you need to clone the Cocos2d-x framework from [here](https://github.com/cocos2d/cocos2d-x) or download it from the [Cocos2d-x website](http://www.cocos2d-x.org/download).  

    > Make sure the version you clone is supported by cocos2dx-store (the tag is the version).

1. Go into your cocos2d-x project and recursively clone cocos2dx-store into the `extensions` directory located at the root of your Cocos2d-x framework.
    ```
    $ git clone --recursive git@github.com:soomla/cocos2dx-store.git extensions/cocos2dx-store
    ```

1. We use a [fork](https://github.com/vedi/jansson) of the jansson library for json parsing, clone our fork into the `external` directory at the root of your framework.
    ```
    $ git clone git@github.com:vedi/jansson.git
    ```

1. Make sure to include the `Soomla.h` header whenever you use any of the *cocos2dx-store* functions:
    ```cpp
    #include "Soomla.h"
    ```

1. Create your own implementation of `CCIStoreAssets` that will represent the assets in your specific game ([Refer to cocos2dx-store-example for an example.](https://github.com/soomla/cocos2dx-store-example/blob/master/Classes/MuffinRushAssets.cpp)).

1. Initialize `CCStoreController` with your assets class, and a `CCDictionary` containing various parameters for it:

    ```cpp
    CCDictionary *storeParams = CCDictionary::create();
    storeParams->
        setObject(CCString::create("ExampleSoomSecret"), "soomSec");
    storeParams->
        setObject(CCString::create("ExamplePublicKey"), "androidPublicKey");
    storeParams->
        setObject(CCString::create("ExampleCustomSecret"), "customSecret");
        
    soomla::CCStoreController::createShared(YourStoreAssetsImplementation::create(), storeParams);
    ```
    - *Custom Secret* - is an encryption secret you provide that will be used to secure your data.
    - *Public Key* - is the public key given to you from Google. (iOS doesn't have a public key).
    - *Soom Sec* - is a special secret SOOMLA uses to increase your data protection.

    **Choose both secrets wisely. You can't change them after you launch your game!**

    > Initialize `StoreController` ONLY ONCE when your application loads.

1. You'll need an event handler in order to be notified about in-app purchasing related events. Refer to the [Event Handling](https://github.com/soomla/cocos2dx-store#event-handling) section for more information.

And that's it! You now have storage and in-app purchasing capabilities.


#### Instructions for iOS

In your XCode project, you'll need to add some folders in order to be able to build with cocos2dx-store:

1. **ios** folder this repo's root.
2. **Soomla** folder this repo's root.
3. **SoomlaiOSStore** folder from submodules/ios-store

* Make sure you have these 3 Frameworks linked to your XCode project: Security, libsqlite3.0.dylib, StoreKit.

That's it! Now all you have to do is build your XCode project and run your game with cocos2dx-store.

#### Instructions for Android

If you're building your application for the Android platform, here are some instructions on how to integrate cocos2dx-store into your Android project:

1. Import the cocos2dx-store library into your project's Android.mk by adding the following lines in their appropriate places.
    ```
    LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_store_static        # add this line along with your other LOCAL_WHOLE_STATIC_LIBRARIES
    
    $(call import-module, extensions/cocos2dx-store/android/jni) # add this line at the end of the file, along with the other import-module calls
    ```

1. Add the following to your classpath:
    - **extensions/cocos2dx-store/android/src**
    - **extensions/cocos2dx-store/submodules/android-store/SoomlaAndroidStore/src**  (the android-store submodule should be there because your cloned cocos2dx-store with the `--recursive` flag).
    - **extensions/cocos2dx-store/submodules/android-store/SoomlaAndroidStore/libs/square-otto-1.3.2.jar**

1. Update your manifest to include these permissions, SoomlaApp and IabActivity:

    ```xml
    <uses-permission android:name="android.permission.INTERNET"/>
    <uses-permission android:name="com.android.vending.BILLING"/>

    <application ...
    	       android:name="com.soomla.store.SoomlaApp">
        <activity android:name="com.soomla.store.StoreController$IabActivity"
                  android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen"/>
    </application>
    ```

1. In your main Cocos2dxActivity (The one your Cocos2d-x application runs in), call the following in the onCreateView method:
    ```java
    Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    StoreControllerBridge.setGLView(glSurfaceView);
    
    SoomlaApp.setExternalContext(getApplicationContext());
    ```

> These settings are required inorder to initialize the event handling bridge, and allow `StoreController` to initiate market purchases.

That's it! Now all you have to do is run the **build_native.sh** script and you can begin using cocos2dx-store in your game.

##### (optional) Starting IAB Service in background

On Android, If you have your own storefront implemented inside your game, it's recommended that you open the IAB Service in the background when the store opens and close it when the store is closed.

```cpp
// Start Iab Service
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)¬
	CCStoreController::sharedStoreController()->startIabServiceInBg();
#endif

// Stop Iab Service
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)¬
	CCStoreController::sharedStoreController()->stopIabServiceInBg();
#endif
```

Don't forget to close the Iab Service when your store is closed. You don't have to do this at all, this is just an optimization.


## What's next? In App Purchasing.

When we implemented modelV3, we were thinking about ways that people buy things inside apps. We figured out many ways you can let your users purchase items in your game and we designed the new modelV3 to support 2 of them: `CCPurchaseWithMarket` and `CCPurchaseWithVirtualItem`.

- **CCPurchaseWithMarket** is a `CCPurchaseType` that allows users to purchase a `CCVirtualItem` with Google Play or the App Store.
- **CCPurchaseWithVirtualItem** is a `CCPurchaseType` that lets your users purchase a `CCVirtualItem` with another `CCVirtualItem`. For example: Buying a sword with 100 gems.

In order to define the way your various virtual items are purchased, you'll need to create your implementation of `CCIStoreAssets` (the same one from step 5 in the [Getting Started](https://github.com/soomla/cocos2dx-store#getting-started) section above).

Here is an example:

Lets say you have a `CCVirtualCurrencyPack` you want to call `TEN_COINS_PACK` and a `CCVirtualCurrency` you want to call `COIN_CURRENCY` (`TEN_COINS_PACK` will hold 10 pieces of the currency `COIN_CURRENCY`):

```cpp
#define COIN_CURRENCY_ITEM_ID "coin_currency"
#define TEN_COIN_PACK_ITEM_ID       "ten_coin_pack"
#define TEN_COIN_PACK_PRODUCT_ID    "10_coins_pack"  // this is the product id from the developer console
	
CCVirtualCurrency *COIN_CURRENCY = CCVirtualCurrency::create(
	CCString::create("COIN_CURRECY"),
	CCString::create(""),
	CCString::create(COIN_CURRENCY_ITEM_ID)
);
		
CCVirtualCurrencyPack *TEN_COIN_PACK = CCVirtualCurrencyPack::create(
	CCString::create("10 Coins"),
	CCString::create("A pack of 10 coins"),
	CCString::create(TEN_COIN_PACK_ITEM_ID),
	CCInteger::create(10),
	CCString::create(COIN_CURRENCY_ITEM_ID),
	CCPurchaseWithMarket::create(CCString::create(TEN_COIN_PACK_PRODUCT_ID), CCDouble::create(0.99))
);
```

Now you can use `CCStoreInventory` to buy your new currency pack:

    soomla::CCStoreInventory::sharedStoreInventory()->buyItem(TEN_COIN_PACK_ITEM_ID);

And that's it! cocos2dx-store knows how to contact Google Play or the App Store for you and will redirect your users to the purchasing system to complete the transaction. Don't forget to subscribe to store events in order to get notified of successful or failed purchases (see [Event Handling](https://github.com/soomla/cocos2dx-store#event-handling)).

In order to test purchases on Android, add an extra field to storeParams before initializing _CCStoreController_:

```cpp
storeParams->setObject(CCBool::create(true), "androidTestMode");
CCStoreController::createShared(assets, storeParams);
```


## Storage & Meta-Data

`CCStoreInventory` and `CCStoreInfo` are important storage and metadata classes you should use when you want to perform all store operations:
* `CCStoreInventory` is a convenience class to let you perform operations on `CCVirtualCurrencies` and `CCVirtualGood`s. Use it to fetch/change the balances of `CCVirtualItem`s in your game (using their ItemIds!)  
* `CCStoreInfo` is where all meta data information about your specific game can be retrieved. It is initialized with your implementation of `CCIStoreAssets` and you can use it to retrieve information about your specific game.

The on-device storage is encrypted and kept in a SQLite database. SOOMLA has a [cloud-based](http://dashboard.soom.la) storage service (The SOOMLA Highway) that allows this SQLite to be synced to a cloud-based repository that you define.

**Example Usages**

* Get all the `CCVirtualCurrencies`:

    ```cpp
    CCArray *vcArray = soomla::CCStoreInfo::sharedStoreInfo()->getVirtualCurrencies();
    ```

* Give the user 10 pieces of a virtual currency with itemId "currency_coin":

    ```cpp
    soomla::CCStoreInventory::sharedStoreInventory()->giveItem("currency_coin", 10);
    ```

* Take 10 virtual goods with itemId "green_hat":

    ```cpp
    soomla::CCStoreInventory::sharedStoreInventory()->takeItem("green_hat", 10);
    ```

* Get the current balance of green hats (virtual goods with itemId "green_hat"):

    ```cpp
    int greenHatsBalance = soomla::CCStoreInventory::sharedStoreInventory()->getItemBalance("green_hat");
    ```


## Event Handling

SOOMLA lets you subscribe to store events, get notified and implement your own application specific behaviour to them.

> Your behaviour is an addition to the default behaviour implemented by SOOMLA. You don't replace SOOMLA's behaviour.

The `CCSoomla` class is where all events go through. To handle various events, create your own event handler, a class that implements `CCEventHandler`, and add it to the `CCSoomla` class:

    soomla::CCSoomla::sharedSoomla()->addEventHandler(yourEventHandler);

## Error Handling

Since Cocos2d-x doesn't support exceptions, we use a different method to catch and work with exceptions on the native side. All functions that raise an exception on the native side have an additional *CCSoomlaError*** parameter to them. In order to know if an exception was raised, send a reference to *CCSoomlaError** to the function, and inspect it after running.

For example, if I want to purchase an item with the ItemID `huge_sword`, and check if all went well after the purchase, I would call `CCStoreController::buyItem()`, like this:

```c++
soomla::CCSoomlaError *err;
soomla::CCStoreInventory::sharedStoreInventory()->buyItem("huge_sword", &err);
if (err != NULL) {
    int code = err->getCode();
    switch code {
        case SOOMLA_EXCEPTION_ITEM_NOT_FOUND:
            // itemNotFoundException was raised
            break;
        case SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS:
            // insufficienFundsException was raised
            break;
        case SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS:
            // notEnoughGoodsException was raised
            break;
    }
}
```

You can choose to handle each exception on its own, handle all three at once, or not handle the exceptions at all. The `CCSoomlaError` parameter is entirely optional, you can pass NULL instead if you do not wish to handle errors, but remember, error handling is *your* responsibility. cocos2dx-store doesn't do any external error handling (i.e. error handling that uses `CCSoomlaError`) for you.

## iOS Server Side Verification

As you probably know, fraud on IAP is pretty common. Hackers can crack their smartphones to think that a purchase is made when payment wasn't actually transferred to you. We want to help you with it so we created our verification server and we let you instantly use it through the framework.
All you need to do is let cocos2dx-store know you want to verify purchases. You can do this by passing an extra parameter to `CCStoreController`:

```cpp
storeParams->setObject(CCBool::create(true), "SSV);
CCStoreController::createShared(assets, storeParams);
```

## Debugging

You can enable debug logging in cocos2dx-store by setting `SOOMLA_DEBUG` in `CCStoreUtils.h` to `true`. Debug logging can also be enabled at build time by adding `-DSOOMLA_DEBUG=1` to `APP_CPPFLAGS` in your `Application.mk` on Android, or by setting `SOOMLA_DEBUG=1` in your Build Settings' `Preprocessor Macros` on iOS.

If you want to see debug messages from _android-store_, set the `logDebug` variable in `com.soomla.store.StoreConfig` to `true`.

To see debug messages on iOS, make sure you have also `DEBUG=1` in your Build Settings' `Preprocessor Macros` (for Debug only).

## Contribution

We want you!

Fork -> Clone -> Implement -> Test -> Pull-Request. We have great RESPECT for contributors.


## SOOMLA, Elsewhere ...

+ [Website](http://soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376)
+ [On AngelList](https://angel.co/the-soomla-project)


## License

MIT License. Copyright (c) 2012 SOOMLA. http://project.soom.la
+ http://www.opensource.org/licenses/MIT


