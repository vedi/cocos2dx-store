/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

// Created by Igor Yegoroff on 5/17/13.

#ifndef __CCSoomlaMacros_h
#define __CCSoomlaMacros_h

#include "cocos2d.h"

#define SL_SYNTHESIZE_RETAIN_WITH_DICT(varType, varName, funName, jsonKey)    \
CC_SYNTHESIZE_RETAIN(varType, varName, funName); \
protected: inline void fill##funName##FromDict(cocos2d::__Dictionary* dict) \
{ \
    cocos2d::Ref* obj = dict->objectForKey(jsonKey); \
    CCAssert(obj == NULL || dynamic_cast<varType>(obj), "invalid object type in dictionary"); \
    if (varName != obj) \
    { \
        set##funName((varType)obj); \
    } \
} \
protected: inline void put##funName##ToDict(cocos2d::__Dictionary* dict) { \
  if (varName) { \
    dict->setObject(varName, jsonKey); \
  } \
}

#define SL_SYNTHESIZE_RETAIN_WITH_DICT_DCL(varType, varName, funName)    \
CC_SYNTHESIZE_RETAIN(varType, varName, funName); \
protected: inline void fill##funName##FromDict(cocos2d::__Dictionary* dict); \
protected: inline void put##funName##ToDict(cocos2d::__Dictionary* dict); \

#define SL_CREATE_WITH_DICTIONARY(__class) \
static __class *createWithDictionary(cocos2d::__Dictionary *dict) { \
    __class *ret = new __class(); \
    if (ret->initWithDictionary(dict)) { \
        ret->autorelease(); \
    } \
    else { \
        CC_SAFE_DELETE(ret); \
    } \
    return ret; \
} \

#endif // __CCSoomlaMacros_h
