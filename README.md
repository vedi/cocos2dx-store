*This project is a part of [The SOOMLA Project](http://project.soom.la) which is a series of open source initiatives with a joint goal to help mobile game developers get better stores and more in-app purchases.*

Didn't you ever wanted an in-app purchase one liner that looks like this ?!

```cpp
    cocos2dx_StoreController::buyCurrencyPack("[Your product id here]");
```

cocos2dx-store
---

The cocod2dx-store shows you how to use The SOOMLA Project's [android-store](https://github.com/soomla/android-store) and [ios-store](https://github.com/soomla/ios-store) in your **cocos2d-x** project.
In cocos2dx-store there are 3 relevant scenes: MainScene, StoreAScene and StoreBScene:
    MainScene - the welcome scene from where you open the store.
    StoreAScene - the store's first window that contains a list of VirtualGoods.
    StoreBScene - the store's second window that contains a list of VirtualCurrencyPacks.

Getting Started
---

In order to run the iOS and Android projects you'll need to recursively clone cocos2dx-store:

```
git clone --recursive git@github.com:soomla/cocos2dx-store.git
```

> The **Android** project is an IntelliJ project. Just open the folder cocos2dx-store/cocos2dx-store/proj.android from IntelliJ to use it.

#### StoreController initialization

StoreController is intialized through cocos2dx_StoreController class. You'll need to initialize StoreController ONLY once from AppDelegate::applicationDidFinishLaunching ([example](https://github.com/soomla/cocos2dx-store/blob/master/cocos2dx-store/Classes/AppDelegate.cpp)).

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




