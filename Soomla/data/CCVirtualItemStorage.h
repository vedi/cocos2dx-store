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

#ifndef __CCVirtualItemStorage_H__
#define __CCVirtualItemStorage_H__

#include "cocos2d.h"
#include "CCVirtualItem.h"
#include "CCError.h"

namespace soomla {
    class CCVirtualItemStorage : public cocos2d::Ref {
    public:
        virtual int getBalance(CCVirtualItem *item, CCError **error = NULL);
        
        virtual int setBalance(CCVirtualItem *item, int balance, CCError **error = NULL) { return setBalance(item, balance, true, error); }
        virtual int setBalance(CCVirtualItem *item, int balance, bool notify, CCError **error = NULL);
        
        virtual int add(CCVirtualItem *item, int amount, CCError **error = NULL) { return add(item, amount, true, error); }
        virtual int add(CCVirtualItem *item, int amount, bool notify, CCError **error = NULL);
        
        virtual int remove(CCVirtualItem *item, int amount, CCError **error = NULL) { return remove(item, amount, true, error); }
        virtual int remove(CCVirtualItem *item, int amount, bool notify, CCError **error = NULL);
        
    protected:
        virtual const char* keyBalance(const char *itemId) const = 0;
        virtual void postBalanceChangeEvent(CCVirtualItem *item, int balance, int amountAdded) = 0;
    };
}

#endif // __CCVirtualItemStorage_H__
