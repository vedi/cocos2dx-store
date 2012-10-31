//
//  cocos2dx_VirtualItemNotFoundException.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/23/12.
//
//

#ifndef __cocos2dx_store__VirtualItemNotFoundException__
#define __cocos2dx_store__VirtualItemNotFoundException__

#include <iostream>
#include <exception>

using namespace std;

class cocos2dx_VirtualItemNotFoundException : public exception {
    
public:
    
    virtual const char* what() const throw() {
        return "The requested virtual item was not found !";
    }
};

#endif
