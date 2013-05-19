//
//  VirtualItem.cpp
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/16/13.
//
//

#include "VirtualItemX.h"

namespace soomla {
    
    using namespace cocos2d;

    VirtualItem* VirtualItem::create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId) {
        VirtualItem* pRet = new VirtualItem();
        if (pRet) {
            pRet->autorelease();
            pRet->init(name, description, itemId);
        }
        return pRet;
    }

    VirtualItem* VirtualItem::createWithDictionary(cocos2d::CCDictionary* dict) {
        VirtualItem* pRet = new VirtualItem();
        if (pRet) {
            pRet->autorelease();
            pRet->initWithDictionary(dict);
        }
        return pRet;
    }

    bool VirtualItem::init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId) {
        setName(name);
        setDescription(description);
        setItemId(itemId);
        
        return true;
    }
    
    bool VirtualItem::initWithDictionary(cocos2d::CCDictionary* dict) {
        fillNameFromDict(dict);
        fillDescriptionFromDict(dict);
        fillItemIdFromDict(dict);
        
        return true;
    }
    
    VirtualItem::~VirtualItem() {
        CC_SAFE_RELEASE(mName);
        CC_SAFE_RELEASE(mDescription);
        CC_SAFE_RELEASE(mItemId);
    }
    
    CCDictionary* VirtualItem::toDictionary() {
        CCDictionary* dict = CCDictionary::create();
        putNameToDict(dict);
        putDescriptionToDict(dict);
        putItemIdToDict(dict);

        return dict;
    }
}
