
var PrevSoomla = Soomla;
Soomla = new function () {

  var Soomla = _.extend(PrevSoomla, {Models: {}}); // merge with binding instance

  Soomla.DEBUG = false;

  var declareClass = Soomla.declareClass = function (ClassName, fields, parentClass) {
    var Clazz = function () {
      return _.extend(parentClass ? parentClass() : {}, fields ? fields : {}, {
        className: ClassName
      });
    };
    Clazz.create = function (values) {
      var instance = _.defaults(values ? _.omit(values, "className") : {}, Clazz());
      if (typeof instance.onCreate == 'function') {
          instance.onCreate();
      }
      return instance;
    };

    return Clazz;
  };

  //------ Core ------//
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
    itemId: null,
    equals: function equals(obj) {
      // If parameter is null return false.
      if (obj == null) {
        return false;
      }

      if (obj.className != this.className) {
        return false;
      }

      if (obj.itemId != this.itemId) {
        return false;
      }

      return true;
    }
  }, Domain);


  /**
   * Recurrence
   */
  var Recurrence = Soomla.Models.Recurrence = {
    EVERY_MONTH: 0,
    EVERY_WEEK: 1,
    EVERY_DAY: 2,
    EVERY_HOUR: 3,
    NONE: 4
  };

  /**
   * CoreConsts
   */
  var CoreConsts = Soomla.Models.CoreConsts = {
    EVENT_REWARD_GIVEN: "com.soomla.events.RewardGivenEvent",
    EVENT_REWARD_TAKEN: "com.soomla.events.RewardTakenEvent",
    EVENT_CUSTOM: "com.soomla.events.CustomEvent"
  };

  /**
   * DateTimeRange
   */
  var DateTimeRange = Soomla.Models.DateTimeRange = declareClass("DateTimeRange", {
    schedTimeRangeStart: null,
    schedTimeRangeEnd: null
  });

  /**
   * Schedule
   */
  var Schedule = Soomla.Models.Schedule = declareClass("Schedule", {
    schedRecurrence: null,
    schedTimeRanges: null,
    schedApprovals: null,
    approve: function approve(activationTimes) {
      var now = Date.now();

      if (this.schedApprovals && this.schedApprovals < 1 && (!this.schedTimeRanges || this.schedTimeRanges.length == 0)) {
        logDebug("There's no activation limit and no TimeRanges. APPROVED!");
        return true;
      }

      if (this.schedApprovals && this.schedApprovals > 0 && activationTimes >= this.schedApprovals) {
        logDebug("Activation limit exceeded.");
        return false;
      }

      if ((!this.schedTimeRanges || this.schedTimeRanges.length == 0)) {
        logDebug("We have an activation limit that was not reached. Also, we don't have any time ranges. APPROVED!");
        return true;
      }


      // NOTE: From this point on ... we know that we didn't reach the activation limit AND we have TimeRanges.
      //		 We'll just make sure the time ranges and the Recurrence copmlies.

      var found = _.find(this.schedTimeRanges, function(dateTimeRange) {
        if (now < dateTimeRange.schedTimeRangeStart && now > dateTimeRange.schedTimeRangeEnd) {
          logDebug("We are just in one of the time spans, it can't get any better then that. APPROVED!");
          return true;
        }
      });

      if (found) {
        return true;
      }

      // we don't need to continue if RequiredRecurrence is NONE
      if (this.schedRecurrence == Recurrence.NONE) {
        return false;
      }

      var _this = this;
      return _.find(this.schedTimeRanges, function(dateTimeRange) {
        if (now.getMinutes() >= dateTimeRange.schedTimeRangeStart.getMinutes()
          && now.getMinutes() <= dateTimeRange.schedTimeRangeEnd.getMinutes()) {

          logDebug("Now is in one of the time ranges' minutes span.");

          if (_this.schedRecurrence == Recurrence.EVERY_HOUR) {
            logDebug(TAG, "It's a EVERY_HOUR recurrence. APPROVED!");
            return true;
          }

          if (now.getHours() >= dateTimeRange.schedTimeRangeStart.getHours()
            && now.getHours() <= dateTimeRange.schedTimeRangeEnd.getHours()) {

            logDebug("Now is in one of the time ranges' hours span.");

            if (_this.schedRecurrence == Recurrence.EVERY_DAY) {
              logDebug("It's a EVERY_DAY recurrence. APPROVED!");
              return true;
            }

            if (now.getDay() >= dateTimeRange.schedTimeRangeStart.getDay()
              && now.getDay() <= dateTimeRange.schedTimeRangeEnd.getDay()) {

              logDebug("Now is in one of the time ranges' day-of-week span.");

              if (_this.schedRecurrence == Recurrence.EVERY_WEEK) {
                logDebug("It's a EVERY_WEEK recurrence. APPROVED!");
                return true;
              }

              if (now.getDate() >= dateTimeRange.schedTimeRangeStart.getDate()
                && now.getDate() <= dateTimeRange.schedTimeRangeEnd.getDate()) {

                logDebug("Now is in one of the time ranges' days span.");

                if (_this.schedRecurrence == Recurrence.EVERY_MONTH) {
                  logDebug("It's a EVERY_MONTH recurrence. APPROVED!");
                  return true;
                }
              }
            }
          }
        }
      }) || false;
    }
  });
  Schedule.createAnyTimeOnce = function createAnyTimeOnce() {
    return Schedule.create({
      schedRecurrence: Recurrence.NONE,
      schedApprovals: 1
    });
  };
  Schedule.createAnyTimeLimited = function createAnyTimeLimited(activationLimit) {
    return Schedule.create({
      schedRecurrence: Recurrence.NONE,
      schedApprovals: activationLimit
    });
  };
  Schedule.createAnyTimeUnLimited = function createAnyTimeUnLimited() {
    return Schedule.create({
      schedRecurrence: Recurrence.NONE,
      schedApprovals: 0
    });
  };

  //noinspection JSUnusedGlobalSymbols
  /**
   * Reward
   */
  var Reward = Soomla.Models.Reward = declareClass("Reward", {
    schedule: null,
    take: function take() {
      if (!Soomla.rewardStorage.isRewardGiven(this)) {
        logDebug("Reward not given. id: " + id);
        return false;
      }

      if (this.takeInner()) {
        Soomla.rewardStorage.setRewardStatus(this, false);
        return true;
      }

      return false;
    },
    give: function give() {
      if (!this.schedule.approve(Soomla.rewardStorage.getTimesGiven(this))) {
        logDebug("(Give) Reward is not approved by Schedule. id: " + this.itemId);
        return false;
      }

      if (this.giveInner()) {
        Soomla.rewardStorage.setRewardStatus(this, true);
        return true;
      }

      return false;
    },
    isOwned: function isOwned() {
      return Soomla.rewardStorage.isRewardGiven(this);
    },
    takeInner: function takeInner() {
      return new Error("takeInner is not implemented");
    },
    giveInner: function giveInner() {
      return new Error("giveInner is not implemented");
    },
    onCreate: function () {
      Reward.addReward(this);
    }
  }, SoomlaEntity);

  Reward.rewardsMap = {};

  Reward.getReward = function(id) {
    if (id in Soomla.Models.Reward.rewardsMap) {
      return Soomla.Models.Reward.rewardsMap[id];
    }

    return null;
  };

  Reward.addReward = function(reward) {
    Soomla.Models.Reward.rewardsMap[reward.itemId] = reward;
  };

  /**
   * AggregateReward
   */
  var AggregateReward = Soomla.Models.AggregateReward = declareClass("AggregateReward", {
    rewards: null
  }, Reward);

  /**
   * BadgeReward
   */
  var BadgeReward = Soomla.Models.BadgeReward = declareClass("BadgeReward", {
    iconUrl: null,
    takeInner: function takeInner() {
      // nothing to do here... the parent Reward takes in storage
      return true;
    },
    giveInner: function giveInner() {
      // nothing to do here... the parent Reward gives in storage
      return true;
    }
  }, Reward);

  /**
   * RandomReward
   */
  var RandomReward = Soomla.Models.RandomReward = declareClass("RandomReward", {
    lastGivenReward: null,
    takeInner: function takeInner() {
      // for now is able to take only last given
      if (this.lastGivenReward == null) {
        return false;
      }

      var taken = this.lastGivenReward.take();
      this.lastGivenReward = null;

      return taken;
    },
    giveInner: function giveInner() {
      var randomReward = _.sample(this.rewards);
      randomReward.give();
      this.lastGivenReward = randomReward;

      return true;
    }
  }, AggregateReward);

  /**
   * SequenceReward
   */
  var SequenceReward = Soomla.Models.SequenceReward = declareClass("SequenceReward", {
    takeInner: function takeInner() {
      var idx = Soomla.rewardStorage.getLastSeqIdxGiven(this);
      if (idx <= 0) {
        return false; // all rewards in the sequence were taken
      }
      Soomla.rewardStorage.setLastSeqIdxGiven(this, --idx);
      return true;
    },
    giveInner: function giveInner() {
      var idx = Soomla.rewardStorage.getLastSeqIdxGiven(this);
      if (idx >= this.rewards.length) {
        return false; // all rewards in the sequence were given
      }
      Soomla.rewardStorage.setLastSeqIdxGiven(this, ++idx);
      return true;
    },
    getLastGivenReward: function getLastGivenReward() {
      var idx = Soomla.rewardStorage.getLastSeqIdxGiven(this);
      if (idx < 0) {
        return null;
      }
      return this.rewards[idx];
    },
    hasMoreToGive: function hasMoreToGive() {
      return Soomla.rewardStorage.getLastSeqIdxGiven(this) < this.rewards.length;
    },
    forceNextRewardToGive: function forceNextRewardToGive(reward) {
      for (var i = 0; i < this.rewards.length; i++) {
        if (reward.equals(this.reward[i])) {
          Soomla.rewardStorage.setLastSeqIdxGiven(this, i - 1);
          return true;
        }
      }
      return false;
    }
  }, AggregateReward);


  //------ Store ------//
  /**
   * VirtualItem
   */
  var VirtualItem = Soomla.Models.VirtualItem = declareClass("VirtualItem", {
    save: function () {
      Soomla.storeInfo.saveItem(this);
    }
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
    marketPrice: 0,
    marketTitle: null,
    marketDesc: null,
    marketCurrencyCode: null,
    marketPriceMicros: 0
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
   * StoreConsts
   */
  var StoreConsts = Soomla.Models.StoreConsts = {
    EVENT_BILLING_NOT_SUPPORTED: "CCStoreEventHandler::onBillingNotSupported",
    EVENT_BILLING_SUPPORTED: "CCStoreEventHandler::onBillingSupported",
    EVENT_CURRENCY_BALANCE_CHANGED: "CCStoreEventHandler::onCurrencyBalanceChanged",
    EVENT_GOOD_BALANCE_CHANGED: "CCStoreEventHandler::onGoodBalanceChanged",
    EVENT_GOOD_EQUIPPED: "CCStoreEventHandler::onGoodEquipped",
    EVENT_GOOD_UNEQUIPPED: "CCStoreEventHandler::onGoodUnEquipped",
    EVENT_GOOD_UPGRADE: "CCStoreEventHandler::onGoodUpgrade",
    EVENT_ITEM_PURCHASED: "CCStoreEventHandler::onItemPurchased",
    EVENT_ITEM_PURCHASE_STARTED: "CCStoreEventHandler::onItemPurchaseStarted",
    EVENT_MARKET_PURCHASE_CANCELED: "CCStoreEventHandler::onMarketPurchaseCancelled",
    EVENT_MARKET_PURCHASE: "CCStoreEventHandler::onMarketPurchase",
    EVENT_MARKET_PURCHASE_STARTED: "CCStoreEventHandler::onMarketPurchaseStarted",
    EVENT_MARKET_ITEMS_REFRESHED: "CCStoreEventHandler::onMarketItemsRefreshed",
    EVENT_MARKET_ITEMS_REFRESH_STARTED: "CCStoreEventHandler::onMarketItemsRefreshStarted",
    EVENT_MARKET_ITEMS_REFRESH_FAILED: "CCStoreEventHandler::onMarketItemsRefreshFailed",
    EVENT_MARKET_PURCHASE_VERIFICATION: "CCStoreEventHandler::onMarketPurchaseVerification",
    EVENT_RESTORE_TRANSACTION_FINISHED: "CCStoreEventHandler::onRestoreTransactionsFinished",
    EVENT_RESTORE_TRANSACTION_STARTED: "CCStoreEventHandler::onRestoreTransactionsStarted",
    EVENT_UNEXPECTED_ERROR_IN_STORE: "CCStoreEventHandler::onUnexpectedErrorInStore",
    EVENT_SOOMLA_STORE_INITIALIZED: "CCStoreEventHandler::onSoomlaStoreInitialized",
    EVENT_MARKET_REFUND: "CCStoreEventHandler::onMarketRefund",
    EVENT_IAB_SERVICE_STARTED: "CCStoreEventHandler::onIabServiceStarted",
    EVENT_IAB_SERVICE_STOPPED: "CCStoreEventHandler::onIabServiceStopped"
  };

  /**
   * PurchasableVirtualItem
   */
  var PurchasableVirtualItem = Soomla.Models.PurchasableVirtualItem = declareClass("PurchasableVirtualItem", {
    purchasableItem: null
  }, VirtualItem);

  /**
   * VirtualCurrency
   */
  var VirtualCurrency = Soomla.Models.VirtualCurrency = declareClass("VirtualCurrency", {
  }, VirtualItem);

  /**
   * VirtualCurrencyPack
   */
  var VirtualCurrencyPack = Soomla.Models.VirtualCurrencyPack = declareClass("VirtualCurrencyPack", {
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

  /**
   * VirtualItemReward
   */
  var VirtualItemReward = Soomla.Models.VirtualItemReward = declareClass("VirtualItemReward", {
    amount: null,
    associatedItemId : null,
    takeInner: function takeInner() {
      Soomla.storeInventory.takeItem(this.associatedItemId, this.amount);
      return true;
    },
    giveInner: function giveInner() {
      Soomla.storeInventory.giveItem(this.associatedItemId, this.amount);
    }
  }, Reward);


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
    GOOGLE: {id: 2, key: 'google'},
    TWITTER: {id: 5, key: 'twitter'}
  };

  Provider.findById = function(id) {
    return _.find(Soomla.Models.Provider, function(provider) {
      return !_.isFunction(provider) && provider.id == id;
    })
  };
  Provider.findByKey = function(key) {
    return _.find(Soomla.Models.Provider, function(provider) {
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

  /**
   * ProfileConsts
   */
  var ProfileConsts = Soomla.Models.ProfileConsts = {
    EVENT_PROFILE_INITIALIZED: "com.soomla.profile.events.ProfileInitializedEvent",
    EVENT_USER_RATING: "com.soomla.profile.events.UserRatingEvent",
    EVENT_LOGIN_CANCELLED: "com.soomla.profile.events.auth.LoginCancelledEvent",
    EVENT_LOGIN_FAILED: "com.soomla.profile.events.auth.LoginFailedEvent",
    EVENT_LOGIN_FINISHED: "com.soomla.profile.events.auth.LoginFinishedEvent",
    EVENT_LOGIN_STARTED: "com.soomla.profile.events.auth.LoginStartedEvent",
    EVENT_LOGOUT_FAILED: "com.soomla.profile.events.auth.LogoutFailedEvent",
    EVENT_LOGOUT_FINISHED: "com.soomla.profile.events.auth.LogoutFinishedEvent",
    EVENT_LOGOUT_STARTED: "com.soomla.profile.events.auth.LogoutStartedEvent",
    EVENT_GET_CONTACTS_FAILED: "com.soomla.profile.events.social.GetContactsFailedEvent",
    EVENT_GET_CONTACTS_FINISHED: "com.soomla.profile.events.social.GetContactsFinishedEvent",
    EVENT_GET_CONTACTS_STARTED: "com.soomla.profile.events.social.GetContactsStartedEvent",
    EVENT_GET_FEED_FAILED: "com.soomla.profile.events.social.GetFeedFailedEvent",
    EVENT_GET_FEED_FINISHED: "com.soomla.profile.events.social.GetFeedFinishedEvent",
    EVENT_GET_FEED_STARTED: "com.soomla.profile.events.social.GetFeedStartedEvent",
    EVENT_SOCIAL_ACTION_FAILED: "com.soomla.profile.events.social.SocialActionFailedEvent",
    EVENT_SOCIAL_ACTION_FINISHED: "com.soomla.profile.events.social.SocialActionFinishedEvent",
    EVENT_SOCIAL_ACTION_STARTED: "com.soomla.profile.events.social.SocialActionStartedEvent",
    EVENT_USER_PROFILE_UPDATED: "com.soomla.profile.events.UserProfileUpdatedEvent"
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

  //------ Highway ------//

  /**
   * HighwayConsts
   */
  var HighwayConsts = Soomla.Models.HighwayConsts = {
    INTERNAL_EVENT_ON_STATE_CONFLICT: "CCHighwayEventDispatcher::onStateConflict",
    EVENT_SOOMLA_SYNC_INITIALIZED: "com.soomla.sync.events.SoomlaSyncInitializedEvent",
    EVENT_META_SYNC_STARTED: "com.soomla.sync.events.MetaDataSyncStartedEvent",
    EVENT_META_SYNC_FINISHED: "com.soomla.sync.events.MetaDataSyncFinishedEvent",
    EVENT_META_SYNC_FAILED: "com.soomla.sync.events.MetaDataSyncFailedEvent",
    EVENT_STATE_SYNC_STARTED: "com.soomla.sync.events.StateSyncStartedEvent",
    EVENT_STATE_SYNC_FINISHED: "com.soomla.sync.events.StateSyncFinishedEvent",
    EVENT_STATE_SYNC_FAILED: "com.soomla.sync.events.StateSyncFailedEvent",
    EVENT_STATE_RESET_STARTED: "com.soomla.sync.events.StateResetStartedEvent",
    EVENT_STATE_RESET_FINISHED: "com.soomla.sync.events.StateResetFinishedEvent",
    EVENT_STATE_RESET_FAILED: "com.soomla.sync.events.StateResetFailedEvent",
    EVENT_SOOMLA_GIFTING_INITIALIZED: "com.soomla.gifting.events.SoomlaGiftingInitializedEvent",
    EVENT_GIFTS_RETRIEVE_STARTED: "com.soomla.gifting.events.GiftsRetrieveStartedEvent",
    EVENT_GIFTS_RETRIEVE_FINISHED: "com.soomla.gifting.events.GiftsRetrieveFinishedEvent",
    EVENT_GIFTS_RETRIEVE_FAILED: "com.soomla.gifting.events.GiftsRetrieveFailedEvent",
    EVENT_GIFT_SEND_STARTED: "com.soomla.gifting.events.GiftSendStartedEvent",
    EVENT_GIFT_SEND_FINISHED: "com.soomla.gifting.events.GiftSendFinishedEvent",
    EVENT_GIFT_SEND_FAILED: "com.soomla.gifting.events.GiftSendFailedEvent",
    EVENT_GIFT_HAND_OUT_SUCCESS: "com.soomla.gifting.events.GiftHandOutSuccessEvent",
    EVENT_GIFT_HAND_OUT_FAILED: "com.soomla.gifting.events.GiftHandOutFailedEvent",
    EVENT_QUERY_FRIENDS_STATES_STARTED: "com.soomla.query.events.QueryFriendsStatesStartedEvent",
    EVENT_QUERY_FRIENDS_STATES_FINISHED: "com.soomla.query.events.QueryFriendsStatesFinishedEvent",
    EVENT_QUERY_FRIENDS_STATES_FAILED: "com.soomla.query.events.QueryFriendsStatesFailedEvent",
    EVENT_SOOMLA_DLC_INITIALIZED: "com.soomla.dlc.events.SoomlaDLCInitializedEvent",
    EVENT_DLC_PACKAGE_STATUS_UPDATED: "com.soomla.dlc.events.DLCPackagesStatusUpdateEvent",
    EVENT_DLC_PACKAGE_SYNC_STARTED: "com.soomla.dlc.events.DLCPackageSyncStartedEvent",
    EVENT_DLC_PACKAGE_SYNC_FINISHED: "com.soomla.dlc.events.DLCPackageSyncFinishedEvent",
    EVENT_DLC_PACKAGE_SYNC_FAILED: "com.soomla.dlc.events.DLCPackageSyncFailedEvent"
  };

  var Gift = Soomla.Models.Gift = declareClass("Gift", {
    giftId : null,
    fromUid : null,
    toProvider : null,
    toProfileId : null,
    payload : null
  }, Domain);

  var GiftPayload = Soomla.Models.GiftPayload = declareClass("GiftPayload", {
    associatedItemId : null,
    itemsAmount : null
  }, Domain);

  var FriendState = Soomla.Models.FriendState = declareClass("FriendState", {
    profileId : null,
    records : null,
    lastCompletedWorlds : null
  }, Domain);

  var MetaDataSyncError = Soomla.Models.MetaDataSyncError = {
    METADATA_GENERAL_ERROR: 0,
    METADATA_SERVER_ERROR: 1,
    METADATA_UPDATE_MODEL_ERROR: 2
  };

  var StateSyncError = Soomla.Models.StateSyncError = {
    STATE_GENERAL_ERROR: 0,
    STATE_SERVER_ERROR: 1,
    STATE_UPDATE_STATE_ERROR: 2
  };

  var DLCSyncError = Soomla.Models.DLCSyncError = {
    DLC_GENERAL_ERROR: 0,
    DLC_DOWNLOAD_ERROR: 1,
    DLC_DELETE_ERROR: 2,
    DLC_SERVER_ERROR: 3
  };

  // ------- Core -------- //
  /**
   * CoreBridge
   */
  var CoreBridge = Soomla.CoreBridge = declareClass("CoreBridge", {
	SOOMLA_ONLY_ONCE_DEFAULT: "SET ONLY ONCE",
    init: function init(soomlaSecret) {

      if (soomlaSecret.length == 0) {
        logError("SOOMLA/COCOS2DX MISSING customSecret!!! Stopping here !!");
        return false;
      }

	  callNative({
		method: "CCSoomla::initialize",
		soomlaSecret: soomlaSecret
	  });

      return true;
    },
    getTimesGiven: function getTimesGiven(reward) {
      var result = callNative({
        method: "CCNativeRewardStorage::getTimesGiven",
        reward: reward.itemId
      });
      return result.return;
    },
    setRewardStatus: function setRewardStatus(reward, give, notify) {
      callNative({
        method: "CCNativeRewardStorage::setRewardStatus",
        reward: reward.itemId,
        give: give,
        notify: notify
      });
    },
    getLastSeqIdxGiven: function getLastSeqIdxGiven(sequenceReward) {
      var result = callNative({
        method: "CCNativeRewardStorage::getLastSeqIdxGiven",
        reward: sequenceReward.itemId
      });
      return result.return;
    },
    setLastSeqIdxGiven: function setLastSeqIdxGiven(sequenceReward, idx) {
      callNative({
        method: "CCNativeRewardStorage::setLastSeqIdxGiven",
        reward: sequenceReward.itemId,
        idx: idx
      });
    },

    kvStorageGetValue: function kvStorageGetValue(key) {
      var result = callNative({
        method: "CCNativeKeyValueStorage::getValue",
        key: key
      });
      return result.return;
    },
    kvStorageSetValue: function kvStorageSetValue(key, val) {
      callNative({
        method: "CCNativeKeyValueStorage::setValue",
        key: key,
        val: val
      });
    },
    kvStorageDeleteKeyValue: function kvStorageDeleteKeyValue(key) {
      callNative({
        method: "CCNativeKeyValueStorage::deleteKeyValue",
        key: key
      });
    },
    kvStoragePurge: function kvStoragePurge() {
      callNative({
        method: "CCNativeKeyValueStorage::purge"
      });
    }
  });
  CoreBridge.createShared = function(customSecret) {
    var ret = new CoreBridge();
    if (ret.init(customSecret)) {
      Soomla.coreBridge = ret;
    } else {
      Soomla.coreBridge = null;
    }
  };

  /**
   * KeyValueStorage
   */
  var KeyValueStorage = Soomla.KeyValueStorage = declareClass("KeyValueStorage", {
    getValue: function getValue(key) {
      Soomla.coreBridge.kvStorageGetValue(key);
    },
    setValue: function setValue(key, val) {
      Soomla.coreBridge.kvStorageSetValue(key, val);
    },
    deleteKeyValue: function deleteKeyValue(key) {
      Soomla.coreBridge.kvStorageDeleteKeyValue(key);
    },
    purge: function purge() {
      Soomla.coreBridge.kvStoragePurge();
    }
  });
  Soomla.keyValueStorage = KeyValueStorage.create();

  /**
   * RewardStorage
   */
  var RewardStorage = Soomla.RewardStorage = declareClass("RewardStorage", {
    setRewardStatus: function setRewardStatus(reward, give, notify) {
      notify = notify || notify == undefined;
      Soomla.coreBridge.setRewardStatus(reward, give, notify);
    },
    getTimesGiven: function getTimesGiven(reward) {
      return Soomla.coreBridge.getTimesGiven(reward);
    },
    isRewardGiven: function isRewardGiven(reward) {
      return this.getTimesGiven(reward) > 0;
    },
    getLastSeqIdxGiven: function getLastSeqIdxGiven(sequenceReward) {
      return Soomla.coreBridge.getLastSeqIdxGiven(sequenceReward);
    },
    setLastSeqIdxGiven: function setLastSeqIdxGiven(sequenceReward, idx) {
      return Soomla.coreBridge.setLastSeqIdxGiven(sequenceReward, idx);
    }
  });
  Soomla.rewardStorage = RewardStorage.create();

  // ------- Store -------- //
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
    getVirtualCategories: function() {
      var retParams = callNative({
        method: "CCStoreInfo::getVirtualCategories"
      });
      return extractCollection(retParams);
    },
    saveItem: function(virtualItem) {
      callNative({
        method: "CCStoreInfo::saveItem",
        virtualItem: virtualItem
      });
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
    version: 1
  });

// ------- Highway -------- //
  /**
   * Cocos2dXSoomlaHighway
   */
  var Cocos2dXSoomlaHighway = Soomla.Cocos2dXSoomlaHighway = declareClass("Cocos2dXSoomlaHighway", {
    init: function init(gameKey, envKey, highwayUrl, servicesUrl) {
      var result = callNative({
        method: "CCSoomlaHighway::init",
        gameKey: gameKey,
        envKey: envKey,
        highwayUrl: highwayUrl,
        servicesUrl: servicesUrl
      });
      return result.return;
    }
  });
  Cocos2dXSoomlaHighway.createShared = function(gameKey, envKey, highwayUrl, servicesUrl) {
    var ret = new Cocos2dXSoomlaHighway();
    if (ret.init(gameKey, envKey, highwayUrl, servicesUrl)) {
      Soomla.cocos2dXSoomlaHighway = ret;
    } else {
      Soomla.cocos2dXSoomlaHighway = null;
    }
  };

  /**
   * SoomlaSync
   */
  var SoomlaSync = Soomla.SoomlaSync = declareClass("SoomlaSync", {
    init: function init(metaDataSync, stateSync) {
      var result = callNative({
        method: "CCSoomlaSync::init",
        metaDataSync: metaDataSync,
        stateSync: stateSync
      });
      return result.return;
    },
    resetState : function() {
      var result = callNative({
        method: "CCSoomlaSync::resetState"
      });
      return result.return;
    },
    stateConflictResolver : function(remoteState, currentState, stateDiff) {
      return remoteState;
    },
    resolveStateConflict : function(remoteState, currentState, stateDiff) {
      var resolvedState = this.stateConflictResolver(remoteState, currentState, stateDiff);

      var conflictResolveStrategy = 2;
      if (_.isEqual(resolvedState, remoteState)) {
        conflictResolveStrategy = 0;
      }
      else if (_.isEqual(resolvedState, currentState)) {
        conflictResolveStrategy = 1;
      }

      var result = callNative({
        method: "CCSoomlaSync::resolveConflictCallback",
        conflictResolveStrategy: conflictResolveStrategy,
        resolvedState: resolvedState
      });
      return result.return;
    }
  });
  SoomlaSync.createShared = function(metaDataSync, stateSync) {
    var ret = new SoomlaSync();
    if (ret.init(metaDataSync, stateSync)) {
      Soomla.soomlaSync = ret;
    } else {
      Soomla.soomlaSync = null;
    }
  };

  /**
   * SoomlaGifting
   */
  var SoomlaGifting = Soomla.SoomlaGifting = declareClass("SoomlaGifting", {
    init: function init() {
      var result = callNative({
        method: "CCSoomlaGifting::init"
      });
      return result.return;
    },
    sendGift: function(toProvider, toProfileId, itemId, amount, deductFromUser) {
      if (_.isUndefined(deductFromUser)) {
        deductFromUser = false;
      }

      var result = callNative({
        method: "CCSoomlaGifting::sendGift",
        toProvider: toProvider,
        toProfileId: toProfileId,
        itemId: itemId,
        amount: amount,
        deductFromUser: deductFromUser
      });

      if (result.return) {
        return result.willStart;
      }

      return false;
    }
  });
  SoomlaGifting.createShared = function() {
    var ret = new SoomlaGifting();
    if (ret.init()) {
      Soomla.soomlaGifting = ret;
    } else {
      Soomla.soomlaGifting = null;
    }
  };

  /**
   * SoomlaQuery
   */
  var SoomlaQuery = Soomla.SoomlaQuery = {
    queryFriendsStates: function(providerId, friendsProfileIds) {
      var result = callNative({
        method: "CCSoomlaQuery::queryFriendsStates",
        providerId: providerId,
        friendsList: friendsProfileIds
      });

      if (result.return) {
        return result.willStart;
      }

      return false;
    }
  };

  /**
   * SoomlaDLC
   */
  var SoomlaDLC = Soomla.SoomlaDLC = declareClass("SoomlaDLC", {
    init: function init() {
      var result = callNative({
        method: "CCSoomlaDLC::init"
      });
      return true;
    },
    checkPackageStatus: function(packageId) {

      callNative({
        method: "CCSoomlaDLC::checkPackageStatus",
        packageId: packageId
      });
    },
    checkSyncedPackagesStatus: function() {

      callNative({
        method: "CCSoomlaDLC::checkSyncedPackagesStatus"
      });
    },
    startSync: function(packageId) {
      var result = callNative({
        method: "CCSoomlaDLC::startSync",
        packageId: packageId
      });

      if (result.return) {
        return result.willStart;
      }

      return false;
    },
    getPathToFile: function(packageId, fileName) {
      var result = callNative({
        method: "CCSoomlaDLC::getFilePath",
        packageId: packageId,
        fileName: fileName
      });

      return result.return;
    },
    getListOfFiles: function(packageId) {
      var result = callNative({
        method: "CCSoomlaDLC::getFilesPathsInPackage",
        packageId: packageId
      });

      return result.return;
    }
  });
  SoomlaDLC.createShared = function() {
    var ret = new SoomlaDLC();
    if (ret.init()) {
      Soomla.soomlaDLC = ret;
    } else {
      Soomla.soomlaDLC = null;
    }
  };

  /**
   * EventHandler
   * Here for documentation reasons only, shows signatures for event handlers
   */
  var EventHandler = Soomla.EventHandler = declareClass("EventHandler", {

    //------ Core ------//
    onRewardGivenEvent: function(reward) {},
    onRewardTakenEvent: function(reward) {},
    onCustomEvent: function(name, extra) {},

    //------ Store ------//
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
    onMarketItemsRefreshFailed: function(errorMessage) {},
    onMarketItemsRefreshed: function(marketItems) {},
    onMarketPurchaseVerification: function(purchasableVirtualItem) {},
    onRestoreTransactionsStarted: function() {},
    onRestoreTransactionsFinished: function(success) {},
    onUnexpectedErrorInStore: function() {},
	onSoomlaStoreInitialized: function() {},
    // For Android only
    onMarketRefund: function(purchasableVirtualItem) {},
    onIabServiceStarted: function() {},
    onIabServiceStopped: function() {},

    //------ Profile ------//
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
     @param payload an identification String sent from the caller of the action
     */
    onLoginFailed: function(provider, errorDescription, payload) {},

    /**
     Called when the login process finishes successfully

     @param userProfile The user's profile from the logged in provider
     @param payload an identification String sent from the caller of the action
     */
    onLoginFinished: function(userProfile, payload) {},

    /**
     Called when the login process to a provider has started

     @param provider The provider on where the login has started
     @param payload an identification String sent from the caller of the action
     */
    onLoginStarted: function(provider, payload) {},

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
     @param payload an identification String sent from the caller of the action
     */
    onGetContactsFailed: function(provider, errorDescription, payload) {},

    /**
     Called when the get contacts process from a provider has finished

     @param provider The provider on which the get contacts process finished
     @param contactsDict an Array of contacts represented by CCUserProfile
     @param payload an identification String sent from the caller of the action
     */
    onGetContactsFinished: function(provider, contactsDict, payload) {},

    /**
     Called when the get contacts process from a provider has started

     @param provider The provider on which the get contacts process started
     @param payload an identification String sent from the caller of the action
     */
    onGetContactsStarted: function(provider, payload) {},

    /**
     Called when the get feed process from a provider has failed

     @param provider The provider on which the get feed process has
     failed
     @param errorDescription a Description of the reason for failure
     @param payload an identification String sent from the caller of the action
     */
    onGetFeedFailed: function(provider, errorDescription, payload) {},

    /**
     Called when the get feed process from a provider has finished

     @param provider The provider on which the get feed process finished
     @param feedList an Array of feed entries represented by __String
     @param payload an identification String sent from the caller of the action
     */
    onGetFeedFinished: function(provider, feedList, payload) {},

    /**
     Called when the get feed process from a provider has started

     @param provider The provider on which the get feed process started
     @param payload an identification String sent from the caller of the action
     */
    onGetFeedStarted: function(provider, payload) {},

    /**
     Called when a generic social action on a provider has failed

     @param provider The provider on which the social action has failed
     @param socialActionType The social action which failed
     @param errorDescription a Description of the reason for failure
     @param payload an identification String sent from the caller of the action
     */
    onSocialActionFailedEvent: function(provider, socialActionType, errorDescription, payload) {},

    /**
     Called when a generic social action on a provider has finished

     @param provider The provider on which the social action has finished
     @param socialActionType The social action which finished
     @param payload an identification String sent from the caller of the action
     */
    onSocialActionFinishedEvent: function(provider, socialActionType, payload) {},

    /**
     Called when a generic social action on a provider has started

     @param provider The provider on which the social action has started
     @param socialActionType The social action which started
     @param payload an identification String sent from the caller of the action
     */
    onSocialActionStartedEvent: function(provider, socialActionType, payload) {},

    /**
     Called the login process to a provider has been cancelled

     @param provider The provider on which the login has failed
     @param payload an identification String sent from the caller of the action
     */
    onLoginCancelledEvent: function(provider, payload) {},

    /**
     Called when a user profile from a provider has been retrieved

     @param userProfile The user's profile which was updated
     */
    onUserProfileUpdatedEvent: function(userProfile) {},

    //------ Highway ------//

    /**
     Fired when Soomla Sync is initialized.
     */
    onSoomlaSyncInitialized : function() {},
    /**
     Fired when the meta-data sync process has began.
     */
    onMetaDataSyncStarted : function() {},
    /**
     Fired when the meta-data sync process has finished.
     @param changedComponents a List of modules' names (string) which were synced.
     */
    onMetaDataSyncFinished : function(changedComponents) {},
    /**
     Fired when the meta-data sync process has failed.
     @param errorCode (MetaDataSyncError) The error code of the failure
     @param errorMessage The reason why the process failed
     */
    onMetaDataSyncFailed : function(errorCode, errorMessage) {},
    /**
     Fired when the state sync process has began.
     */
    onStateSyncStarted : function() {},
    /**
     Fired when the state sync process has finished.
     @param changedComponents a List of modules' names (string) which were updated.
     @param failedComponents a List of modules' names (string) which failed to update.
     */
    onStateSyncFinished : function(changedComponents, failedComponents) {},
    /**
     Fired when the state sync process has failed.
     @param errorCode (StateSyncError) The error code of the failure
     @param errorMessage The reason why the process failed
     */
    onStateSyncFailed : function(errorCode, errorMessage) {},
    /**
     Fired when the state reset process has began.
     */
    onStateResetStarted : function() {},
    /**
     Fired when the state reset process has finished.
     */
    onStateResetFinished : function() {},
    /**
     Fired when the state reset process has failed.
     @param errorCode (StateSyncError) The error code of the failure
     @param errorMessage The reason why the process failed
     */
    onStateResetFailed : function(errorCode, errorMessage) {},
    /**
     Fired when Soomla Gifting is initialized.
     */
    onSoomlaGiftingInitialized : function() {},
    /**
     Fired when gifting has started retrieving a list of gifts for the user.
     */
    onGiftsRetrieveStarted : function() {},
    /**
     Fired when the list of gifts for the user has been retrieved.
     NOTE: This event is fired just before the gifts are handed out
     to the user
     @param retrievedGifts a List of gifts (`Gift`) which will be handed
     out.
     */
    onGiftsRetrieveFinished : function(retrievedGifts) {},
    /**
     Fired when gifting failed to retrieve a list of gifts for the user.
     @param errorMessage The reason why the retrieval failed
     */
    onGiftsRetrieveFailed : function(errorMessage) {},
    /**
     Fired when a gift has began to be sent to the server.
     @param gift the gift that is being sent.
     */
    onGiftSendStarted : function(gift) {},
    /**
     Fired when sending the gift has failed.
     NOTE: At this point the gift will have an ID
     @param gift the gift which was sent
     */
    onGiftSendFinished : function(gift) {},
    /**
     Fired when sending the gift has failed.
     @param gift the gift has failed to be sent.
     @param errorMessage The reason why the gift has failed to be sent.
     */
    onGiftSendFailed : function(gift, errorMessage) {},
    /**
     Fired when the gift was handed out to the user.
     @param gift the gift which was handed out to the user.
     */
    onGiftHandOutSuccess : function(gift) {},
    /**
     Fired when handing out the gift to the user has failed.
     @param gift the gift that failed to be handed out.
     @param errorMessage The reason why the gift has failed to be handed out.
     */
    onGiftHandOutFailed : function(gift, errorMessage) {},
    /**
     Fired when soomla query starts querying friends' states for a
     specific social provider.
     @param providerId The social provider ID for which the query operation
     is preformed.
     */
    onQueryFriendsStatesStarted : function(providerId) {},
    /**
     Fired when soomla query finished querying friends' states for a
     specific social provider
     @param providerId The social provider ID for which the query operation
     is preformed.
     @param friendsStates a List of friends' states for the requested query
     */
    onQueryFriendsStatesFinished : function(providerId, friendsStates) {},
    /**
     Fired when soomla query fails to query friends' states for a specific
     social provider
     @param providerId The social provider ID for which the query operation
     is preformed.
     @param errorMessage The error message explaining why the query
     operation failed
     */
    onQueryFriendsStatesFailed : function(providerId, errorMessage) {},

    /**
     Fired when the DLC client is initialized.
     */
    onSoomlaDLCInitialized: function() {},
    /**
     Fired when a package/s update status check has returned from the server.
     @param hasChanges General status against the server state of packages
     @param packagesToSync All packages which were updated on the server
     and need to be synced on the device.
     @param packagesDeleted All packages which were deleted from the
     device as a result of their deletion from the server.
     */
    onDLCPackagesStatusUpdate: function(hasChanges, packagesToSync, packagesDeleted) {},
    /**
     This event is fired when the package starts the syncing process
     @param packageId The package started syncing
     */
    onDLCPackageSyncStarted: function(packageId) {},
    /**
     This event is fired when the package finishes the syncing process
     @param packageId The package finished syncing
     */
    onDLCPackageSyncFinished: function(packageId) {},
    /**
     This event is fired when the package failed the syncing process.
     @param packageId The package which failed to sync
     @param errorCode The error code for this failure
     @param errorMessage The error message for the failure
     */
    onDLCPackageSyncFailed: function(packageId, errorCode, errorMessage) {}
  });

  /**
   * Root definitions
   */
  Soomla.eventHandlers = {};
  Soomla.addEventHandler = Soomla.on = function (eventName, handler, target) {
    var handlersArray = Soomla.eventHandlers[eventName];
    if (handlersArray === undefined) {
      handlersArray = Soomla.eventHandlers[eventName] = [];
    }

    var foundHandler = _.find(handlersArray, function(callbackObject) {
      return ((callbackObject.obj == target) && (callbackObject.callback == handler));
    });

    if (foundHandler != null) {
      return;
    }

    handlersArray.push({
      obj: target,
      callback: handler
    });
  };
  Soomla.removeEventHandler = Soomla.off = function (eventName, handler) {
    var handlersArray = Soomla.eventHandlers[eventName];
    if (handlersArray === undefined) {
      return;
    }

    var filteredArray =_.filter(handlersArray, function(callbackObject) {
      return (callbackObject.callback != handler);
    });
    Soomla.eventHandlers[eventName] = filteredArray;
  };
  Soomla.removeEventHandlersWithTarget = function (target) {
    _.forEach(Soomla.eventHandlers, function(handlers, eventName) {
      var filteredArray =_.filter(handlers, function(callbackObject) {
        return (callbackObject.obj != target);
      });
      Soomla.eventHandlers[eventName] = filteredArray;
    });
  }
  Soomla.fireSoomlaEvent = function (eventName, args) {
    var handlersArray = Soomla.eventHandlers[eventName];
    if (handlersArray === undefined) {
      return;
    }

    _.forEach(handlersArray, function(callbackObject){
      callbackObject.callback.apply(callbackObject.obj, args);
    });
  };

  Soomla.ndkCallback = function (parameters) {
    parameters = JSON.parse(parameters);
    try {
      var methodName = parameters.method || "";

      // ------- Core -------- //
      if (methodName == Soomla.Models.CoreConsts.EVENT_REWARD_GIVEN) {
        var rewardId = parameters['reward'];
        var reward = Soomla.Models.Reward.getReward(rewardId);
        Soomla.fireSoomlaEvent(methodName, [reward]);
      }
      else if (methodName == Soomla.Models.CoreConsts.EVENT_REWARD_TAKEN) {
        var rewardId = parameters['reward'];
        var reward = Soomla.Models.Reward.getReward(rewardId);
        Soomla.fireSoomlaEvent(methodName, [reward]);
      }
      else if (methodName == Soomla.Models.CoreConsts.EVENT_CUSTOM) {
        var name = parameters['name'];
        var extra = parameters['extra'];
        Soomla.fireSoomlaEvent(methodName, [name, extra]);
      }

      // ------- Store -------- //
      else if (methodName == Soomla.Models.StoreConsts.EVENT_BILLING_NOT_SUPPORTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_BILLING_SUPPORTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_CURRENCY_BALANCE_CHANGED) {
        var virtualCurrency = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [virtualCurrency, parameters.balance, parameters.amountAdded]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_BALANCE_CHANGED) {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [virtualGood, parameters.balance, parameters.amountAdded]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_EQUIPPED) {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [equippableVG]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_UNEQUIPPED) {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [equippableVG]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_UPGRADE) {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        var upgradeVG = Soomla.storeInfo.getItemByItemId(parameters.vguItemId);
        Soomla.fireSoomlaEvent(methodName, [virtualGood, upgradeVG]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_ITEM_PURCHASED) {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [purchasableVirtualItem]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_ITEM_PURCHASE_STARTED) {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [purchasableVirtualItem]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_PURCHASE_CANCELED) {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [purchasableVirtualItem]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_PURCHASE) {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        var token = parameters.token;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [purchasableVirtualItem, token, payload]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_PURCHASE_STARTED) {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [purchasableVirtualItem]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_ITEMS_REFRESHED) {
        var marketItemsDict = parameters.marketItems;
        var marketItems = [];
        _.forEach(marketItemsDict, function(marketItem) {

          // be careful confusing naming: snake_case VS camelCase
          var productId = marketItem.productId;
          var marketPrice = marketItem.marketPrice;
          var marketTitle = marketItem.marketTitle;
          var marketDescription = marketItem.marketDesc;

          var pvi = Soomla.storeInfo.getPurchasableItemWithProductId(productId);

          var purchaseWithMarket = pvi.purchasableItem;
          var mi = purchaseWithMarket.marketItem;

          mi.marketPrice        = marketPrice;
          mi.marketTitle        = marketTitle;
          mi.marketDescription  = marketDescription;

          marketItems.push(pvi);
        });

        Soomla.fireSoomlaEvent(methodName, [marketItems]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_ITEMS_REFRESH_STARTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_ITEMS_REFRESH_FAILED) {
        Soomla.fireSoomlaEvent(methodName, [parameters.errorMessage]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_PURCHASE_VERIFICATION) {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [purchasableVirtualItem]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_RESTORE_TRANSACTION_FINISHED) {
        Soomla.fireSoomlaEvent(methodName, [parameters.success]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_RESTORE_TRANSACTION_STARTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_UNEXPECTED_ERROR_IN_STORE) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_SOOMLA_STORE_INITIALIZED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      //  Android specific
      else if (methodName == Soomla.Models.StoreConsts.EVENT_MARKET_REFUND) {
        var purchasableVirtualItem = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        Soomla.fireSoomlaEvent(methodName, [purchasableVirtualItem]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_IAB_SERVICE_STARTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_IAB_SERVICE_STOPPED) {
        Soomla.fireSoomlaEvent(methodName);
      }

      // Profile
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_PROFILE_INITIALIZED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_USER_RATING) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_LOGIN_CANCELLED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_LOGIN_FAILED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, errorDescription, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_LOGIN_FINISHED) {
        var userProfile = parameters.userProfile;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [userProfile, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_LOGIN_STARTED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_LOGOUT_FAILED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        Soomla.fireSoomlaEvent(methodName, [provider, errorDescription]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_LOGOUT_FINISHED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        Soomla.fireSoomlaEvent(methodName, [provider]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_LOGOUT_STARTED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        Soomla.fireSoomlaEvent(methodName, [provider]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_GET_CONTACTS_FAILED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, errorDescription, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_GET_CONTACTS_FINISHED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var contacts = parameters.contacts;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, contacts, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_GET_CONTACTS_STARTED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_GET_FEED_FAILED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var errorDescription = parameters.errorDescription;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, errorDescription, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_GET_FEED_FINISHED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var feed = parameters.feed;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, feed, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_GET_FEED_STARTED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_SOCIAL_ACTION_FAILED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var socialActionType = parameters.socialActionType;
        var errorDescription = parameters.errorDescription;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, socialActionType, errorDescription, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var socialActionType = parameters.socialActionType;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, socialActionType, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_SOCIAL_ACTION_STARTED) {
        var providerId = parameters.provider;
        var provider = Provider.findById(providerId);
        var socialActionType = parameters.socialActionType;
        var payload = parameters.payload;
        Soomla.fireSoomlaEvent(methodName, [provider, socialActionType, payload]);
      }
      else if (methodName == Soomla.Models.ProfileConsts.EVENT_USER_PROFILE_UPDATED) {
        var userProfile = parameters.userProfile;
        Soomla.fireSoomlaEvent(methodName, [userProfile]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.INTERNAL_EVENT_ON_STATE_CONFLICT) {
        var remoteState = parameters.remoteState;
        var currentState = parameters.currentState;
        var stateDiff = parameters.stateDiff;

        if (Soomla.soomlaSync.resolveStateConflict) {
          Soomla.soomlaSync.resolveStateConflict(remoteState, currentState, stateDiff);
        }
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_SOOMLA_SYNC_INITIALIZED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_META_SYNC_STARTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_META_SYNC_FINISHED) {
        var changedComponents = parameters.changedComponents;
        Soomla.fireSoomlaEvent(methodName, [changedComponents]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_META_SYNC_FAILED) {
        var errorCode = parameters.errorCode;
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [errorCode, errorMessage]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_STATE_SYNC_STARTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_STATE_SYNC_FINISHED) {
        var changedComponents = parameters.changedComponents;
        var failedComponents = parameters.failedComponents;
        Soomla.fireSoomlaEvent(methodName, [changedComponents, failedComponents]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_STATE_SYNC_FAILED) {
        var errorCode = parameters.errorCode;
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [errorCode, errorMessage]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_STATE_RESET_STARTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_STATE_RESET_FINISHED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_STATE_RESET_FAILED) {
        var errorCode = parameters.errorCode;
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [errorCode, errorMessage]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_SOOMLA_GIFTING_INITIALIZED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFTS_RETRIEVE_STARTED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFTS_RETRIEVE_FINISHED) {
        var givenGifts = parameters.givenGifts;
        Soomla.fireSoomlaEvent(methodName, [givenGifts]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFTS_RETRIEVE_FAILED) {
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [errorMessage]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFT_SEND_STARTED) {
        var gift = parameters.gift;
        Soomla.fireSoomlaEvent(methodName, [gift]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFT_SEND_FINISHED) {
        var gift = parameters.gift;
        Soomla.fireSoomlaEvent(methodName, [gift]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFT_SEND_FAILED) {
        var gift = parameters.gift;
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [gift, errorMessage]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFT_HAND_OUT_SUCCESS) {
        var gift = parameters.gift;
        Soomla.fireSoomlaEvent(methodName, [gift]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_GIFT_HAND_OUT_FAILED) {
        var gift = parameters.gift;
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [gift, errorMessage]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_QUERY_FRIENDS_STATES_STARTED) {
        var providerId = parameters.providerId;
        Soomla.fireSoomlaEvent(methodName, [providerId]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_QUERY_FRIENDS_STATES_FINISHED) {
        var providerId = parameters.providerId;
        var friendsStates = parameters.friendsStates;
        Soomla.fireSoomlaEvent(methodName, [providerId, friendsStates]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_QUERY_FRIENDS_STATES_FAILED) {
        var providerId = parameters.providerId;
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [providerId, errorMessage]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_SOOMLA_DLC_INITIALIZED) {
        Soomla.fireSoomlaEvent(methodName);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_DLC_PACKAGE_STATUS_UPDATED) {
        var hasChanges = parameters.hasChanges;
        var packagesToSync = parameters.packagesToSync;
        var packagesDeleted = parameters.packagesDeleted;
        Soomla.fireSoomlaEvent(methodName, [hasChanges, packagesToSync, packagesDeleted]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_DLC_PACKAGE_SYNC_STARTED) {
        var packageId = parameters.packageId;
        Soomla.fireSoomlaEvent(methodName, [packageId]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_DLC_PACKAGE_SYNC_FINISHED) {
        var packageId = parameters.packageId;
        Soomla.fireSoomlaEvent(methodName, [packageId]);
      }
      else if (methodName == Soomla.Models.HighwayConsts.EVENT_DLC_PACKAGE_SYNC_FAILED) {
        var packageId = parameters.packageId;
        var errorCode = parameters.errorCode;
        var errorMessage = parameters.errorMessage;
        Soomla.fireSoomlaEvent(methodName, [packageId, errorCode, errorMessage]);
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
    init: function(storeAssets, storeParams) {

      // Redundancy checking. Most JS libraries don't do this. I hate it when they don't do this. Do this.
      var fields = ["androidPublicKey", "SSV", "testPurchases"];
      var wrongParams = _.omit(storeParams, fields);
      if (wrongParams.length > 0) {
        logDebug("WARNING!! Possible typo in member of storeParams: " + wrongParams);
      }

      storeParams = _.pick(storeParams, fields);
      storeParams.androidPublicKey  = storeParams.androidPublicKey || "";
      storeParams.SSV  = storeParams.SSV === true || false;
      storeParams.testPurchases  = storeParams.testPurchases === true || false;

      if (sys.os == "android" && storeParams.androidPublicKey.length == 0) {
        logError("SOOMLA/COCOS2DX MISSING publickKey !!! Stopping here !!");
        return false;
      }

      if (sys.os == "android" && storeParams.androidPublicKey == this.SOOMLA_AND_PUB_KEY_DEFAULT) {
        logError("SOOMLA/COCOS2DX You have to change android publicKey !!! Stopping here !!");
        return false;
      }

      if (sys.os == "ios") {
        callNative({
          method: "CCSoomlaStore::setSSV",
          ssv: storeParams.SSV
        });
      }

      StoreInfo.createShared(storeAssets);

      callNative({
        method: "CCStoreServiceJsb::init"
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
    init: function(customParams) {
      callNative({
        method: "CCProfileBridge::init",
        params: customParams
      });

      this.inited = true;
      return true;
    },
    login: function(provider, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::login",
        provider: provider.key
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
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
    updateStatus: function(provider, status, payload, reward) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStatus",
        provider: provider.key,
        status: status
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    updateStatusDialog: function(provider, link, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStatusDialog",
        provider: provider.key,
        link: link
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    updateStory: function(provider, message, name, caption, description, link, picture, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStory",
        provider: provider.key,
        message: message,
        name: name,
        caption: caption,
        description: description,
        link: link,
        picture: picture
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    updateStoryDialog: function(provider, name, caption, description, link, picture, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::updateStoryDialog",
        provider: provider.key,
        name: name,
        caption: caption,
        description: description,
        link: link,
        picture: picture
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    uploadImage: function(provider, message, filePath, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::uploadImage",
        provider: provider.key,
        message: message,
        filePath: filePath
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    getContacts: function(provider, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::getContacts",
        provider: provider.key,
        reward: reward
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    getFeed: function(provider, reward, payload) {
      var toPassData = {
        method: "CCSoomlaProfile::getFeed",
        provider: provider.key
      };

      if (payload) {
        toPassData.payload = payload;
      }
      else {
        toPassData.payload = "default";
      }

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    isLoggedIn: function(provider) {
      var retParams = callNative({
        method: "CCSoomlaProfile::isLoggedIn",
        provider: provider.key
      });
      return retParams.return;
    },
    like: function(provider, pageName, reward) {
      var toPassData = {
        method: "CCSoomlaProfile::like",
        provider: provider.key,
        pageName: pageName
      };

      if (reward) {
        toPassData.reward = reward;
      }

      callNative(toPassData, true);
    },
    openAppRatingPage: function() {
      callNative({
        method: "CCSoomlaProfile::openAppRatingPage"
      });
    }
  });

  SoomlaProfile.createShared = function(customParams) {
    var ret = new SoomlaProfile();
    if (ret.init(customParams)) {
      Soomla.soomlaProfile = ret;
    } else {
      Soomla.soomlaProfile = null;
    }
  };

    var callNative = function (params, clean) {
    var jsonString = null;

    if (typeof(clean) === "undefined") {
      jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params));
    }
    else {
      jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params, removeNulls));
    }

    var result = JSON.parse(jsonString);

    if (!result.success) {
      throw new SoomlaException(result.code, result.info);
    }
    return result.result;
  };

  var removeNulls = function(key, value) {
    if (!value){
      return undefined;
    }

    return value;
  }

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
