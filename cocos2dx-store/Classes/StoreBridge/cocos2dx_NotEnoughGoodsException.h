//
//  cocos2dx_NotEnoughGoodsException.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/23/12.
//
//

#ifndef __cocos2dx_store__NotEnoughGoodsException__
#define __cocos2dx_store__NotEnoughGoodsException__

#include <iostream>
#include <exception>

using namespace std;

class cocos2dx_NotEnoughGoodsException : public exception {
    
public:
    virtual const char* what() const throw() {
        return "The user doesn't have enough VirtualGoods to equip one !";
    }
};

#endif
