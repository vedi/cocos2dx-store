//
// Created by Fedor Shubin on 5/21/13.
//


#import <Foundation/Foundation.h>
#import "IStoreAsssets.h"

@interface StoreAssetsBridge : NSObject <IStoreAsssets>{
    int version;
    NSMutableArray* virtualCurrenciesArray;
    NSMutableArray* virtualGoodsArray;
    NSMutableArray* virtualCurrencyPacksArray;
    NSMutableArray* virtualCategoriesArray;
    NSMutableArray* nonConsumablesArray;
}

- (id)initWithStoreAssetsDict:(NSDictionary*)storeAssetsDict andVersion:(int)oVersion;

@end
