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

namespace soomla {
    
    class VirtualItem : public cocos2d::CCObject {
        SL_SYNTHESIZE_RETAIN(cocos2d::CCString*, mName, Name)
        SL_SYNTHESIZE_RETAIN(cocos2d::CCString*, mDescription, Description)
        SL_SYNTHESIZE_RETAIN(cocos2d::CCString*, mItemId, ItemId)
        
    public:
        VirtualItem(): mName(NULL), mDescription(NULL), mItemId(NULL) {}
        
        virtual bool init(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);
        
        static VirtualItem* create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId);
        static VirtualItem* createWithDictionary(cocos2d::CCDictionary* dict);
        
        virtual ~VirtualItem();
        
        virtual cocos2d::CCDictionary* toDictionary() const;
//        virtual void giveAmount(int amount);
//        virtual void takeAmount(int amount);
    };
    
}



#endif /* defined(__cocos2dx_store__VirtualItem__) */
