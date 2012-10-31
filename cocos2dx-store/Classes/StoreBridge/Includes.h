//
//  Includes.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/27/12.
//
//

#ifndef cocos2dx_store_Includes_h
#define cocos2dx_store_Includes_h

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include <jni.h>
    #include "platform/android/jni/JniHelper.h"
    #include <android/log.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "iOSHelper.h"
#endif

#endif
