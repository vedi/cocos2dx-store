//
//  VirtualItem.h
//  cocos2dx-store
//
//  Created by Igor Yegoroff on 5/16/13.
//
//

#ifndef __cocos2dx_store__VirtualItem__
#define __cocos2dx_store__VirtualItem__

#include "cocos2d.h"
#include "../SoomlaMacros.h"
#include "JSONConstsX.h"

namespace soomla {
    
    class VirtualItem : public cocos2d::CCObject {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mName, Name, JSON_ITEM_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mDescription, Description, JSON_ITEM_DESCRIPTION);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mItemId, ItemId, JSON_ITEM_ITEMID);
        
    public:
        VirtualItem(): mName(NULL), mDescription(NULL), mItemId(NULL) {}

        static VirtualItem* create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId);
        static VirtualItem* createWithDictionary(cocos2d::CCDictionary* dict);

        virtual bool init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);
        
        virtual ~VirtualItem();
        
        virtual cocos2d::CCDictionary* toDictionary();
    };
    
}



#endif /* defined(__cocos2dx_store__VirtualItem__) */
