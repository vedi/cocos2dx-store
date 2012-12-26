*This project is a part of [The SOOMLA Project](http://project.soom.la) which is a series of open source initiatives with a joint goal to help mobile game developers get better stores and more in-app purchases.*

Didn't you ever wanted an in-app purchase one liner that looks like this ?!

```cpp
    cocos2dx_StoreController::buyCurrencyPack("[Product id here]");
```

cocos2dx-store
---

The cocod2dx-store shows you how to use The SOOMLA Project's [android-store](https://github.com/soomla/android-store) and [ios-store](https://github.com/soomla/ios-store) in your **cocos2d-x** project.
In cocos2dx-store there are 3 relevant scenes: MainScene, StoreAScene and StoreBScene:
    MainScene - the welcome scene from where you open the store.
    StoreAScene - the store's first window that contains a list of VirtualGoods.
    StoreBScene - the store's second window that contains a list of VirtualCurrencyPacks.

We suggest that you go obver the information on ios-store and android-store:
- ios-store [project](https://github.com/soomla/ios-store) [wiki](https://github.com/soomla/ios-store/wiki)
- android-store [project](https://github.com/soomla/android-store) [wiki](https://github.com/soomla/android-store/wiki)

>If you also want to create a storefront you can do that using our [Store Designer](designer.soom.la).

Getting Started
---

In order to run the iOS and Android projects you'll need to recursively clone cocos2dx-store:

```
git clone --recursive git@github.com:soomla/cocos2dx-store.git
```

> The **Android** project is an IntelliJ project. Just open the folder cocos2dx-store/cocos2dx-store/proj.android from IntelliJ to use it.

#### Application secret

The first thing you should do is go to StoreConfig.java (Android) and StoreConfig.m (iOS) and change the value for the variable SOOM_SEC. Do this now! **This value is set once and cannot be changed after you publish you game.**

#### StoreController initialization

StoreController is intialized through cocos2dx_StoreController class. "initialize" is called with another secret. This secret is also unchangable and it's purpose is to provide more security to your game's data. **This value is set once and cannot be changed after you publish you game.**

You'll need to initialize StoreController ONLY once from AppDelegate::applicationDidFinishLaunching ([example](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/Classes/AppDelegate.cpp)).

Instructions for iOS
---

If you're building your cocos2dx applicaiton for the iOS platform, open our xCode project and see how to integrate it with ios-store.
The example ios project needs to be enough, but if you want more info than this is what's relevant to you:

1. You'll have to create your implementation of IStoreAssets that'll represent the assets in your specific game. We created an IStoreAsset's implementation for an imaginary game called Muffin Rush and we called it [MuffinRushAssets](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/ios/MuffinRushAssets.m).
2. We've created our cocos2dx UI in cocos2dx-store/Classes. You don't need these files. Just look into [AppDelegate.cpp](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/Classes/AppDelegate.cpp) and see where we initialize cocos2dx_StoreController and do the same in your game.
3. You'll need ONLY the HEADER files from cocos2dx-store/Classes/StoreBridge to be included in your game's ios project. (EXCEPT for JniHelpers.h !)
4. From cocos2dx-store/ios, copy the following files into your ios project: cocos2dx_StoreController.mm, cocos2dx_StoreInfo.mm, cocos2dx_StoreInventory.mm, iOSHelper.mm, iOSHelper.h.
5. In the above [Getting Started](https://github.com/soomla/cocos2dx-store#getting-started), we said you need to recursively clone cocos2dx-store. By doing that you also cloned [ios-store](https://www.github.com/soomla/ios-store) into the folder 'submodules'. Make sure you add the folder 'SoomlaiOSStore' from ios-store into your project. 
6. Make sure you go over [ios-store Getting Started](https://github.com/soomla/ios-store#getting-started-using-source-code) for more instructions. for example: make sure you add '-fno-objc-arc' to the source JSONKit.m in Build Phases.

Instructions for Android
---

If you're building your cocos2dx applicaiton for the Android platform, open our IntelliJ project from cocos2dx-store/proj.android and see how to integrate it with android-store.
The example Android project needs to be enough, but if you want more info than this is what's relevant to you:

1. You'll have to create your implementation of IStoreAssets that'll represent the assets in your specific game. We created an IStoreAsset's implementation for an imaginary game called Muffin Rush and we called it [MuffinRushAssets](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/proj.android/src/com/soomla/cocos2dx/example/MuffinRushAssets.java).
2. We've created our cocos2dx UI in cocos2dx-store/Classes. You don't need these files. Just look into [AppDelegate.cpp](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/Classes/AppDelegate.cpp) and see where we initialize cocos2dx_StoreController and do the same in your game.
3. You'll need an Android.mk similar to [the one](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/proj.android/jni/Android.mk) under proj.android/jni folder.
4. Look into Application.mk and see how we added '-fexceptions' to 'APP_CPPFLAGS'.
5. From cocos2dx-store/android.proj, copy the folder 'com' into your project's 'src' folder. (you can remove the subfolder 'example')
6. In the above [Getting Started](https://github.com/soomla/cocos2dx-store#getting-started), we said you need to recursively clone cocos2dx-store. By doing that you also cloned [android-store](https://www.github.com/soomla/android-store) into the folder 'submodules'. Make sure you add the folder 'SoomlaAndroidStore/src' from android-store into your classpath as a source folder.
7. Make sure you go over [ios-store Getting Started](https://github.com/soomla/android-store#getting-started) for more instructions.

What's next? In App Purchasing.
---

android-store and ios-store provides you with VirtualCurrencyPacks. VirtualCurrencyPack is a representation of a "bag" of currencies that you want to let your users purchase in Google Play or App-Store. You define VirtualCurrencyPacks in your game specific assets file which is your implemetation of IStoreAssets (examples: [android](https://github.com/soomla/android-store/blob/master/SoomlaAndroidExample/src/com/soomla/example/MuffinRushAssets.java) [ios](https://github.com/soomla/ios-store/blob/master/SoomlaiOSStoreExample/SoomlaiOSStoreExample/MuffinRushAssets.m)). 
After you do that you can use cocos2dx-store to call cocos2dx_StoreController to make actual purchases and android-store or ios-store will take care of the rest.

Example:

Lets say you have a VirtualCurrencyPack you call TEN_COINS_PACK, a VirtualCurrency you call COIN_CURRENCY and a VirtualCategory you call CURRENCYPACKS_CATEGORY:

```Java
VirtualCurrencyPack TEN_COINS_PACK = new VirtualCurrencyPack(
        "10 Coins",                // name
        "A pack of 10 coins",      // description
        "10_coins",                // item id
        TEN_COINS_PACK_PRODUCT_ID, // product id in Google Market
        1.99,                      // actual price in $$
        10,                        // number of currencies in the pack
        COIN_CURRENCY);            // the associated currency
```

```objective-c
VirtualCurrencyPack* TEN_COINS_PACK = [[VirtualCurrencyPack alloc] initWithName:@"10 Coins"
                                              andDescription:@"A pack of 10 coins"
                                                   andItemId:@"10_coins"
                                                    andPrice:0.99
                                                andProductId:TEN_COINS_PACK_PRODUCT_ID
                                           andCurrencyAmount:10
                                                 andCurrency:COIN_CURRENCY];
```

Now you can use cocos2dx_StoreController to call the in-app purchasing mechanism:

>This is a full example the shows you how to do everything from the click event handler to the actual purchase and event handling. You can find the full example [here](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/Classes/StoreBScene.cpp).

```cpp
void StoreScene::menuChooseCallback(CCObject* pSender)
{
    if (pSender)
    {
		GameMenuItem* item = (GameMenuItem*)pSender;

		int tag = item->getTag();
		char productId[512];
		snprintf(productId, sizeof(productId), productIdFromTag(tag).c_str());
		try{
			if (tag == 0) {

			} else {
				cocos2dx_StoreController::buyCurrencyPack(productId);
			}
		}
		catch (cocos2dx_VirtualItemNotFoundException& e) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "Cought cocos2dx_VirtualItemNotFoundException from NATIVE!");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            iOSHelper::LogMessage("Cought cocos2dx_VirtualItemNotFoundException!");
#endif
		}
	}
}
```

And that's it! android-store and ios-store knows how to contact Google Play and the App Store for you and redirect the user to the purchasing mechanism. 
**IMPORTANT:** Don't forget to handle in cocos2dx_EventHandler.cpp in order to get the events of successful or failed purchase.

Storage & Meta-Data
---

When you initialize cocos2dx_StoreController, ios-store and android-store automatically initializes two other classes: StorageManager and StoreInfo which makes 2 cocos2dx classes relevant: 
* cocos2dx_StoreInventory is used to acccess all stoaage related instances in your game. Use it to access tha balances of virtual currencies and virtual goods (ususally, using their itemIds). 
* cocos2dx_StoreInfo is the mother of all meta data information about your specific game. ios-store and android-store initializes StoreInfo with your implementation of IStoreAssets so you can use cocos2dx_StoreInfo to retrieve information about your specific game.

The on-device storage is encrypted and kept in a SQLite database. SOOMLA is preparing a cloud-based storage service that'll allow this SQLite to be synced to a cloud-based repository that you'll define. Stay tuned... this is just one of the goodies we prepare for you.

Example Usages

Add 10 coins to the virtual currency with itemId "currency_coin":

```cpp
string itemId("currency_coin");
cocos2dx_StoreInventory::addCurrencyAmount(itemId, 10);
```

Remove 10 virtual goods with itemId "green_hat":

```cpp
string itemId("green_hat");
cocos2dx_StoreInventory::removeGoodAmount(itemId, 10);
```

Get the current balance of green hats (virtual goods with itemId "green_hat"):

```cpp
string itemId("green_hat");
int balance = cocos2dx_StoreInventory::getCurrencyBalance(itemId);
```

>Make sure you handle the appropriate exceptions when using any cocos2dx_* class. Look in the header files in ../Classes/StoreBridge to see what exceptions are thrown.

Contribution
---

We want you!

Fork -> Clone -> Implement -> Test -> Pull-Request. We have great RESPECT for contributors.

SOOMLA, Elsewhere ...
---

+ [Website](http://project.soom.la/)
+ [On Facebook](https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376).
+ [On AngelList](https://angel.co/the-soomla-project)

License
---
MIT License. Copyright (c) 2012 SOOMLA. http://project.soom.la
+ http://www.opensource.org/licenses/MIT


