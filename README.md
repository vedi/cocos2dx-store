*This project is a part of [The SOOMLA Project](http://project.soom.la) which is a series of open source initiatives with a joint goal to help mobile game developers get better stores and more in-app purchases.*

Haven't you ever wanted an in-app purchase one liner that looks like this ?!

```cpp
    soomla::StoreController::buyMarketItem("[itemId]");
```

# cocos2dx-store

**The new Virtual Economy model V3 is merged into master. The new model has many new features and it works better than the old one. Old applications may break if they use in this new model so if you have already published games with android-store from before May 1st, 2013 clone this project with the 'v2.2' tag and not the 'v3.0' tag.**

Want to learn more about modelV3? Try these:
* [Economy Model Objects - android-store](https://github.com/soomla/android-store/wiki/Economy-Model-Objects)
* [Handling Store Operations - android-store](https://github.com/soomla/android-store/wiki/Handling-Store-Operations)
(The same model objects from android-store exist in cocos2dx-store)

The cocos2dx-store is the Cocos2d-x flavour of The SOOMLA Project. This project uses [android-store](https://github.com/soomla/android-store) and [ios-store](https://github.com/soomla/ios-store) in order to provide game developers with in-app billing for their **cocos2d-x** projects.

**Before you start**, we suggest that you go over the information in ios-store and android-store so you get acquainted with the SOOMLA framework:
- ios-store [project](https://github.com/soomla/ios-store) [wiki](https://github.com/soomla/ios-store/wiki)
- android-store [project](https://github.com/soomla/android-store) [wiki](https://github.com/soomla/android-store/wiki)

>If you also want to create a **storefront** you can do that using SOOMLA's [In-App Purchase Store Designer](http://soom.la).

## Download

We've created a cocos2d-x extension and an example project:

#### cocos2dx-store v1.0

[Cocos2d-x - cocos2dx-store v1.0](http://bit.ly/XVWLZY)

#### cocos2dx-store-example v1.0

[Cocos2d-x - cocos2dx-store-example v1.0](about:blank)

## Getting Started

1. As with all Cocos2d-x projects, you need to clone the to Cocos2d-x framework from [here](https://github.com/cocos2d/cocos2d-x) or from the [Cocos2d-x website](http://www.cocos2d-x.org/download). If you decided to clone the git repository, make sure you're using the **2.1.4** tag.
2. Recursively clone this repository into the `extensions` directory located at the root of your Cocos2d-x framework.

```
$ cd cocos2d-x/
$ git clone --recursive git@github.com:soomla/cocos2dx-store.git extensions/cocos2dx-store
```

3. Clone the _jansson_ library into the `external` directory located at the root of your Cocos2d-x framework.
```
$ cd cocos2d-x/
$ git clone https://github.com/vedi/jansson.git external/jansson
```

4. Create a directory for your project in the `projects` directory located at the root of your Cocos2d-x framework.
5. cocos2dx-store contains project bundles for Android Studio (IntelliJ IDEA) and XCode. These bundles contain bridges that Cocos2d-x uses to communicate with our Java or Objective-C code. Open one of the bundles, and continue to the corresponding section.

> The **Android** project is an Android Studio project. Just open cocos2dx-store/proj.android from Android Studio to use it.


#### Instructions for iOS

To be added.


#### Instructions for Android

If you're building your cocos2dx application for the Android platform, open our Android Studio project from cocos2dx-store/proj.android and take a look at how to integrate it into .

#### In your Android Studio project:
1. Create an Android.mk similar to [the one](about:blank) under the proj.android/jni folder. Take a look at Application.mk and see how we added '-fexceptions' to 'APP_CPPFLAGS'.
2. From cocos2dx-store/android.proj, copy the `com` directory into your project's `src` directory. (you can remove the `example` subdirectory)
3. In the above [Getting Started](https://github.com/soomla/cocos2dx-store#getting-started), we mentioned you need to recursively clone cocos2dx-store. By doing that you also cloned [android-store](https://www.github.com/soomla/android-store) into the 'cocos2dx-store/submodules' directory. Make sure you add the folder 'SoomlaAndroidStore/src' from android-store into your classpath as a source folder.


#### In your Cocos2d-x project:
1. In your AppDelegate class, set the values for "Soom Sec", "Custom Secret", and "Public Key":
   - _Custom Secret_ - is an encryption secret you provide that will be used to secure your data.
   - _Public Key_ - is the public key given to you from Google. (iOS doesn't have a public key).
   - _Soom Sec_ - is a special secret SOOMLA uses to increase your data protection.
   **Choose both secrets wisely. You can't change them after you launch your game!**
   
```cpp
bool AppDelegate::applicationDidFinishLaunching() {
	/* ... */
	CCSoomla::sharedSoomla()->setSoomSec("ExampleSoomSecret");
	CCSoomla::sharedSoomla()->setPublicKey("ExampleCustomSecret");
	CCSoomla::sharedSoomla()->setCustomSecret("ExampleCustomSecret");
	/* ... */
}
```

2. Create your own implementation of _CCIStoreAssets_ that will represent the assets in your specific game ([example](about:blank)). Initialize _CCStoreController_ with the class you just created:
```cpp
	CCStoreController::createShared(YourStoreAssetsImplementation::create());
```

> Initialize _StoreController_ ONLY ONCE when your application loads.
3. Now, that you have _CCStoreController_ loaded, just decide when you want to show/hide your store's UI to the user and let _CCStoreController_ know about it:

When you show the store call:
```cpp
CCStoreController::sharedStoreController()->storeOpening();
```

When you hide the store call:
```cpp
CCStoreController::sharedStoreController()->storeClosing();
```

> Don't forget to make these calls. _StoreController_ has to know that you opened/closed your in-app purchase store. Just to make it clear: the in-app purchase store is where you sell virtual goods (and not Google Play or App Store).
4. You'll need an event handler in order to be notified about in-app purchasing related events. refer to the [Event Handling](about:blank) section for more information.

And that's it! You now have storage and in-app purchasing capabilities.


## What's next? In App Purchasing.

When we implemented modelV3, we were thinking about way people buy things inside apps. We figured there many ways you can let your users purchase items in your game and we designed the new modelV3 to support 2 for them: _PurchaseWithMarket_ and _PurchaseWithVirtualItem_.

**PurchaseWithMarket** is a _PurchaseType_ that allows users to purchase a _VirtualItem_ with Google Play or the App Store.
**PurchaseWithVirtualItem** is a _PurchaseType_ that lets your users purchase a _VirtualItem_ with a different _VirtualItem_. For example: Buying a sword with 100 gems.

In order to define the way your various virtual itemsare purchased, you'll need to create your implementation of _CCIStoreAssets_ (the same one from step 2 in the [Getting Started](about:blank) section above).

Here is an example:

To create a _VirtualCurrencyPack_ you call `TEN_COINS_PACK` first define a _VirtualCurrency_ you call `COIN_CURRENCY` and then define the pack:

```cpp
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

Now you can use _StoreInventory_ to buy your new currency pack:

```cpp
CCStoreInventory::sharedStoreInventory()->buyItem(TEN_COIN_PACK_ITEM_ID);
```

And that's it! cocos2dx-store knows how to contact Google Play or the App Store for you and will redirect your users to the purchasing system to complete the transaction. Don't forget to subscribe to store events in order to get the notified of successful or failed purchases (see [Event Handling](about:blank)).

**Test purchases on Android** will not work (even in the debug library) if you won't switch Android's test mode on. In order to do that, call `CCSoomla::setAndroidTestMode(true)` in your AppDelegate class before initializing _CCStoreController_.

## Storage & Meta-Data

When you initialize _CCStoreController_, it automatically initializes two other classes: _CCStoreInventory_ and _CCStoreInfo_:
* _CCStoreInventory_ is a convenience class to let you perform operations on VirtualCurrencies and VirtualGoods. Use it to fetch/change the balances of VirtualItems in your game (using their ItemIds!)  
* _CCStoreInfo_ is where all meta data information about your specific game can be retrieved. It is initialized with your implementation of _CCIStoreAssets_ and you can use it to retrieve information about your specific game.

The on-device storage is encrypted and kept in a SQLite database. SOOMLA is preparing a cloud-based storage service that will allow this SQLite to be synced to a cloud-based repository that you'll define.

**Example Usages**

* Get all the VirtualCurrencies:

```cpp
CCArray *vcArray = CCStoreInfo::sharedStoreInfo()->getVirtualCurrencies();
```

* Give the user 10 pieces of a virtual currency with itemId "currency_coin":

```cpp
CCStoreInventory::sharedStoreInventory()->giveItem("currency_coin", 10);
```

* Take 10 virtual goods with itemId "green_hat":

```cpp
CCStoreInventory::sharedStoreInventory()->takeItem("green_hat", 10);
```

* Get the current balance of green hats (virtual goods with itemId "green_hat"):

```cpp
int greenHatsBalance = CCStoreInventory::sharedStoreInventory()->getItemBalance("green_hat");
```

## Event Handling

SOOMLA lets you subscribe to store events, get notified and implement your own application specific behaviour to those events.

> Your behaviour is an addition to the default behaviour implemented by SOOMLA. You don't replace SOOMLA's behaviour.

The _CCSoomla_ class is where all event go through. To handle various events, create your own event handler, a class that implements _CCEventHandler_, and add it to the _CCSoomla_ class:

```cpp
CCSoomla::sharedSoomla()->addEventHandler(yourEventHandler);
```

## Debugging

The download packages and the code in the repo using the "release" versions of android-store and ios-store. Also, Cocos2d-x debug messages will only be printed out if you set `SOOMLA_DEBUG` to `true` in CCStoreUtils.

If you want to see full debug messages from android-store and ios-store you'll have to use the debug builds of those libraries. You can find those builds in the repo, in the folder _soomla-native_ ([android](https://github.com/soomla/unity3d-store/blob/master/soomla-native/android/Soomla_debug.jar)  [ios](https://github.com/soomla/unity3d-store/blob/master/soomla-native/ios/release/libSoomlaIOSStore.a)).

## Contribution

We want you!

Fork -> Clone -> Implement -> Test -> Pull-Request. We have great RESPECT for contributors.

## SOOMLA, Elsewhere ...

+ [Website](http://project.soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376).
+ [On AngelList](https://angel.co/the-soomla-project)

## License

MIT License. Copyright (c) 2012 SOOMLA. http://project.soom.la
+ http://www.opensource.org/licenses/MIT


