#include "com_soomla_cocos2dx_store_EventHandlerBridge.h"
#include "platform/android/jni/JniHelper.h"
#include "StoreAScene.h"
#include "StoreBScene.h"

#include <android/log.h>
#include <string>

using namespace std;

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_marketPurchase
  (JNIEnv * env, jobject obj, jstring productId){
	  string productIdStr = cocos2d::JniHelper::jstring2string(productId);
	  string msg(productIdStr);
	  msg.append(" was just purchased.");
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
	  
	  //StoreAScene::setCurrencyBalanceLabel();
	  StoreBScene::setCurrencyBalanceLabel();
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_marketRefund
  (JNIEnv * env, jobject obj, jstring productId){
	  string productIdStr = cocos2d::JniHelper::jstring2string(productId);
	  string msg(productIdStr);
	  msg.append(" was just refunded.");
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
	  
	  StoreBScene::setCurrencyBalanceLabel();
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_virtualGoodPurchased
  (JNIEnv * env, jobject obj, jstring itemId){
	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
	  string msg(itemIdStr);
	  msg.append(" was just purchased.");
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
	  
	  StoreAScene::setPriceBalanceLabel(itemIdStr.c_str());
	  StoreAScene::setCurrencyBalanceLabel();
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_virtualGoodEquipped
  (JNIEnv * env, jobject obj, jstring itemId){
	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
	  string msg(itemIdStr);
	  msg.append(" was just equipped.");
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_virtualGoodUnequipped
  (JNIEnv * env, jobject obj, jstring itemId){
	  string itemIdStr = cocos2d::JniHelper::jstring2string(itemId);
	  string msg(itemIdStr);
	  msg.append(" was just unequipped.");
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_billingSupported
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Billing is supported.");
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_billingNotSupported
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Billing is not supported.");
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_marketPurchaseProcessStarted
  (JNIEnv * env, jobject obj, jstring productId){
	  string productIdStr = cocos2d::JniHelper::jstring2string(productId);
	  string msg("bc Market purchase just started for: ");
	  msg += productIdStr;
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", msg.c_str());
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_goodsPurchaseProcessStarted
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "VirtualGoods purchase started.");
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_closingStore
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Store is closing.");
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_unexpectedErrorInStore
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Unexpected error occured.");
  }

JNIEXPORT void JNICALL Java_com_soomla_cocos2dx_store_EventHandlerBridge_openingStore
  (JNIEnv * env, jobject obj){
	  __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Store is opening.");
  }
