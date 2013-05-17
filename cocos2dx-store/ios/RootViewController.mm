
#import "RootViewController.h"
#import "IOSNDKHelper.h"


@implementation RootViewController

 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Tell NDKHelper that RootViewController will respond to messages
        // Coming from C++
        [IOSNDKHelper setNDKReceiver:self];
    }
    return self;
}

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/

- (BOOL)shouldAutorotate
{
    //returns true if want to allow orientation change
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations
{
    // return UIInterfaceOrientationMaskLandscape;
	
    // switch to this line if you want to set portrait view
    return UIInterfaceOrientationMaskPortrait;
}

// Override to allow orientations other than the default landscape orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // return UIInterfaceOrientationIsLandscape( interfaceOrientation );
    
    // switch to this line if you want to set portrait view
    return UIInterfaceOrientationIsPortrait( interfaceOrientation );
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

#pragma mark -
#pragma mark Easy NDK methods

- (void) soomla_easyNDKTest:(NSObject *)params {
    NSLog(@"soomla_easyNDKTest call");
    NSDictionary *parameters = (NSDictionary*) params;
    NSLog(@"Passed params are : %@", parameters);

    NSLog(@"Send them back to native code");
    [IOSNDKHelper sendMessage:@"soomla_easyNDKCallBackTest" withParameters:params];
}



@end
