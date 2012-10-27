//
//  cocos2dx_StoreController.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/22/12.
//
//

#include "cocos2dx_StoreController.h"

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

void cocos2dx_StoreController::storeOpening() {
    cocos2d::JniMethodInfo minfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","storeOpening", "()V"); 
    
    if (!isHave) {
        //do nothing
    } else {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void cocos2dx_StoreController::storeClosing() {
    cocos2d::JniMethodInfo minfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","storeClosing", "()V"); 
    
    if (!isHave) {
        //do nothing
    } else {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void cocos2dx_StoreController::initialize(bool debug) {
    cocos2d::JniMethodInfo minfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","initialize", "(Z)V"); 
    
    if (!isHave) {
        //do nothing
    } else {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, debug);
    }
}

void cocos2dx_StoreController::buyCurrencyPack(string productId) throw(cocos2dx_VirtualItemNotFoundException&){
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting buyCurrencyPack"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","buyCurrencyPack", "(Ljava/lang/String;)V"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(productId.c_str());
		
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "buyCurrencyPack returned");		
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION"); 
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
    }
}

void cocos2dx_StoreController::buyVirtualGood(string itemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting buyVirtualGood"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","buyVirtualGood", "(Ljava/lang/String;)V"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(itemId.c_str());
		
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "buyVirtualGood returned");		
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION"); 
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
			
			vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/InsufficientFundsException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought InsufficientFundsException!"); 

				throw cocos2dx_InsufficientFundsException();
			}
		}
    }
}

void cocos2dx_StoreController::buyManagedItem(string productId) throw(cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting buyManagedItem"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","buyManagedItem", "(Ljava/lang/String;)V"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(productId.c_str());
		
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "buyManagedItem returned");		
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION"); 
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
    }
}

void cocos2dx_StoreController::equipVirtualGood(string itemId) throw (cocos2dx_NotEnoughGoodsException&, cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting equipVirtualGood"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","equipVirtualGood", "(Ljava/lang/String;)V"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(itemId.c_str());
		
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "equipVirtualGood returned");		
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION"); 
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
			
			vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/NotEnoughGoodsException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought NotEnoughGoodsException!"); 

				throw cocos2dx_NotEnoughGoodsException();
			}
		}
    }
}

void cocos2dx_StoreController::unequipVirtualGood(string itemId) throw(cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting unequipVirtualGood"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreControllerBridge","unequipVirtualGood", "(Ljava/lang/String;)V"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(itemId.c_str());
		
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "unequipVirtualGood returned");		
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION"); 
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
    }
}


