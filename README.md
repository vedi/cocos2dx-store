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

StoreController is intialized through cocos2dx_StoreController class. You'll need to initialize StoreController ONLY once from AppDelegate::applicationDidFinishLaunching ([example](https://github.com/refaelos/cocos2dx-store/blob/master/cocos2dx-store/Classes/AppDelegate.cpp)).

Instructions for iOS
---

If you're building your cocos2dx applicaiton for iOS platforms you can open our xCode project and see how to integrate it with ios-store.
These is what's relevant to you:

1. You'll have to create your implementation of IStoreAssets that'll represent the assets in your specific game. We created an IStoreAsset's implementation for an imaginary game called Muffin Rush and we called it [MuffinRushAssets](https://github.com/refaelos/cocos2dx-store/blob/master/cocos2dx-store/ios/MuffinRushAssets.m).
