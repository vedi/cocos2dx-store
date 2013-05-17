LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/StoreBridge/JniHelpers.cpp \
                   ../../Classes/StoreBridge/cocos2dx_StoreController.cpp \
                   ../../Classes/StoreBridge/cocos2dx_StoreInventory.cpp \
				   ../../Classes/StoreBridge/cocos2dx_EventHandlers.cpp \
                   ../../Classes/StoreBridge/cocos2dx_StoreInfo.cpp \
                   ../../Classes/StoreBridge/com_soomla_cocos2dx_store_EventHandlerBridge.cpp \
                   ../../Classes/GameMenuItem.cpp \
                   ../../Classes/EventHandler.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/StoreAScene.cpp \
                   ../../Classes/StoreBScene.cpp \
                   ../../Classes/EasyNDK/NDKCallbackData.cpp \
                   ../../Classes/EasyNDK/NDKHelper.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += jansson_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,jansson)

