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

#include "CCPurchaseType.h"
#include "CCSoomlaUtils.h"

namespace soomla {
    
    bool CCPurchaseType::init() {
        return true;
    }
    
    CCPurchaseType *CCPurchaseType::create() {
        CCPurchaseType *ret = new CCPurchaseType();
        if (ret->init()) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }
    
    void CCPurchaseType::buy(cocos2d::__String* payload, CCError **error) {
        CCSoomlaUtils::logError("SOOMLA PurchaseType", "Cannot buy CCPurchaseType");
    }
    
    CCPurchaseType::~CCPurchaseType() {}
}