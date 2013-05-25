LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/EventHandler.cpp \
                   ../../Classes/GameMenuItem.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/MuffinRushAssets.cpp \
                   ../../Classes/StoreAScene.cpp \
                   ../../Classes/StoreBScene.cpp \
                   ../../Classes/EasyNDK/NDKCallbackData.cpp \
                   ../../Classes/EasyNDK/NDKHelper.cpp \
	../../Classes/Soomla/CCSoomla.cpp \
	../../Classes/Soomla/CCSoomlaEasyNdkBridge.cpp \
	../../Classes/Soomla/CCSoomlaError.cpp \
	../../Classes/Soomla/CCStoreController.cpp \
	../../Classes/Soomla/CCStoreInventory.cpp \
	../../Classes/Soomla/CCStoreUtils.cpp \
	../../Classes/Soomla/PurchaseTypes/CCPurchaseType.cpp \
	../../Classes/Soomla/PurchaseTypes/CCPurchaseWithMarket.cpp \
	../../Classes/Soomla/PurchaseTypes/CCPurchaseWithVirtualItem.cpp \
	../../Classes/Soomla/data/CCStoreInfo.cpp \
	../../Classes/Soomla/data/SoomlaJSONConsts.cpp \
	../../Classes/Soomla/domain/CCMarketItem.cpp \
	../../Classes/Soomla/domain/CCNonConsumableItem.cpp \
	../../Classes/Soomla/domain/CCPurchasableVirtualItem.cpp \
	../../Classes/Soomla/domain/CCVirtualCategory.cpp \
	../../Classes/Soomla/domain/CCVirtualItem.cpp \
	../../Classes/Soomla/domain/virtualCurrencies/CCVirtualCurrency.cpp \
	../../Classes/Soomla/domain/virtualCurrencies/CCVirtualCurrencyPack.cpp \
	../../Classes/Soomla/domain/virtualGoods/CCEquippableVG.cpp \
	../../Classes/Soomla/domain/virtualGoods/CCLifetimeVG.cpp \
	../../Classes/Soomla/domain/virtualGoods/CCSingleUsePackVG.cpp \
	../../Classes/Soomla/domain/virtualGoods/CCSingleUseVG.cpp \
	../../Classes/Soomla/domain/virtualGoods/CCUpgradeVG.cpp \
	../../Classes/Soomla/domain/virtualGoods/CCVirtualGood.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += jansson_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,jansson)

