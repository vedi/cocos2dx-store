//
//  JniHelpers.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/28/12.
//
//

#ifndef __cocos2dx_store__JniHelpers__
#define __cocos2dx_store__JniHelpers__

#include "cocos2dx_VirtualItemNotFoundException.h"
#include "cocos2dx_InsufficientFundsException.h"
#include "cocos2dx_NotEnoughGoodsException.h"

class JniHelpers {
public:
	static void jniCommonVoidCall(const char* methodName, const char* classPath);
	static void jniCommonVoidCall(const char* methodName, const char* classPath, bool arg0);
    static void jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0)
		throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&);
    static int jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0, int arg1) 
		throw (cocos2dx_VirtualItemNotFoundException&);
	static int jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0) 
		throw (cocos2dx_VirtualItemNotFoundException&);
	static int jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0, const char* arg1) 
		throw (cocos2dx_VirtualItemNotFoundException&);
	static string jniCommonStringCall(const char* methodName, const char* classPath, const char* arg0) 
		throw (cocos2dx_VirtualItemNotFoundException&);
	static double jniCommonDoubleCall(const char* methodName, const char* classPath, const char* arg0) 
		throw (cocos2dx_VirtualItemNotFoundException&);
};

#endif /* defined(__cocos2dx_store__JniHelpers__) */
