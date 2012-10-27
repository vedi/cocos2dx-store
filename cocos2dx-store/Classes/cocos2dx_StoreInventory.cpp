//
//  cocos2dx_StoreInventory.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/24/12.
//
//

#include "cocos2dx_StoreInventory.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

int cocos2dx_StoreInventory::getCurrencyBalance(string currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting getCurrencyBalance"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreInventoryBridge","getCurrencyBalance", "(Ljava/lang/String;)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(currencyItemId.c_str());
		
        jint balance = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "getCurrencyBalance returned");		
		
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
		
		return (int)balance;
    }
	
	return 0;
}

int cocos2dx_StoreInventory::addCurrencyAmount(string currencyItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting addCurrencyAmount"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreInventoryBridge","addCurrencyAmount", "(Ljava/lang/String;I)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(currencyItemId.c_str());
		
        jint balance = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, amount);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "addCurrencyAmount returned");		
		
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
		
		return (int)balance;
    }
	
	return 0;
}

int cocos2dx_StoreInventory::removeCurrencyAmount(string currencyItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting removeCurrencyAmount"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreInventoryBridge","removeCurrencyAmount", "(Ljava/lang/String;I)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(currencyItemId.c_str());
		
        jint balance = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, amount);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "removeCurrencyAmount returned");		
		
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
		
		return (int)balance;
    }
	
	return 0;
}

int cocos2dx_StoreInventory::getGoodBalance(string goodItemId)  throw (cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting getGoodBalance"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreInventoryBridge","getGoodBalance", "(Ljava/lang/String;)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(goodItemId.c_str());
		
        jint balance = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "getGoodBalance returned");		
		
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
		
		return (int)balance;
    }
	
	return 0;
}

int cocos2dx_StoreInventory::addGoodAmount(string goodItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting addGoodAmount"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreInventoryBridge","addGoodAmount", "(Ljava/lang/String;I)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(goodItemId.c_str());
		
        jint balance = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, amount);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "addGoodAmount returned");		
		
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
		
		return (int)balance;
    }
	
	return 0;
}

int cocos2dx_StoreInventory::removeGoodAmount(string goodItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
    cocos2d::JniMethodInfo minfo;
    
	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Starting removeGoodAmount"); 
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,"com/soomla/store/StoreInventoryBridge","removeGoodAmount", "(Ljava/lang/String;I)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(goodItemId.c_str());
		
        jint balance = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, amount);
		
		minfo.env->DeleteLocalRef(stringArg0);

		__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "removeGoodAmount returned");		
		
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
		
		return (int)balance;
    }
	
	return 0;

}
