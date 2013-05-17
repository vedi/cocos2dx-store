//
//  VirtualItem.cpp
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/16/13.
//
//

#include "VirtualItemX.h"
#include "JSONConstsX.h"

namespace soomla {
    
    using namespace cocos2d;
    
    bool VirtualItem::init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId) {
        setName(name);
        setDescription(description);
        setItemId(itemId);
        
        return true;
    }
    
    bool VirtualItem::initWithDictionary(cocos2d::CCDictionary* dict) {
        loadName(dict, JSON_ITEM_NAME);
        loadDescription(dict, JSON_ITEM_DESCRIPTION);
        loadItemId(dict, JSON_ITEM_ITEMID);
        
        return true;
    }
    
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
    
    VirtualItem::~VirtualItem() {
        CC_SAFE_RELEASE(mName);
        CC_SAFE_RELEASE(mDescription);
        CC_SAFE_RELEASE(mItemId);
        
        printf("VirtualItem dtor\n");
    }
    
    CCDictionary* VirtualItem::toDictionary() const {
        CCDictionary* dict = CCDictionary::create();
        dict->setObject(mName, "name");
        dict->setObject(mDescription, "description");
        dict->setObject(mItemId, "itemId");
        
        return dict;
    }
    
//    void VirtualItem::giveAmount(int amount) { CCAssert(0, "not implemented"); }
//    void VirtualItem::takeAmount(int amount) { CCAssert(0, "not implemented"); }
    
}
