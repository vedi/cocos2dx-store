/**
 * Created by vedi on 1/21/14.
 */

var PrevSoomla = Soomla;
Soomla = new function () {

  var Soomla = _.extend(PrevSoomla, {Models: {}}); // merge with binding instance

  Soomla.DEBUG = false;

  var declareClass = Soomla.declareClass = function (ClassName, fields, parentClass) {
    var Clazz = function () {
      return _.extend(parentClass ? parentClass() : {}, fields ? fields : {}, {
        jsonType: ClassName
      });
    };
    Clazz.create = function (values) {
      return _.defaults(values ? _.omit(values, "jsonType") : {}, Clazz());
    };

    return Clazz;
  };

  /**
   * Domain
   */
  var Domain = Soomla.Models.SoomlaEntity = declareClass("Domain", {
  });

  /**
   * SoomlaEntity
   */
  var SoomlaEntity = Soomla.Models.SoomlaEntity = declareClass("SoomlaEntity", {
    name: "",
    description: "",
    itemId: null
  }, Domain);

  /**
   * VirtualItem
   */
  var VirtualItem = Soomla.Models.VirtualItem = declareClass("VirtualItem", {
  }, SoomlaEntity);

  /**
   * VirtualCategory
   */
  var VirtualCategory = Soomla.Models.VirtualCategory = declareClass("VirtualCategory", {
    name: "",
    goods_itemIds: null
  }, Domain);

  /**
   * MarketItem
   */
  var MarketItem = Soomla.Models.MarketItem = declareClass("MarketItem", {
    productId: null,
    consumable: null,
    price: null,
    market_price: null,
    market_title: null,
    market_desc: null
  }, Domain);
  MarketItem.Consumable = {
    NONCONSUMABLE: 0,
    CONSUMABLE: 1,
    SUBSCRIPTION: 2
  };

  var PURCHASE_TYPE = {
    MARKET: "market",
    VI: "virtualItem"
  };

  /**
   * PurchasableVirtualItem
   */
  var PurchasableVirtualItem = Soomla.Models.PurchasableVirtualItem = declareClass("PurchasableVirtualItem", {
    purchasableItem: null
  }, VirtualItem);

  /**
   * NonConsumableItem
   */
  var NonConsumableItem = Soomla.Models.NonConsumableItem = declareClass("NonConsumableItem", {

  }, PurchasableVirtualItem);

  /**
   * VirtualCurrency
   */
  var VirtualCurrency = Soomla.Models.VirtualCurrency = declareClass("VirtualCurrency", {
  }, VirtualItem);

  /**
   * VirtualCurrencyPack
   */
  var VirtualCurrencyPack = Soomla.Models.VirtualCurrencyPack = declareClass("v", {
    currency_amount: 0,
    currency_itemId: null
  }, PurchasableVirtualItem);

  /**
   * VirtualGood
   */
  var VirtualGood = Soomla.Models.VirtualGood = declareClass("VirtualGood", {
  }, PurchasableVirtualItem);

  /**
   * LifetimeVG
   */
  var LifetimeVG = Soomla.Models.LifetimeVG = declareClass("LifetimeVG", {
  }, VirtualGood);

  /**
   * EquippableVG
   */
  var EquippableVG = Soomla.Models.EquippableVG = declareClass("EquippableVG", {
    equipping: null
  }, LifetimeVG);
  EquippableVG.EquippingModel = {
    LOCAL: "local",
    CATEGORY: "category",
    GLOBAL: "global"
  };

  /**
   * SingleUseVG
   */
  var SingleUseVG = Soomla.Models.SingleUseVG = declareClass("SingleUseVG", {
  }, VirtualGood);

  /**
   * SingleUsePackVG
   */
  var SingleUsePackVG = Soomla.Models.SingleUsePackVG = declareClass("SingleUsePackVG", {
    good_itemId: null,
    good_amount: null
  }, VirtualGood);

  /**
   * UpgradeVG
   */
  var UpgradeVG = Soomla.Models.UpgradeVG = declareClass("UpgradeVG", {
    good_itemId: null,
    prev_itemId: null,
    next_itemId: null
  }, VirtualGood);

  /**
   * PurchaseType
   */
  var PurchaseType = Soomla.Models.PurchaseType = declareClass("PurchaseType", {
    purchaseType: null
  });

  /**
   * PurchaseWithMarket
   */
  var PurchaseWithMarket = Soomla.Models.PurchaseWithMarket = declareClass("PurchaseWithMarket", {
    purchaseType: PURCHASE_TYPE.MARKET,
    marketItem: null
  }, PurchaseType);

  PurchaseWithMarket.createWithMarketItem = function(productId, price) {
    var marketItem = MarketItem.create({
      productId: productId,
      consumable: MarketItem.Consumable.CONSUMABLE,
      price: price
    });
    return PurchaseWithMarket.create({marketItem: marketItem});
  };

  /**
   * PurchaseWithVirtualItem
   */
  var PurchaseWithVirtualItem = Soomla.Models.PurchaseWithVirtualItem = declareClass("PurchaseWithVirtualItem", {
    purchaseType: PURCHASE_TYPE.VI,
    pvi_itemId: null,
    pvi_amount: null
  }, PurchaseType);


  //------ Profile ------//
  /**
   * UserProfile
   */
  var UserProfile = Soomla.Models.UserProfile = declareClass("UserProfile", {
    provider: null,
    profileId: null,
    email: null,
    firstName: null,
    lastName: null,
    avatarLink: null,
    location: null,
    gender: null,
    language: null,
    birthday: null
  }, Domain);

  var Provider = Soomla.Models.Provider = {
    FACEBOOK: {id: 0, key: 'facebook'},
    FOURSQUARE: {id: 1, key: 'foursquare'},
    GOOGLE: {id: 2, key: 'google'},
    LINKEDIN: {id: 3, key: 'linkedin'},
    MYSPACE: {id: 4, key: 'myspace'},
    TWITTER: {id: 5, key: 'twitter'},
    YAHOO: {id: 6, key: 'yahoo'},
    SALESFORCE: {id: 7, key: 'salesforce'},
    YAMMER: {id: 8, key: 'yammer'},
    RUNKEEPER: {id: 9, key: 'runkeeper'},
    INSTAGRAM: {id: 10, key: 'instagram'},
    FLICKR: {id: 11, key: 'flickr'}
  };

  Provider.findById = function(id) {
    _.find(Soomla.Models.Provider, function(provider) {
      return !_.isFunction(provider) && provider.id == id;
    })
  };
  Provider.findByKey = function(key) {
    _.find(Soomla.Models.Provider, function(provider) {
      return !_.isFunction(provider) && provider.key == key;
    });
  };

  var SocialActionType = Soomla.Models.SocialActionType = {
    UPDATE_STATUS: 0,
    UPDATE_STORY: 1,
    UPLOAD_IMAGE: 2,
    GET_CONTACTS: 3,
    GET_FEED: 4
  };


  function extractModel(retParams) {
    return retParams.return;
  }

  function extractCollection(retParams) {
    var retArray = retParams.return;

    var result = [];
    for (var i = 0; i < retArray.length; i++) {
      result.push(retArray[i]);
    }
    return result;
  }

  /**
   * StoreInfo
   */
  var StoreInfo = Soomla.StoreInfo = declareClass("StoreInfo", {
    init: function(storeAssets) {
      callNative({
        method: "CCStoreAssets::init",
        version: storeAssets.version,
        storeAssets: storeAssets
      });
      return true;
    },
    getItemByItemId: function(itemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getItemByItemId",
        itemId: itemId
      });
      return extractModel(retParams);
    },
    getPurchasableItemWithProductId: function(productId) {
      var retParams = callNative({
        method: "CCStoreInfo::getPurchasableItemWithProductId",
        productId: productId
      });
      return extractModel(retParams);
    },
    getCategoryForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getCategoryForVirtualGood",
        goodItemId: goodItemId
      });
      return extractModel(retParams);
    },
    getFirstUpgradeForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getFirstUpgradeForVirtualGood",
        goodItemId: goodItemId
      });
      return extractModel(retParams);
    },
    getLastUpgradeForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getLastUpgradeForVirtualGood",
        goodItemId: goodItemId
      });
      return extractModel(retParams);
    },
    getUpgradesForVirtualGood: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInfo::getUpgradesForVirtualGood",
        goodItemId: goodItemId
      });

      return extractCollection(retParams);
    },
    getVirtualCurrencies: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualCurrencies"
      });
      return extractCollection(retParams);
    },
    getVirtualGoods: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualGoods"
      });
      return extractCollection(retParams);
    },
    getVirtualCurrencyPacks: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualCurrencyPacks"
      });
      return extractCollection(retParams);
    },
    getNonConsumableItems: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getNonConsumableItems"
      });
      return extractCollection(retParams);
    },
    getVirtualCategories: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualCategories"
      });
      return extractCollection(retParams);
    }
  });

  StoreInfo.createShared = function(storeAssets) {
    var ret = new StoreInfo();
    if (ret.init(storeAssets)) {
      Soomla.storeInfo = ret;
    } else {
      Soomla.storeInfo = null;
    }
  };

  var IStoreAssets = Soomla.IStoreAssets = declareClass("IStoreAssets", {
    categories: [],
    currencies: [],
    currencyPacks: [],
    goods: {
      singleUse: [],
      lifetime: [],
      equippable: [],
      goodUpgrades: [],
      goodPacks: []
    },
    nonConsumables: [],
    version: 1
  });

  /**
   * EventHandler
   */
  var EventHandler = Soomla.EventHandler = declareClass("EventHandler", {
    onBillingNotSupported: function() {},
    onBillingSupported: function() {},
    onCurrencyBalanceChanged: function(virtualCurrency, balance, amountAdded) {},
    onGoodBalanceChanged: function(virtualGood, balance, amountAdded) {},
    onGoodEquipped: function(equippableVG) {},
    onGoodUnEquipped: function(equippableVG) {},
    onGoodUpgrade: function(virtualGood, upgradeVG) {},
    onItemPurchased: function(purchasableVirtualItem) {},
    onItemPurchaseStarted: function(purchasableVirtualItem) {},
    onMarketPurchaseCancelled: function(purchasableVirtualItem) {},
    onMarketPurchase: function(purchasableVirtualItem, token, payload) {},
    onMarketPurchaseStarted: function(purchasableVirtualItem) {},
    onMarketItemsRefreshStarted: function() {},
    onMarketItemsRefreshed: function(marketItems) {},
    onMarketPurchaseVerification: function(purchasableVirtualItem) {},
    onRestoreTransactionsStarted: function() {},
    onRestoreTransactionsFinished: function(success) {},
    onUnexpectedErrorInStore: function() {},
    onStoreControllerInitialized: function() {},
    // For Android only
    onMarketRefund: function(purchasableVirtualItem) {},
    onIabServiceStarted: function() {},
    onIabServiceStopped: function() {},

    // Profile
    /**
     * Called after the service has been initialized
     */
    onProfileInitialized: function() {},
    /**
     Called when the market page for the app is opened
     */
    onUserRatingEvent: function() {},

    /**
     Called when the login process to a provider has failed

     @param provider The provider on which the login has failed
     @param errorDescription a Description of the reason for failure
     */
    onLoginFailed: function(provider, errorDescription) {},

    /**
     Called when the login process finishes successfully

     @param userProfile The user's profile from the logged in provider
     */
    onLoginFinished: function(userProfile) {},

    /**
     Called when the login process to a provider has started

     @param provider The provider on where the login has started
     */
    onLoginStarted: function(provider) {},

    /**
     Called when the logout process from a provider has failed

     @param provider The provider on which the logout has failed
     @param errorDescription a Description of the reason for failure
     */
    onLogoutFailed: function(provider, errorDescription) {},

    /**
     Called when the logout process from a provider has finished

     @param provider The provider on which the logout has finished
     */
    onLogoutFinished: function(provider) {},

    /**
     Called when the logout process from a provider has started

     @param provider The provider on which the login has started
     */
    onLogoutStarted: function(provider) {},

    /**
     Called when the get contacts process from a provider has failed

     @param provider The provider on which the get contacts process has
     failed
     @param errorDescription a Description of the reason for failure
     */
    onGetContactsFailed: function(provider, errorDescription) {},

    /**
     Called when the get contacts process from a provider has finished

     @param provider The provider on which the get contacts process finished
     @param contactsDict an Array of contacts represented by CCUserProfile
     */
    onGetContactsFinished: function(provider, contactsDict) {},

    /**
     Called when the get contacts process from a provider has started

     @param provider The provider on which the get contacts process started
     */
    onGetContactsStarted: function(provider) {},

    /**
     Called when the get feed process from a provider has failed

     @param provider The provider on which the get feed process has
     failed
     @param errorDescription a Description of the reason for failure
     */
    onGetFeedFailed: function(provider, errorDescription) {},

    /**
     Called when the get feed process from a provider has finished

     @param provider The provider on which the get feed process finished
     @param feedList an Array of feed entries represented by __String
     */
    onGetFeedFinished: function(provider, feedList) {},

    /**
     Called when the get feed process from a provider has started

     @param provider The provider on which the get feed process started
     */
    onGetFeedStarted: function(provider) {},

    /**
     Called when a generic social action on a provider has failed

     @param provider The provider on which the social action has failed
     @param socialActionType The social action which failed
     @param errorDescription a Description of the reason for failure
     */
    onSocialActionFailedEvent: function(provider, socialActionType, errorDescription) {},

    /**
     Called when a generic social action on a provider has finished

     @param provider The provider on which the social action has finished
     @param socialActionType The social action which finished
     */
    onSocialActionFinishedEvent: function(provider, socialActionType) {},

    /**
     Called when a generic social action on a provider has started

     @param provider The provider on which the social action has started
     @param socialActionType The social action which started
     */
    onSocialActionStartedEvent: function(provider, socialActionType) {},

    /**
     Called the login process to a provider has been cancelled

     @param provider The provider on which the login has failed
     */
    onLoginCancelledEvent: function(provider) {},

    /**
     Called when a user profile from a provider has been retrieved

     @param userProfile The user's profile which was updated
     */
    onUserProfileUpdatedEvent: function(userProfile) {}
  });

  /**
   * Root definitions
   */
  Soomla.eventHandlers = [];
  Soomla.addEventHandler = Soomla.on = function (eventHandler) {
    Soomla.eventHandlers.push(eventHandler);
  };
  Soomla.removeEventHandler = Soomla.off = function (eventHandler) {
    var idx = Soomla.eventHandlers.indexOf(eventHandler);
    Soomla.eventHandlers.splice(idx, 1);
  };
  Soomla.ndkCallback = function (parameters) {
    parameters = JSON.parse(parameters);
    try {
      var methodName = parameters.method || "";

      if (methodName == "CCStoreEventHandler::onBillingNotSupported") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onBillingNotSupported) {
            eventHandler.onBillingNotSupported();
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onBillingSupported") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onBillingSupported) {
            eventHandler.onBillingSupported();
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onCurrencyBalanceChanged") {
        var virtualCurrency = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onCurrencyBalanceChanged) {
            eventHandler.onCurrencyBalanceChanged(virtualCurrency, parameters.balance, parameters.amountAdded);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onGoodBalanceChanged") {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodBalanceChanged) {
            eventHandler.onGoodBalanceChanged(virtualGood, parameters.balance, parameters.amountAdded);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onGoodEquipped") {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodEquipped) {
            eventHandler.onGoodEquipped(equippableVG);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onGoodUnEquipped") {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodUnEquipped) {
            eventHandler.onGoodUnEquipped(equippableVG);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onGoodUpgrade") {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        var upgradeVG = Soomla.storeInfo.getItemByItemId(parameters.vguItemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGoodUpgrade) {
            eventHandler.onGoodUpgrade(virtualGood, upgradeVG);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onItemPurchased") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onItemPurchased) {
            eventHandler.onItemPurchased(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onItemPurchaseStarted") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onItemPurchaseStarted) {
            eventHandler.onItemPurchaseStarted(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onMarketPurchaseCancelled") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchaseCancelled) {
            eventHandler.onMarketPurchaseCancelled(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onMarketPurchase") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        var token = parameters.token;
        var payload = parameters.payload;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchase) {
            eventHandler.onMarketPurchase(purchasableVirtualItem, token, payload);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onMarketPurchaseStarted") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchaseStarted) {
            eventHandler.onMarketPurchaseStarted(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onMarketItemsRefreshed") {
        var marketItemsDict = parameters.marketItems;
        var marketItems = [];
        _.forEach(marketItemsDict, function(marketItem) {

          // be careful confusing naming: snake_case VS camelCase
          var productId = marketItem.productId;
          var marketPrice = marketItem.marketPrice;
          var marketTitle = marketItem.marketTitle;
          var marketDescription = marketItem.marketDesc;

          var pvi = Soomla.storeInfo.getPurchasableItemWithProductId(productId);

          var purchaseWithMarket = pvi.purchaseType;
          var mi = purchaseWithMarket.marketItem;

          mi.marketPrice        = marketPrice;
          mi.marketTitle        = marketTitle;
          mi.marketDescription  = marketDescription;

          pvi.save();

          marketItems.push(pvi);
        });

        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketItemsRefreshed) {
            eventHandler.onMarketItemsRefreshed(marketItems);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onMarketItemsRefreshStarted") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketItemsRefreshStarted) {
            eventHandler.onMarketItemsRefreshStarted();
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onMarketPurchaseVerification") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketPurchaseVerification) {
            eventHandler.onMarketPurchaseVerification(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onRestoreTransactionsFinished") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onRestoreTransactionsFinished) {
            eventHandler.onRestoreTransactionsFinished(parameters.success);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onRestoreTransactionsStarted") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onRestoreTransactionsStarted) {
            eventHandler.onRestoreTransactionsStarted();
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onUnexpectedErrorInStore") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onUnexpectedErrorInStore) {
            eventHandler.onUnexpectedErrorInStore();
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onStoreControllerInitialized") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onStoreControllerInitialized) {
            eventHandler.onStoreControllerInitialized();
          }
        });
      }
      //  Android specific
      else if (methodName == "CCStoreEventHandler::onMarketRefund") {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onMarketRefund) {
            eventHandler.onMarketRefund(purchasableVirtualItem);
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onIabServiceStarted") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onIabServiceStarted) {
            eventHandler.onIabServiceStarted();
          }
        });
      }
      else if (methodName == "CCStoreEventHandler::onIabServiceStopped") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onIabServiceStopped) {
            eventHandler.onIabServiceStopped();
          }
        });
      }

      // Profile
      else if (methodName == "com.soomla.profile.events.ProfileInitializedEvent") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onProfileInitialized) {
            eventHandler.onProfileInitialized();
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.UserRatingEvent") {
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onUserRatingEvent) {
            eventHandler.onUserRatingEvent();
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.auth.LoginCancelledEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onLoginCancelledEvent) {
            eventHandler.onLoginCancelledEvent(provider);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.auth.LoginFailedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onLoginFailed) {
            eventHandler.onLoginFailed(provider, errorDescription);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.auth.LoginFinishedEvent") {
        var userProfile = parameters.userProfile;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onLoginFinished) {
            eventHandler.onLoginFinished(userProfile);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.auth.LoginStartedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onLoginStarted) {
            eventHandler.onLoginStarted(provider);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.auth.LogoutFailedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onLogoutFailed) {
            eventHandler.onLogoutFailed(provider, errorDescription);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.auth.LogoutFinishedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onLogoutFinished) {
            eventHandler.onLogoutFinished(provider);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.auth.LogoutStartedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onLogoutStarted) {
            eventHandler.onLogoutStarted(provider);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.GetContactsFailedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGetContactsFailed) {
            eventHandler.onGetContactsFailed(provider, errorDescription);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.GetContactsFinishedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var contacts = parameters.contacts;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGetContactsFinished) {
            eventHandler.onGetContactsFinished(provider, errorDescription);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.GetContactsStartedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGetContactsStarted) {
            eventHandler.onGetContactsStarted(provider);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.GetFeedFailedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGetFeedFailed) {
            eventHandler.onGetFeedFailed(provider, errorDescription);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.GetFeedFinishedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var feed = parameters.feed;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGetFeedFinished) {
            eventHandler.onGetFeedFinished(provider, feed);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.GetFeedStartedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onGetFeedStarted) {
            eventHandler.onGetFeedStarted(provider);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.SocialActionFailedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var socialActionType = parameters.socialActionType;
        var errorDescription = parameters.errorDescription;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onSocialActionFailedEvent) {
            eventHandler.onSocialActionFailedEvent(provider, socialActionType, errorDescription);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.SocialActionFinishedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var socialActionType = parameters.socialActionType;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onSocialActionFinishedEvent) {
            eventHandler.onSocialActionFinishedEvent(provider, socialActionType);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.social.SocialActionStartedEvent") {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var socialActionType = parameters.socialActionType;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onSocialActionStartedEvent) {
            eventHandler.onSocialActionStartedEvent(provider, socialActionType);
          }
        });
      }
      else if (methodName == "com.soomla.profile.events.UserProfileUpdatedEvent") {
        var userProfile = parameters.userProfile;
        _.forEach(Soomla.eventHandlers, function (eventHandler) {
          if (eventHandler.onUserProfileUpdatedEvent) {
            eventHandler.onUserProfileUpdatedEvent(userProfile);
          }
        });
      }
    } catch (e) {
      logError("ndkCallback: " + e.message);
    }
  };
  // put it into global context
  ndkCallback = function(params) {
    Soomla.ndkCallback.call(Soomla, params);
  };

  /**
   * SoomlaStore
   */
  var SoomlaStore = Soomla.SoomlaStore = declareClass("SoomlaStore", {
    SOOMLA_AND_PUB_KEY_DEFAULT: "YOUR GOOGLE PLAY PUBLIC KEY",
    SOOMLA_ONLY_ONCE_DEFAULT: "SET ONLY ONCE",
    init: function(storeAssets, storeParams) {

      // Redundancy checking. Most JS libraries don't do this. I hate it when they don't do this. Do this.
      var fields = ["customSecret", "androidPublicKey", "SSV", "testPurchases"];
      var wrongParams = _.omit(storeParams, fields);
      if (wrongParams.length > 0) {
        logDebug("WARNING!! Possible typo in member of storeParams: " + wrongParams);
      }

      storeParams = _.pick(storeParams, fields);
      storeParams.customSecret      = storeParams.customSecret || "";
      storeParams.androidPublicKey  = storeParams.androidPublicKey || "";
      storeParams.SSV  = storeParams.SSV === true || false;
      storeParams.testPurchases  = storeParams.testPurchases === true || false;

      if (storeParams.customSecret.length == 0) {
        logError("SOOMLA/COCOS2DX MISSING customSecret!!! Stopping here !!");
        return false;
      }

      if (storeParams.customSecret == this.SOOMLA_ONLY_ONCE_DEFAULT) {
        logError("SOOMLA/COCOS2DX You have to change customSecret!!! Stopping here !!");
        return false;
      }

      if (sys.os == "android" && storeParams.androidPublicKey.length == 0) {
        logError("SOOMLA/COCOS2DX MISSING publickKey !!! Stopping here !!");
        return false;
      }

      if (sys.os == "android" && storeParams.androidPublicKey == this.SOOMLA_AND_PUB_KEY_DEFAULT) {
        logError("SOOMLA/COCOS2DX You have to change android publicKey !!! Stopping here !!");
        return false;
      }

      callNative({
        method: "CCServiceManager::setCommonParams",
        params: {customSecret: storeParams.customSecret}
      });

      if (sys.os == "ios") {
        callNative({
          method: "CCSoomlaStore::setSSV",
          ssv: storeParams.SSV
        });
      }

      StoreInfo.createShared(storeAssets);

      callNative({
        method: "CCStoreService::init"
      });

      if (sys.os == "android") {
        callNative({
          method: "CCSoomlaStore::setAndroidPublicKey",
          androidPublicKey: storeParams.androidPublicKey
        });
        callNative({
          method: "CCSoomlaStore::setTestPurchases",
          testPurchases: storeParams.testPurchases
        });
      }

      return true;
    },
    buyMarketItem: function(productId, payload) {
      callNative({
        method: "CCSoomlaStore::buyMarketItem",
        productId: productId,
        payload: payload
      });
    },
    restoreTransactions: function() {
      callNative({
        method: "CCSoomlaStore::restoreTransactions"
      });
    },
    refreshInventory: function() {
      callNative({
        method: "CCSoomlaStore::refreshInventory"
      });
    },
    // TODO: For iOS only
    transactionsAlreadyRestored: function() {
      var retParams = callNative({
        method: "CCSoomlaStore::transactionsAlreadyRestored"
      });
      return retParams.return;
    },
    refreshMarketItemsDetails: function() {
      callNative({
        method: "CCSoomlaStore::refreshMarketItemsDetails"
      });
    },
    // TODO: For Android only
    startIabServiceInBg: function() {
      callNative({
        method: "CCSoomlaStore::startIabServiceInBg"
      });
    },
    // TODO: For Android only
    stopIabServiceInBg: function() {
      callNative({
        method: "CCSoomlaStore::stopIabServiceInBg"
      });
    }
  });

  SoomlaStore.createShared = function(storeAssets, storeParams) {
    var ret = new SoomlaStore();
    if (ret.init(storeAssets, storeParams)) {
      Soomla.soomlaStore = ret;
    } else {
      Soomla.soomlaStore = null;
    }
  };

  var StoreInventory = Soomla.StoreInventory = declareClass("StoreInventory", {
    buyItem: function(itemId, payload) {
      callNative({
        method: "CCStoreInventory::buyItem",
        payload: payload,
        itemId: itemId
      });
    },
    getItemBalance: function(itemId) {
      var retParams = callNative({
        method: "CCStoreInventory::getItemBalance",
        itemId: itemId
      });
      return retParams.return;
    },
    giveItem: function(itemId, amount) {
      callNative({
        method: "CCStoreInventory::giveItem",
        itemId: itemId,
        amount: amount
      });
    },
    takeItem: function(itemId, amount) {
      callNative({
        method: "CCStoreInventory::takeItem",
        itemId: itemId,
        amount: amount
      });
    },
    equipVirtualGood: function(itemId) {
      callNative({
        method: "CCStoreInventory::equipVirtualGood",
        itemId: itemId
      });
    },
    unEquipVirtualGood: function(itemId) {
      callNative({
        method: "CCStoreInventory::unEquipVirtualGood",
        itemId: itemId
      });
    },
    isVirtualGoodEquipped: function(itemId) {
      var retParams = callNative({
        method: "CCStoreInventory::isVirtualGoodEquipped",
        itemId: itemId
      });
      return retParams.return;
    },
    getGoodUpgradeLevel: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInventory::getGoodUpgradeLevel",
        goodItemId: goodItemId
      });
      return retParams.return;
    },
    getGoodCurrentUpgrade: function(goodItemId) {
      var retParams = callNative({
        method: "CCStoreInventory::getGoodCurrentUpgrade",
        goodItemId: goodItemId
      });
      return retParams.return;
    },
    upgradeGood: function(goodItemId) {
      callNative({
        method: "CCStoreInventory::upgradeGood",
        goodItemId: goodItemId
      });
    },
    removeGoodUpgrades: function(goodItemId) {
      callNative({
        method: "CCStoreInventory::removeGoodUpgrades",
        goodItemId: goodItemId
      });
    },
    nonConsumableItemExists: function(nonConsItemId) {
      var retParams = callNative({
        method: "CCStoreInventory::nonConsumableItemExists",
        nonConsItemId: nonConsItemId
      });
      return retParams.return;
    },
    addNonConsumableItem: function(nonConsItemId) {
      callNative({
        method: "CCStoreInventory::addNonConsumableItem",
        nonConsItemId: nonConsItemId
      });
    },
    removeNonConsumableItem: function(nonConsItemId) {
      callNative({
        method: "CCStoreInventory::removeNonConsumableItem",
        nonConsItemId: nonConsItemId
      });
    }
  });

  Soomla.storeInventory = StoreInventory.create();

  function SoomlaException(code, message) {
    this.name = "SoomlaException";
    this.code = code || 0;
    this.message = (message || "");
  }
  SoomlaException.prototype = Error.prototype;
  SoomlaException.CODE = {
    ITEM_NOT_FOUND: -1,
    INSUFFICIENT_FUNDS: -2,
    NOT_ENOUGH_GOODS: -3,
    OTHER: -4
  };

  /**
   * SoomlaProfile
   */
  var SoomlaProfile = Soomla.SoomlaProfile = declareClass("SoomlaProfile", {
    inited: false,
    init: function() {
      this.inited = true;
      return true;
    },
    login: function(provider, reward) {
      callNative({
        method: "CCSoomlaProfile::login",
        provider: provider.key,
        reward: reward
      });
    },
    logout: function(provider) {
      callNative({
        method: "CCSoomlaProfile::logout",
        provider: provider.key
      });
    },
    getStoredUserProfile: function(provider) {
      var retParams = callNative({
        method: "CCSoomlaProfile::getStoredUserProfile",
        provider: provider.key
      });
      return retParams.return;
    },
    updateStatus: function(provider, status, reward) {
      callNative({
        method: "CCSoomlaProfile::updateStatus",
        provider: provider.key,
        status: status,
        reward: reward
      });
    },
    updateStory: function(provider, message, name, caption, description, link, picture, reward) {
      callNative({
        method: "CCSoomlaProfile::updateStory",
        provider: provider.key,
        message: message,
        name: name,
        caption: caption,
        description: description,
        link: link,
        picture: picture,
        reward: reward
      });
    },
    uploadImage: function(provider, message, filePath, reward) {
      callNative({
        method: "CCSoomlaProfile::uploadImage",
        provider: provider.key,
        message: message,
        filePath: filePath,
        reward: reward
      });
    },
    getContacts: function(provider, filePath, reward) {
      callNative({
        method: "CCSoomlaProfile::getContacts",
        provider: provider.key,
        reward: reward
      });
    },
    getFeed: function(provider, reward) {
      callNative({
        method: "CCSoomlaProfile::getFeed",
        provider: provider.key,
        reward: reward
      });
    },
    isLoggedIn: function(provider) {
      var retParams = callNative({
        method: "CCSoomlaProfile::isLoggedIn",
        provider: provider.key
      });
      return retParams.return;
    },
    like: function(provider, pageName, reward) {
      callNative({
        method: "CCSoomlaProfile::like",
        provider: provider.key,
        pageName: pageName,
        reward: reward
      });
    },
    openAppRatingPage: function() {
      callNative({
        method: "CCSoomlaProfile::openAppRatingPage"
      });
    }
  });

  SoomlaProfile.createShared = function() {
    var ret = new SoomlaProfile();
    if (ret.init()) {
      Soomla.soomlaProfile = ret;
    } else {
      Soomla.soomlaProfile = null;
    }
  };

  var callNative = function (params) {
    var jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params));
    var result = JSON.parse(jsonString);

    if (!result.success) {
      throw new SoomlaException(result.code, result.info);
    }
    return result.result;
  };

  var logDebug = Soomla.logDebug = function (output) {
    if (Soomla.DEBUG) {
      cc.log("DEBUG: " + output);
    }
  };

  var logError = Soomla.logError = function (output) {
    cc.log("ERROR: " + output);
  };

  var dumpError = Soomla.dumpError = function (e) {
    return e + " : " + JSON.stringify(e);
  };

  return Soomla
};
