//
// Created by Fedor Shubin on 5/24/13.
//


#import <Foundation/Foundation.h>


@interface SoomlaEasyNDKGlue : NSObject

+ (NSObject *)dispatchNDKCall:(NSDictionary *)parameters;
+ (void)dispatchNDKCallback:(NSNotification*)notification;
@end