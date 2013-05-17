//
//  SoomlaMacros.h
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/17/13.
//
//

#ifndef cocos2dx_store_SoomlaMacros_h
#define cocos2dx_store_SoomlaMacros_h

#include "cocos2d.h"

#define SL_SYNTHESIZE_RETAIN(varType, varName, funName)    \
private: varType varName; \
public: inline varType get##funName(void) const { return varName; } \
public: inline void set##funName(varType var)   \
{ \
    if (varName != var) \
    { \
        CC_SAFE_RETAIN(var); \
        CC_SAFE_RELEASE(varName); \
        varName = var; \
    } \
} \
private: inline void load##funName(cocos2d::CCDictionary* dict, std::string const& key) \
{ \
    cocos2d::CCObject* obj; \
    obj = dict->objectForKey(key); \
    CCAssert(obj == NULL || dynamic_cast<varType>(obj), "invalid object type in dictionary"); \
    if (varName != obj) \
    { \
        CC_SAFE_RETAIN(obj); \
        CC_SAFE_RELEASE(varName); \
        varName = (varType)obj; \
    } \
}
    

#endif
