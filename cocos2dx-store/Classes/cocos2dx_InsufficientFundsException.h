//
//  cocos2dx_InsufficientFundsException.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/23/12.
//
//

#ifndef __cocos2dx_store__InsufficientFundsException__
#define __cocos2dx_store__InsufficientFundsException__

#include <iostream>
#include <exception>

using namespace std;

class cocos2dx_InsufficientFundsException : public exception {
    
public:
    
    virtual const char* what() const throw() {
        return "The user doesn't have enough funds to purchase the requested VirtualGood !";
    }
};

#endif
