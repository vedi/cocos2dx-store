//
//  iOSHelper.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/27/12.
//
//

#include "iOSHelper.h"
#import "AnalyticXStringUtil.h"
    
void iOSHelper::LogMessage(const char* msg) {
    NSString *message = [AnalyticXStringUtil nsstringFromCString:msg];
    NSLog(@"%@", message);
}
