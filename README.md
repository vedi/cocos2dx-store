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