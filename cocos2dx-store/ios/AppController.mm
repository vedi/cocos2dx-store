
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#import "EventHandling.h"
#import "cocos2dx_EventHandlers.h"
#import "VirtualCurrencyPack.h"
#import "AppStoreItem.h"
#import "VirtualGood.h"

#import "RootViewController.h"

@implementation AppController

static RootViewController* viewController;

+ (UIViewController*) rootViewController {
    return viewController;
}



#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0 ];

    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    [window addSubview: viewController.view];
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    
    [EventHandling observeAllEventsWithObserver:self withSelector:@selector(eventFired:)];

    cocos2d::CCApplication::sharedApplication()->run();
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

- (void)eventFired:(NSNotification*)notification{
    if ([notification.name isEqualToString:EVENT_APPSTORE_PURCHASED]) {
        AppStoreItem* apItem = (AppStoreItem*)[notification.userInfo objectForKey:@"AppStoreItem"];
        string productId([apItem.productId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->marketPurchase(productId);
    }
    else if ([notification.name isEqualToString:EVENT_VIRTUAL_GOOD_PURCHASED]) {
        VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:@"VirtualGood"];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->virtualGoodPurchased(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_VIRTUAL_GOOD_EQUIPPED]) {
        VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:@"VirtualGood"];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->virtualGoodEquipped(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_VIRTUAL_GOOD_UNEQUIPPED]) {
        VirtualGood* good = (VirtualGood*)[notification.userInfo objectForKey:@"VirtualGood"];
        string itemId([good.itemId UTF8String]);
        cocos2dx_EventHandlers::getInstance()->virtualGoodUnequipped(itemId);
    }
    else if ([notification.name isEqualToString:EVENT_BILLING_SUPPORTED]) {
        cocos2dx_EventHandlers::getInstance()->billingSupported();
    }
    else if ([notification.name isEqualToString:EVENT_BILLING_NOT_SUPPORTED]) {
        cocos2dx_EventHandlers::getInstance()->billingNotSupported();
    }
    else if ([notification.name isEqualToString:EVENT_MARKET_PURCHASE_STARTED]) {
        string productId("");
        cocos2dx_EventHandlers::getInstance()->marketPurchaseProcessStarted(productId);
    }
    else if ([notification.name isEqualToString:EVENT_GOODS_PURCHASE_STARTED]) {
        cocos2dx_EventHandlers::getInstance()->goodsPurchaseProcessStarted();
    }
    else if ([notification.name isEqualToString:EVENT_CLOSING_STORE]) {
        cocos2dx_EventHandlers::getInstance()->closingStore();
    }
    else if ([notification.name isEqualToString:EVENT_OPENING_STORE]) {
        cocos2dx_EventHandlers::getInstance()->openingStore();
    }
    else if ([notification.name isEqualToString:EVENT_UNEXPECTED_ERROR_IN_STORE]) {
        cocos2dx_EventHandlers::getInstance()->unexpectedErrorInStore();
    }
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}


@end

