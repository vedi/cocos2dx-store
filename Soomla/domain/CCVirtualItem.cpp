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

//  Created by Igor Yegoroff on 5/16/13.

#include "CCVirtualItem.h"

namespace soomla {
    
    using namespace cocos2d;

    CCVirtualItem *CCVirtualItem::create(cocos2d::__String* name, cocos2d::__String* description, cocos2d::__String* itemId) {
        CCVirtualItem *ret = new CCVirtualItem();
        if (ret->init(name, description, itemId)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCVirtualItem::init(cocos2d::__String* name, cocos2d::__String* description, cocos2d::__String* itemId) {
        setName(name);
        setDescription(description);
        setItemId(itemId);
        
        return true;
    }
    
    bool CCVirtualItem::initWithDictionary(cocos2d::__Dictionary* dict) {
        fillNameFromDict(dict);
        fillDescriptionFromDict(dict);
        fillItemIdFromDict(dict);
        
        return true;
    }
    
    CCVirtualItem::~CCVirtualItem() {
        CC_SAFE_RELEASE(mName);
        CC_SAFE_RELEASE(mDescription);
        CC_SAFE_RELEASE(mItemId);
    }
    
    __Dictionary*CCVirtualItem::toDictionary() {
        __Dictionary* dict = __Dictionary::create();
        putNameToDict(dict);
        putDescriptionToDict(dict);
        putItemIdToDict(dict);

        return this->putTypeData(dict, CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_ITEM);
    }
}
