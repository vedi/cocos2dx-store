if (_.isUndefined(window.Soomla)) {
  window.Soomla = {
  };
}

// for compatibility with v2
if (_.isUndefined(cc.sys)) {
  cc.sys = sys;
}

// for compatibility with v2
if (_.isUndefined(window.console)) {
  window.console = cc;
}


var PrevSoomla = Soomla;
Soomla = new function () {

  var platform = {
    name: cc.sys.os.toLowerCase(),
    isNativeSupported: function isNativeSupported() {
      return this.isAndroid() || this.isIos();
    },
    isAndroid: function isAndroid() {
      return this.name === "android";
    },
    isIos: function isIos() {
      return this.name === "ios";
    }
  };

  var Soomla = _.extend(PrevSoomla, {Models: {}}); // merge with binding instance

  Soomla.DEBUG = false;

  Soomla.factory = {
    classFactories: {},
    create: function(data) {
      data.className = data.className ||
      (data.purchaseType === 'market' && 'PurchaseWithMarket') ||
      (data.purchaseType === 'virtualItem' && 'PurchaseWithVirtualItem');
      this.checkForClass(data);
      var classFactory = this.classFactories[data.className];
      if (classFactory) {
        var result = classFactory.call(this, data);
        result.factored = true;
        return result;
      } else {
        logError('Cannot find factory for className: ' + data.className);
        return null;
      }
    },
    checkForClass: function (data) {
      _.forEach(data, function (value, key) {
        if (_.isPlainObject(value)) {
          value.className = value.className ||
          (value.purchaseType === 'market' && 'PurchaseWithMarket') ||
          (value.purchaseType === 'virtualItem' && 'PurchaseWithVirtualItem');

          if (!value.className) {
            this.checkForClass(value);
          } else {
            data[key] = this.create(value);
          }
        }
      }, this);
    }
  };

  var declareClass = Soomla.declareClass = function (ClassName, fields, parentClass) {
    // TODO: It's better if change it to standard constructor
    var Clazz = function () {
      var parent = parentClass ? parentClass() : {};
      var __super__ = _.pick(parent, _.methods(parent));

      var obj = _.extend(parent, fields ? fields : {}, {
        className: ClassName
      });

      obj.__super__ = __super__;

      if (_.isFunction(obj.ctor)) {
        obj.ctor.call(obj);
      }

      return obj;
    };

    Clazz.create = function (values) {
      var instance = Clazz();

      _.assign(instance, values ? _.omit(values, ['className', '__super__']) : {});

      if (_.isFunction(instance.onCreate)) {
        instance.onCreate.call(instance);
      }
      return instance;
    };

    Soomla.factory.classFactories[ClassName] = Clazz.create;

    return Clazz;
  };

  //------ Core ------//
  /**
   * Domain
   */
  var Domain = Soomla.Models.Domain = declareClass("Domain", {
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
              logDebug("It's a EVERY_HOUR recurrence. APPROVED!");
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
    /**
     Gives your user the given amount of the specific virtual item.
     For example, when your users play your game for the first time you
     GIVE them 1000 gems.

     NOTE: This action is different than `PurchasableVirtualItem<`'s `buy()`:
     You use `give(int amount)`to give your user something for free.
     You use `buy()` to give your user something and get something in return.

     @param amount the amount of the specific item to be given.
     @param notify Notify of change in user's balance of current virtual item
     @return The balance after the giving process.
     */
    give: function (amount, notify) {
      logError('IMPLEMENT ME!');
    },

    /**
     Takes from your user the given amount of the specific virtual item.
     For example, when you want to downgrade a virtual good, you take the upgrade.

     @param amount The amount of the specific item to be taken.
     @param notify Notify of change in user's balance of current virtual item
     @return The balance after the taking process.
     */
    take: function take(amount, notify) {
      logError('IMPLEMENT ME!');
    },

    /**
     Resets this Virtual Item's balance to the given balance.

     @param balance The balance of the current virtual item.
     @param notify Notify of change in user's balance of current virtual item.
     @return The balance after the reset process.
     */
    resetBalance: function resetBalance(balance, notify) {
      logError('IMPLEMENT ME!');
    },

    /**
     Will fetch the balance for the current VirtualItem according to its type.

     @return The balance.
     */
    getBalance: function getBalance() {
      logError('IMPLEMENT ME!');
    },

    /**
     Save this instance with changes that were made to it.
     The saving is done in the metadata in StoreInfo and being persisted to the local DB.

     @param saveToDB should the save persist to the local DB.
     */
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
    // androidId: null,
    // iosId: null,
    consumable: null,
    price: null,
    marketPrice: 0,
    marketTitle: null,
    marketDesc: null,
    marketCurrencyCode: null,
    marketPriceMicros: 0,

    onCreate: function () {
      if (!this.productId) {
        if (platform.isAndroid()) {
          this.productId = this.androidId;
        } else if (platform.isIos()) {
          this.productId = this.iosId;
        }
      }
    }
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
    purchasableItem: null,

    onCreate: function () {
      this.purchasableItem.associatedItemId = this.itemId;
    },

    /**
     Checks if there is enough funds to afford the `CCPurchasableVirtualItem`.
     This action uses the associated `CCPurchaseType` to perform the check.
     @return True if there are enough funds to afford the virtual item
     with the given item id
     */
    canAfford: function canAfford() {
      this.purchasableItem.canAfford();
    },

    /**
     Buys the `CCPurchasableVirtualItem`, after checking if the user is in a state that
     allows him/her to buy. This action uses the associated `CCPurchaseType` to perform
     the purchase.

     @param payload a string you want to be assigned to the purchase.
     This string is saved in a static variable and will be given bacl to you
     when the purchase is completed..
     */
    buy: function buy(payload) {
      if (!this.canBuy()) {
        return;
      }

      if (!payload) {
        payload = "";
      }

      this.purchasableItem.buy(payload);
    },

    /**
     Determines if user is in a state that allows him/her to buy a specific
     `CCVirtualItem`.
     */
    canBuy: function canBuy() {
      return false;
    }
  }, VirtualItem);

  /**
   * VirtualCurrency
   */
  var VirtualCurrency = Soomla.Models.VirtualCurrency = declareClass("VirtualCurrency", {
    /**
     See parent
     */
    give: function give(amount, notify) {
      return Soomla.virtualCurrencyStorage.add(this, amount, notify);
    },
    /**
     See parent
     */
    take: function take(amount, notify) {
      return Soomla.virtualCurrencyStorage.remove(this, amount, notify);
    },

    /**
     See parent
     */
    resetBalance: function (balance, notify) {
      return Soomla.virtualCurrencyStorage.setBalance(this, balance, notify);
    },

    /**
     See parent
     */
    getBalance: function getBalance() {
      return Soomla.virtualCurrencyStorage.getBalance(this);
    }
  }, VirtualItem);

  /**
   * VirtualCurrencyPack
   */
  var VirtualCurrencyPack = Soomla.Models.VirtualCurrencyPack = declareClass("VirtualCurrencyPack", {
    currency_amount: 0,
    currency_itemId: null,

    /**
     See parent
     */
    canBuy: function canBuy() {
      return true;
    },

    /**
     See parent
     */
    give: function (amount, notify) {
      var currencyId = this.currency_itemId;
      var currency = Soomla.storeInfo.getItemByItemId(currencyId);

      if (!currency) {
        logError('VirtualCurrency with itemId: ' + currencyId + ' doesn\'t exist! Can\'t give this pack.');
        return 0;
      }

      return Soomla.virtualCurrencyStorage.add(currency, this.currency_amount * amount, notify);
    },

    /**
     See parent
     */
    take: function take(amount, notify) {
      var currencyId = this.currency_itemId;
      var currency = Soomla.storeInfo.getItemByItemId(currencyId);

      if (!currency) {
        logError('VirtualCurrency with itemId: ' + currencyId + ' doesn\'t exist! Can\'t take this pack.');
        return 0;
      }

      return Soomla.virtualCurrencyStorage.remove(currency, this.currency_amount * amount, notify);
    },

    /**
     See parent
     */
    resetBalance: function resetBalance(balance, notify) {
      // Not supported for VirtualCurrencyPacks !
      logError('Someone tried to reset balance of CurrencyPack. That\'s not right.');
      return 0;
    },

    /**
     See parent
     */
    getBalance: function getBalance() {
      // Not supported for VirtualCurrencyPacks !
      logError("Someone tried to check balance of CurrencyPack. That's not right.");
      return 0;
    }

  }, PurchasableVirtualItem);

  /**
   * VirtualGood
   */
  var VirtualGood = Soomla.Models.VirtualGood = declareClass("VirtualGood", {
    /**
     See parent
     */
    resetBalance: function resetBalance(balance, notify) {
      return Soomla.virtualGoodsStorage.setBalance(this, balance, notify);
    },
    /**
     See parent
     */
    getBalance: function getBalance() {
      return Soomla.virtualGoodsStorage.getBalance(this);

    }
  }, PurchasableVirtualItem);

  /**
   * LifetimeVG
   */
  var LifetimeVG = Soomla.Models.LifetimeVG = declareClass("LifetimeVG", {
    /**
     See parent
     */
    canBuy: function () {
      var balance = Soomla.virtualGoodsStorage.getBalance(this);

      return balance < 1;
    },

    /**
     See parent
     */
    give: function (amount, notify) {
      if (amount > 1) {
        logDebug('You tried to give more than one LifetimeVG. \
                                    Will try to give one anyway.');
        amount = 1;
      }

      var balance = Soomla.virtualGoodsStorage.getBalance(this);

      if (balance < 1) {
        return Soomla.virtualGoodsStorage.add(this, amount, notify);
      }
      return 1;
    },

    /**
     See parent
     */
    take: function (amount, notify) {
      if (amount > 1) {
        amount = 1;
      }

      var balance = Soomla.virtualGoodsStorage.getBalance(this);

      if (balance > 0) {
        return Soomla.virtualGoodsStorage.remove(this, amount, notify);
      }
      return 0;
    }
  }, VirtualGood);

  /**
   * EquippableVG
   */
  var EquippableVG = Soomla.Models.EquippableVG = declareClass("EquippableVG", {
    equipping: null,

    /**
     Equips the current `CCEquippableVG`.
     The equipping is done according to the equipping model ('GLOBAL', 'CATEGORY', or 'LOCAL').
     @param notify if true, the relevant event will be posted when equipped.
     be returned here
     */
    equip: function (notify) {
      notify = notify || _.isUndefined(notify);

      // only if the user has bought this EquippableVG, the EquippableVG is equipped.
      if (Soomla.virtualGoodsStorage.getBalance(this) > 0) {
        var equippingModel = this.equipping;
        if (equippingModel === EquippableVG.EquippingModel.CATEGORY) {
          var itemId = this.itemId;
          var category = Soomla.storeInfo.getCategoryForVirtualGood(itemId);
          if (!category) {
            logError('Tried to unequip all other category VirtualGoods but there was no associated category. \
                  virtual good itemId: ' + itemId);
            return;
          }

          var goodItemIds = category.goods_itemIds;
          _.forEach(goodItemIds, function (goodItemId) {
            var equippableVG = Soomla.storeInfo.getItemByItemId(goodItemId);
            if (!equippableVG) {
              logError("On equip, couldn't find one of the itemIds in the category. " +
              "Continuing to the next one. itemId: " + goodItemId);
            }
            else if (equippableVG !== this) {
              equippableVG.unequip(notify);
            }
          }, this);

        } else if (equippingModel == EquippableVG.EquippingModel.GLOBAL) {
          var virtualGoods = Soomla.storeInfo.getGoods();
          _.forEach(virtualGoods, function (virtualGood) {
            if ((virtualGood != this) && (virtualGood.className === "EquippableVG")) {
              virtualGood.unequip(notify);
            }
          }, this);
        }

        Soomla.virtualGoodsStorage.equip(this, notify);
      }
      else {
        logError('You tried to equip virtual good with itemId: ' + this.itemId + ' but you don\'t have any of it.');
      }
    },

    /**
     Unequips the current `CCEquippableVG`
     @param notify if true, the relevant event will be posted when equipped.
     @param error If an error was generated during the execution it will
     be returned here
     */
    unequip: function (notify) {
      notify = notify || _.isUndefined(notify);
      Soomla.virtualGoodsStorage.unequip(this, notify);
    }

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

    /**
     See parent
     */
    canBuy: function () {
      return true;
    },

    /**
     See parent
     */
    give: function (amount, notify) {
      return Soomla.virtualGoodsStorage.add(this, amount, notify);

    },

    /**
     See parent
     */
    take: function (amount, notify) {
      return Soomla.virtualGoodsStorage.remove(this, amount, notify);
    }

  }, VirtualGood);

  /**
   * SingleUsePackVG
   */
  var SingleUsePackVG = Soomla.Models.SingleUsePackVG = declareClass("SingleUsePackVG", {
    good_itemId: null,
    good_amount: null,

    /**
     See parent
     */
    canBuy: function () {
      return true;
    },

    /**
     See parent
     */
    give: function (amount, notify) {
      var goodItemId = this.good_itemId;
      var good = Soomla.storeInfo.getItemByItemId(goodItemId);

      if (!good) {
        logError('SingleUseVG with itemId: ' + goodItemId + ' doesn\'t exist! Can\'t give this pack.');
        return 0;
      }

      return Soomla.virtualGoodsStorage.add(good, this.good_amount * amount, notify);
    },

    /**
     See parent
     */
    take: function (amount, notify) {
      var goodItemId = this.good_itemId;
      var good = Soomla.storeInfo.getItemByItemId(goodItemId);

      if (!good) {
        logError('SingleUseVG with itemId: ' + goodItemId + ' doesn\'t exist! Can\'t give this pack.');
        return 0;
      }

      return Soomla.virtualGoodsStorage.remove(good, this.good_amount * amount, notify);
    },

    /**
     See parent
     */
    resetBalance: function (balance, notify) {
      // Not supported for SingleUsePackVGs !
      logError('Someone tried to reset balance of GoodPack. That\'s not right.');
      return 0;
    },

    /**
     See parent
     */
    getBalance: function () {
      // Not supported for SingleUsePackVGs !
      logError('Someone tried to check balance of GoodPack. That\'s not right.');
      return 0;
    }
  }, VirtualGood);

  /**
   * UpgradeVG
   */
  var UpgradeVG = Soomla.Models.UpgradeVG = declareClass("UpgradeVG", {
    good_itemId: null,
    prev_itemId: null,
    next_itemId: null,

    /**
     See parent
     */
    canBuy: function () {
      var goodItemId = this.good_itemId;
      var good = Soomla.storeInfo.getItemByItemId(goodItemId);
      if (!good) {
        logError('VirtualGood with itemId: ' + goodItemId + ' doesn\'t exist! Returning false (can\'t buy).');
        return false;
      }

      var upgradeVG = Soomla.virtualGoodsStorage.getCurrentUpgrade(good);

      return ((!upgradeVG && (_.isNull(this.prev_itemId) || _.isEmpty(this.prev_itemId))) ||
        (upgradeVG && (upgradeVG.next_itemId === this.itemId) || upgradeVG.prev_itemId === this.itemId))
        && this.__super__.canBuy.apply(this, arguments);
    },

    /**
     See parent
     */
    give: function (amount, notify) {
      var goodItemId = this.good_itemId;
      logDebug('Assigning ' + this.name + ' to: ' + this.itemId);

      var good = Soomla.storeInfo.getItemByItemId(goodItemId);
      if (!good) {
        logError('VirtualGood with itemId: ' + goodItemId + ' doesn\'t exist! Can\'t upgrade.');
        return 0;
      }

      Soomla.virtualGoodsStorage.assignCurrentUpgrade(good, this, notify);

      return this.__super__.give.apply(this, arguments);
    },

    /**
     See parent
     */
    take: function (amount, notify) {
      var goodItemId = this.good_itemId;

      var good = Soomla.storeInfo.getItemByItemId(goodItemId);
      if (!good) {
        logError('VirtualGood with itemId: ' + goodItemId + ' doesn\'t exist! Can\'t downgrade.');
        return 0;
      }

      var upgradeVG = Soomla.virtualGoodsStorage.getCurrentUpgrade(good, error);

      // Case: Upgrade is not assigned to this Virtual Good
      if (upgradeVG !== this) {
        logError('You can\'t take an upgrade that\'s not currently assigned. The UpgradeVG ' + this.name +
        ' is not assigned to the VirtualGood: ' + good.name);
        return 0;
      }

      if (!(_.isNull(this.prev_itemId) || _.isEmpty(this.prev_itemId))) {
        var prevItemId = this.prev_itemId;
        var prevUpgradeVG = Soomla.storeInfo.getItemByItemId(prevItemId);

        // Case: downgrade is not possible because previous upgrade does not exist
        if (!prevUpgradeVG) {
          logError('Previous UpgradeVG with itemId: ' + prevItemId + ' doesn\'t exist! Can\'t downgrade.');
          return 0;
        }

        // Case: downgrade is successful!
        logDebug('Downgrading ' + good.name + ' to: ' + prevUpgradeVG.name);

        Soomla.virtualGoodsStorage.assignCurrentUpgrade(good, prevUpgradeVG, notify);
      }

      // Case: first Upgrade in the series - so we downgrade to NO upgrade.
      else {
        logError('Downgrading ' + good.name + ' to NO-UPGRADE');
        Soomla.virtualGoodsStorage.removeUpgrades(good, notify, error);
      }

      return this.__super__.take.apply(this, arguments);
    }
  }, LifetimeVG);

  /**
   * PurchaseType
   */
  var PurchaseType = Soomla.Models.PurchaseType = declareClass("PurchaseType", {
    purchaseType: null,
    associatedItemId : null,

    /**
     Buys the purchasable virtual item.
     Implementation in subclasses will be according to specific type of
     purchase.

     @param payload string you want to be assigned to the purchase. This
     string is saved in a static variable and will be given bacl to you when
     the purchase is completed.
     */
    buy: function (payload) {
      logError('IMPLEMENT ME!');
    },

    /**
     Checks if there is enough funds to afford the `CCPurchasableVirtualItem`.
     Implementation in subclasses will be according to specific type of purchase.
     @return True if there are enough funds to afford the virtual item
     with the given item id
     */
    canAfford: function () {
      logError('IMPLEMENT ME!');
    }
  });

  /**
   * PurchaseWithMarket
   */
  var PurchaseWithMarket = Soomla.Models.PurchaseWithMarket = declareClass("PurchaseWithMarket", {
    purchaseType: PURCHASE_TYPE.MARKET,
    marketItem: null,

    /**
     See parent
     */
    buy: function (payload) {
      logDebug('Starting in-app purchase for productId: ' + this.marketItem.productId);

      if (_.isNull(payload)) {
        payload = "";
      }

      var pvi = Soomla.storeInfo.getItemByItemId(this.associatedItemId);
      Soomla.fireSoomlaEvent(StoreConsts.EVENT_ITEM_PURCHASE_STARTED, [pvi, true]);
      Soomla.soomlaStore.buyMarketItem(this.marketItem.productId, payload);
    },

    /**
     See parent
     */
    canAfford: function () {
      return true;
    }

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
    pvi_amount: null,

    /**
     See parent
     */
    buy: function (payload) {
      var associatedItemId = this.associatedItemId;
      if (!payload) {
        payload = "";
      }
      var associatedItem = Soomla.storeInfo.getItemByItemId(associatedItemId);
      if (!associatedItem) {
        logError('Trying to buy an non-existing associated item: ' + associatedItemId);
        return;
      }

      var targetItemId = this.pvi_itemId;
      var amount = this.pvi_amount;
      logDebug('Trying to buy a ' + associatedItem.name +' with ' + amount + ' pieces of ' + targetItemId);

      var item = Soomla.storeInfo.getItemByItemId(targetItemId);
      if (!item) {
        logError('Target virtual item ' + targetItemId + ' doesn\'t exist !');
        return;
      }

      Soomla.fireSoomlaEvent(StoreConsts.EVENT_ITEM_PURCHASE_STARTED, [associatedItem, true]);

      var balance = item.getBalance();

      if (balance < amount){
        logError('You tried to buy with itemId: ' + item.itemId + ' but you don\'t have enough funds to buy it.');
        return;
      }

      item.take(amount);

      associatedItem.give(1);

      Soomla.fireSoomlaEvent(StoreConsts.EVENT_ITEM_PURCHASED, [associatedItem, payload, true]);
    },

    /**
     See parent
     */
    canAfford: function () {
      var associatedItemId = this.associatedItemId || this.pvi_itemId;

      var associatedItem = Soomla.storeInfo.getItemByItemId(associatedItemId);
      if (!associatedItem) {
        logError('Trying to buy an non-existing associated item: ' + associatedItemId);
        return;
      }

      var targetItemId = this.pvi_itemId;
      var amount = this.pvi_amount;
      logDebug('Checking affordability of ' + associatedItem.name + ' with ' + amount + ' pieces of ' + targetItemId);

      var item = Soomla.storeInfo.getItemByItemId(targetItemId);
      if (!item) {
        logError('Target virtual item ' + targetItemId + ' doesn\'t exist !');
        return false;
      }

      var balance = item.getBalance();

      return balance >= amount;
    }

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
    var retArray = retParams.return || [];

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
   * Soomla
   */
  Soomla.DB_KEY_PRFIX = 'soomla.';
  Soomla.initialize = function initialize(soomlaSecret) {
    if (!soomlaSecret || soomlaSecret.length == 0) {
      logError("Can't initialize SOOMLA without soomlaSecret");
      return false;
    }

    Soomla.coreBridge = platform.isNativeSupported() ? NativeCoreBridge.create() : BridgelessCoreBridge.create();

    callNative({
      method: "CCSoomla::initialize",
      soomlaSecret: soomlaSecret
    });

    return true;
  };

  /**
   * NativeCoreBridge
   */
  var NativeCoreBridge = Soomla.NativeCoreBridge = declareClass("NativeCoreBridge", {
    ctor: function () {
      this.bindNative();
    },
    bindNative: function () {
      logDebug('Binding to native platform bridge...');
      if (!_.isUndefined(window.jsb)) {
        if (platform.isAndroid()) {
          jsb.reflection.callStaticMethod('com/soomla/cocos2dx/common/CoreBridgeBinder', "bind", "()V");
        } else if (platform.isIos()) {
          jsb.reflection.callStaticMethod('CoreBridge', 'initShared');
        } else {
          logError('Unsupported platform: ' + platform.name);
        }
      } else {
        logDebug('Your version of JSB does not support reflection. Do not forget to initialize the bridges on the native sides.');
      }
    }
  });

  /**
   * BridgelessCoreBridge
   */
  var BridgelessCoreBridge = Soomla.BridgelessCoreBridge = declareClass("BridgelessCoreBridge", {
  });


  /**
   * NativeKeyValueStorage
   */
  var NativeKeyValueStorage = Soomla.NativeKeyValueStorage = declareClass("NativeKeyValueStorage", {
    getValue: function getValue(key) {
      var result = callNative({
        method: "CCNativeKeyValueStorage::getValue",
        key: key
      });
      return result.return;
    },
    setValue: function setValue(key, val) {
      callNative({
        method: "CCNativeKeyValueStorage::setValue",
        key: key,
        val: val
      });
    },
    deleteKeyValue: function deleteKeyValue(key) {
      callNative({
        method: "CCNativeKeyValueStorage::deleteKeyValue",
        key: key
      });
    },
    purge: function purge() {
      callNative({
        method: "CCNativeKeyValueStorage::purge"
      });
    }
  });

  /**
   * BridgelessKeyValueStorage
   */
  var BridgelessKeyValueStorage = Soomla.BridgelessKeyValueStorage = declareClass("BridgelessKeyValueStorage", {
    KEY_VALUE_STORAGE_KEY: 'soomla.kvs.keys',
    mStoredKeys: [],

    ctor: function () {
      this.loadStoredKeys();
    },

    getValue: function getValue(key) {
      var defaultValue = "";
      var result = cc.sys.localStorage.getItem(key) || defaultValue;
      logDebug('getValue with key: ' + key + ', result: ' + result);
      return result;
    },
    setValue: function setValue(key, val) {
      cc.sys.localStorage.setItem(key, val);

      logDebug('setValue with key: ' + key + ', value: ' + val);

      this.addStoredKeys(key);
      this.saveStoredKeys();
    },
    deleteKeyValue: function deleteKeyValue(key) {
      cc.sys.localStorage.removeItem(key);

      logDebug('deleteKeyValue with key: ' + key);

      this.removeStoredKeys(key);
      this.saveStoredKeys();
    },
    purge: function purge() {
      logDebug('purge');

      _.forEach(this.mStoredKeys, function (key) {
        this.deleteKeyValue(key);
      }, this);

      cc.sys.localStorage.setItem(this.KEY_VALUE_STORAGE_KEY, "");
    },

    addStoredKeys: function (key) {
      if (this.mStoredKeys.indexOf(key) < 0) {
        this.mStoredKeys.push(key);
      }
    },
    removeStoredKeys: function (key) {
      var idx = this.mStoredKeys.indexOf(key);
      if (idx >= 0) {
        this.mStoredKeys.splice(idx, 1);
      }
    },
    saveStoredKeys: function () {
      cc.sys.localStorage.setItem(this.KEY_VALUE_STORAGE_KEY, JSON.stringify(this.mStoredKeys));
    },
    loadStoredKeys: function () {
      var strKeys = cc.sys.localStorage.getItem(this.KEY_VALUE_STORAGE_KEY);
      if (strKeys) {
        this.mStoredKeys = JSON.parse(strKeys);
      }
    }
  });

  Soomla.keyValueStorage = platform.isNativeSupported() ? NativeKeyValueStorage.create() : BridgelessKeyValueStorage.create();

  /**
   * NativeRewardStorage
   */
  var NativeRewardStorage = Soomla.NativeRewardStorage = declareClass("NativeRewardStorage", {
    setRewardStatus: function setRewardStatus(reward, give, notify) {
      notify = notify || _.isUndefined(notify);
      callNative({
        method: "CCNativeRewardStorage::setRewardStatus",
        reward: reward.itemId,
        give: give,
        notify: notify
      });
    },
    getTimesGiven: function getTimesGiven(reward) {
      var result = callNative({
        method: "CCNativeRewardStorage::getTimesGiven",
        reward: reward.itemId
      });
      return result.return;
    },
    isRewardGiven: function isRewardGiven(reward) {
      return this.getTimesGiven(reward) > 0;
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
    }
  });

  /**
   * BridgelessRewardStorage
   */
  var BridgelessRewardStorage = Soomla.BridgelessRewardStorage = declareClass("BridgelessRewardStorage", {
    setRewardStatus: function setRewardStatus(reward, give, notify) {
      notify = notify || _.isUndefined(notify);
      this.setTimesGiven(reward, give, notify);
    },
    getTimesGiven: function getTimesGiven(reward) {
      var key = this.keyRewardTimesGiven(reward.getId());
      var val = Soomla.keyValueStorage.getValue(key);
      return (!_.isUndefined(val) && !_.isNull(val)) ? val : 0;
    },
    isRewardGiven: function isRewardGiven(reward) {
      return this.getTimesGiven(reward) > 0;
    },
    getLastSeqIdxGiven: function getLastSeqIdxGiven(sequenceReward) {
      var key = this.keyRewardIdxSeqGiven(sequenceReward.getId());
      var val = Soomla.keyValueStorage.getValue(key);
      return (!_.isUndefined(val) && !_.isNull(val)) ? val : -1;
    },
    setLastSeqIdxGiven: function setLastSeqIdxGiven(sequenceReward, idx) {
      var key = this.keyRewardIdxSeqGiven(sequenceReward.getId());
      Soomla.keyValueStorage.setValue(key, idx);
    },


    setTimesGiven: function setTimesGiven(reward, up, notify) {
      notify = notify || _.isUndefined(notify);
      var total = this.getTimesGiven(reward) + (up ? 1 : -1);
      if (total < 0) {
        total = 0;
      }

      var key = this.keyRewardTimesGiven(reward.getId());
      Soomla.keyValueStorage.setValue(key, total);

      if (up) {
        key = this.keyRewardLastGiven(reward.getId());
        Soomla.keyValueStorage.setValue(key, Date.now());
      }

      if (notify) {
        if (up) {
          Soomla.fireSoomlaEvent(CoreConsts.EVENT_REWARD_GIVEN, [reward]);
        } else {
          Soomla.fireSoomlaEvent(CoreConsts.EVENT_REWARD_TAKEN, [reward]);
        }
      }
    },
    keyRewards: function keyRewards(rewardId, postfix) {
      return Soomla.DB_KEY_PRFIX + 'rewards.' + rewardId + '.' + postfix;
    },
    keyRewardIdxSeqGiven: function keyRewardIdxSeqGiven(rewardId) {
      return this.keyRewards(rewardId, "seq.id");
    },
    keyRewardTimesGiven: function keyRewardTimesGiven(rewardId) {
      return this.keyRewards(rewardId, "timesGiven");
    },
    keyRewardLastGiven: function keyRewardLastGiven(rewardId) {
      return this.keyRewards(rewardId, "lastGiven");
    }
  });

  Soomla.rewardStorage = platform.isNativeSupported() ? NativeRewardStorage.create() : BridgelessRewardStorage.create();

  // ------- Store -------- //
  /**
   * VirtualItemStorage
   */
  var VirtualItemStorage = Soomla.VirtualItemStorage = declareClass("VirtualItemStorage", {
    getBalance: function getBalance(item) {
      var itemId = item.itemId;
      var key = this.keyBalance(itemId);
      var val = Soomla.keyValueStorage.getValue(key);

      var balance = (!_.isUndefined(val) && !_.isEmpty(val)) ? parseInt(val) : 0;

      logDebug('the balance for ' + itemId + ' is ' + balance);

      return balance;
    },

    setBalance: function setBalance(item, balance, notify) {
      notify = notify || _.isUndefined(notify);
      var oldBalance = this.getBalance(item);
      if (oldBalance === balance) {
        return balance;
      }

      var itemId = item.itemId;
      var key = this.keyBalance(itemId);

      Soomla.keyValueStorage.setValue(key, balance);

      if (notify) {
        this.postBalanceChangeEvent(item, balance, 0);
      }

      return balance;
    },

    add: function add(item, amount, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;
      var balance = this.getBalance(item);
      if (balance < 0) { /* in case the user "adds" a negative value */
        balance = 0;
        amount = 0;
      }

      var newBalance = balance + amount;
      var key = this.keyBalance(itemId);

      Soomla.keyValueStorage.setValue(key, newBalance);

      if (notify) {
        this.postBalanceChangeEvent(item, newBalance, amount);
      }

      return newBalance;
    },

    remove: function remove(item, amount, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;
      var balance = this.getBalance(item) - amount;
      if (balance < 0) {
        balance = 0;
        amount = 0;
      }

      var key = this.keyBalance(itemId);

      Soomla.keyValueStorage.setValue(key, balance);

      if (notify) {
        this.postBalanceChangeEvent(item, balance, -1 * amount);
      }

      return balance;
    },

    keyBalance: function keyBalance(itemId) {
      logError('OVERRIDE ME!')
    },

    postBalanceChangeEvent: function (item, balance, amountAdded) {
      logError('OVERRIDE ME!')
    }
  });

  /**
   * VirtualCurrencyStorage
   */
  var VirtualCurrencyStorage = Soomla.VirtualCurrencyStorage = declareClass("VirtualCurrencyStorage", {
    keyBalance: function keyBalance(itemId) {
      return this.keyCurrencyBalance(itemId);
    },
    postBalanceChangeEvent: function postBalanceChangeEvent(item, balance, amountAdded) {
      Soomla.fireSoomlaEvent(StoreConsts.EVENT_CURRENCY_BALANCE_CHANGED, [item, balance, amountAdded]);
    },
    keyCurrencyBalance: function keyCurrencyBalance(itemId) {
      return 'currency.' + itemId + '.balance';
    }
  }, VirtualItemStorage);

  /**
   * NativeVirtualCurrencyStorage
   */
  var NativeVirtualCurrencyStorage = Soomla.NativeVirtualCurrencyStorage = declareClass("NativeVirtualCurrencyStorage", {

    getBalance: function getBalance(item) {
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling getBalance with: ' + itemId);
      var retParams = callNative({
        method: 'CCNativeVirtualCurrencyStorage::getBalance',
        itemId: itemId
      });

      return retParams['return'] || 0;
    },

    setBalance: function setBalance(item, balance, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling setBalance with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualCurrencyStorage::setBalance',
        itemId: itemId,
        balance: balance,
        notify: notify
      });

      return retParams['return'] || 0;
    },

    add: function add(item, amount, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling add with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualCurrencyStorage::add',
        itemId: itemId,
        amount: amount,
        notify: notify
      });

      return retParams['return'] || 0;
    },

    remove: function remove(item, amount, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling remove with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualCurrencyStorage::remove',
        itemId: itemId,
        amount: amount,
        notify: notify
      });

      return retParams['return'] || 0;
    }

  }, VirtualCurrencyStorage);

  Soomla.virtualCurrencyStorage = platform.isNativeSupported() ? NativeVirtualCurrencyStorage.create() : VirtualCurrencyStorage.create();

  /**
   * VirtualGoodsStorage
   */
  var VirtualGoodsStorage = Soomla.VirtualGoodsStorage = declareClass("VirtualGoodsStorage", {
    /**
     Removes any upgrade associated with the given `CCVirtualGood`.
     @param good `CCVirtualGood` to remove upgrade from.
     @param notify true will also post event.
     */
    removeUpgrades: function removeUpgrades(good, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = good.itemId;
      var key = this.keyGoodUpgrade(itemId);

      Soomla.keyValueStorage.deleteKeyValue(key);

      if (notify) {
        Soomla.fireSoomlaEvent(StoreConsts.EVENT_GOOD_UPGRADE, [good]);
      }
    },

    /**
     Assigns a specific upgrade to the given virtual good.
     @param good `CCVirtualGood` to remove upgrade from.
     @param upgradeVG the upgrade to assign.
     @param notify true will also post event.
     */
    assignCurrentUpgrade: function assignCurrentUpgrade(good, upgradeVG, notify) {
      notify = notify || _.isUndefined(notify);
      var upgrade = this.getCurrentUpgrade(good);
      if (upgrade && upgrade.itemId === upgradeVG.itemId) {
        return;
      }

      var itemId = good.itemId;
      var key = this.keyGoodUpgrade(itemId);
      var upItemId = upgradeVG.itemId;

      Soomla.keyValueStorage.setValue(key, upItemId);

      if (notify) {
        Soomla.fireSoomlaEvent(StoreConsts.EVENT_GOOD_UPGRADE, [good, upgradeVG]);
      }
    },

    /**
     Retrieves the current upgrade for the given virtual good.
     @param good the virtual good to retrieve upgrade for.
     @return the current upgrade for the given virtual good, or NULL if one
     does not exist
     */
    getCurrentUpgrade: function getCurrentUpgrade(good) {
      var itemId = good.itemId;
      var key = this.keyGoodUpgrade(itemId);

      var upItemId = Soomla.keyValueStorage.getValue(key);

      if (!upItemId) {
        logDebug('You tried to fetch the current upgrade of ' + itemId + ' but there\'s not upgrade to it.');
        return null;
      }

      var item = Soomla.storeInfo.getItemByItemId(upItemId);

      return item || null;
    },

    /**
     Checks the equipping status of the given `CCEquippableVG`.
     @param good The `CCEquippableVG` to check the status for.
     @return boolean true if the good is equipped, false otherwise
     */
    isEquipped: function isEquipped(good) {
      var itemId = good.itemId;
      var key = this.keyGoodEquipped(itemId);
      var val = Soomla.keyValueStorage.getValue(key);

      return !!val;
    },

    /**
     Equips the given `CCEquippableVG`.
     @param good The `CCEquippableVG` to equip.
     @param notify true will also post event.
     @param error Gets A `CCError` for error checking.
     */
    equip: function equip(good, notify) {
      notify = notify || _.isUndefined(notify);
      if (this.isEquipped(good)) {
        return;
      }

      this.equipPriv(good, true, notify);
    },

    /**
     UnEquips the given `CCEquippableVG`.
     @param good The `CCEquippableVG` to unequip.
     @param notify true will also post event.
     @param error Gets A `CCError` for error checking.
     */
    unequip: function unequip(good, notify) {
      notify = notify || _.isUndefined(notify);
      if (!this.isEquipped(good)) {
        return;
      }

      this.equipPriv(good, false, notify);
    },


    keyBalance: function keyBalance(itemId) {
      return this.keyGoodBalance(itemId);
    },

    postBalanceChangeEvent: function postBalanceChangeEvent(item, balance, amountAdded) {
      Soomla.fireSoomlaEvent(StoreConsts.EVENT_GOOD_BALANCE_CHANGED, [item, balance, amountAdded]);
    },

    equipPriv: function equipPriv(good, equip, notify) {
      var itemId = good.itemId;
      var key = this.keyGoodEquipped(itemId);

      if (equip) {
        Soomla.keyValueStorage.setValue(key, 'yes');
        if (notify) {
          Soomla.fireSoomlaEvent(StoreConsts.EVENT_GOOD_EQUIPPED, [good]);
        }
      } else {
        Soomla.keyValueStorage.deleteKeyValue(key);
        if (notify) {
          Soomla.fireSoomlaEvent(StoreConsts.EVENT_GOOD_UNEQUIPPED, [good]);
        }
      }
    },

    keyGoodBalance: function keyGoodBalance(itemId) {
      return 'good.' + itemId + '.balance';
    },

    keyGoodEquipped: function keyGoodEquipped(itemId) {
      return 'good.' + itemId + '.equipped';
    },

    keyGoodUpgrade: function keyGoodUpgrade(itemId) {
      return 'good.' + itemId + '.currentUpgrade';
    }

  }, VirtualItemStorage);

  /**
   Implements the `CCVirtualGoodsStorage` using the bridge to talk
   with the native implementation of VirtualGoodsStorage

   See parent for all functions.
   */
  var NativeVirtualGoodsStorage = Soomla.NativeVirtualGoodsStorage = declareClass("NativeVirtualGoodsStorage", {

    getBalance: function getBalance(item) {
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling getBalance with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualGoodsStorage::getBalance',
        itemId: itemId
      });

      return retParams['return'] || 0;
    },

    setBalance: function setBalance(item, balance, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling setBalance with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualGoodsStorage::setBalance',
        itemId: itemId,
        balance: balance,
        notify: notify
      });

      return retParams['return'] || 0;
    },

    add: function add(item, amount, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling add with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualGoodsStorage::add',
        itemId: itemId,
        amount: amount,
        notify: notify
      });

      return retParams['return'] || 0;
    },

    remove: function remove(item, amount, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = item.itemId;

      logDebug('SOOMLA/COCOS2DX Calling remove with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualGoodsStorage::remove',
        itemId: itemId,
        amount: amount,
        notify: notify
      });

      return retParams['return'] || 0;
    },

    removeUpgrades: function removeUpgrades(good, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = good.itemId;

      logDebug('SOOMLA/COCOS2DX Calling removeUpgrades with: ' + itemId);

      callNative({
        method: 'CCNativeVirtualGoodsStorage::removeUpgrades',
        itemId: itemId,
        notify: notify
      });
    },

    assignCurrentUpgrade: function assignCurrentUpgrade(good, upgradeVG, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = good.itemId;
      var upgradeItemId = upgradeVG.itemId;


      logDebug('SOOMLA/COCOS2DX Calling assignCurrentUpgrade with: ' + itemId);

      callNative({
        method: 'CCNativeVirtualGoodsStorage::assignCurrentUpgrade',
        itemId: itemId,
        upgradeItemId: upgradeItemId,
        notify: notify
      });
    },

    getCurrentUpgrade: function getCurrentUpgrade(good) {
      var itemId = good.itemId;

      logDebug('SOOMLA/COCOS2DX Calling getCurrentUpgrade with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualGoodsStorage::getCurrentUpgrade',
        itemId: itemId
      });

      var retItemId = retParams['return'];

      return retItemId ? Soomla.storeInfo.getItemByItemId(retItemId) : null;
    },

    isEquipped: function isEquipped(good) {
      var itemId = good.itemId;

      logDebug('SOOMLA/COCOS2DX Calling isEquipped with: ' + itemId);

      var retParams = callNative({
        method: 'CCNativeVirtualGoodsStorage::isEquipped',
        itemId: itemId
      });

      return retParams['return'] || false;
    },

    equip: function equip(good, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = good.itemId;

      logDebug('SOOMLA/COCOS2DX Calling equip with: ' + itemId);

      callNative({
        method: 'CCNativeVirtualGoodsStorage::equip',
        itemId: itemId,
        notify: notify
      });
    },

    unequip: function unequip(good, notify) {
      notify = notify || _.isUndefined(notify);
      var itemId = good.itemId;

      logDebug('SOOMLA/COCOS2DX Calling unequip with: ' + itemId);

      callNative({
        method: 'CCNativeVirtualGoodsStorage::unequip',
        itemId: itemId,
        notify: notify
      });
    }
  }, VirtualGoodsStorage);

  Soomla.virtualGoodsStorage = platform.isNativeSupported() ? NativeVirtualGoodsStorage.create() : VirtualGoodsStorage.create();

  /**
   * StoreInfo
   */
  var StoreInfo = Soomla.StoreInfo = declareClass("StoreInfo", {
    KEY_META_STORE_INFO: "meta.storeinfo",

    virtualItems: null,
    purchasableItems: null,
    goodsCategories: null,
    goodsUpgrades: null,
    currencies: null,
    currencyPacks: null,
    goods: null,
    categories: null,

    init: function(storeAssets) {

      Soomla.logDebug('Setting store assets in SoomlaInfo');

      if (!storeAssets){
        Soomla.logDebug('The given store assets can\'t be null!');
        return false;
      }

      var _this = this;

      this.setStoreAssets(storeAssets);

      // At this point we have StoreInfo JSON saved at the local key-value storage. We can just
      // continue by initializing from DB.

      this.initializeFromDB();

      return true;
    },

    setStoreAssets: function (storeAssets) {
      var jsonString = JSON.stringify(storeAssets);
      Soomla.keyValueStorage.setValue(this.KEY_META_STORE_INFO, jsonString);
    },

    initializeFromDB: function () {
      var val = Soomla.keyValueStorage.getValue(this.KEY_META_STORE_INFO);

      if (!val) {
        var message = 'store json is not in DB. Make sure you initialized SoomlaStore with your Store assets. The App will shut down now.';
        logError(message);
        throw message;
      }

      logDebug('the metadata-economy json (from DB) is ' + val);

      var storeAssets = JSON.parse(val);

      this.currencies = _.collect(storeAssets.currencies, function (currency) {
        return Soomla.factory.create(currency);
      });
      this.currencyPacks = _.collect(storeAssets.currencyPacks, function (currencyPack) {
        return Soomla.factory.create(currencyPack);
      });
      if (storeAssets.goods) {
        this.goods = _.collect(_.union(
          storeAssets.goods.singleUse,
          storeAssets.goods.lifetime,
          storeAssets.goods.equippable,
          storeAssets.goods.goodPacks,
          storeAssets.goods.goodUpgrades
        ), function (good) {
          return Soomla.factory.create(good);
        });
      } else {
        this.goods = [];
      }
      this.categories = _.collect(storeAssets.categories, function (category) {
        return Soomla.factory.create(category);
      });


      this.virtualItems = _.transform(
        _.groupBy(
          _.union(this.currencies, this.currencyPacks, this.goods),
          'itemId'),
        function (result, value, key) {
          result[key] = value[0];
        }
      );

      this.purchasableItems = _.transform(
        _.groupBy(
          _.filter(_.union(this.currencyPacks, this.goods),
            function (vi) {
              return vi.purchasableItem && vi.purchasableItem.marketItem;
            }
          ),
          function (vi) {
            return vi.purchasableItem.marketItem.productId;
          }
        ),
        function (result, value, key) {
          result[key] = value[0];
        }
      );

      this.goodsUpgrades = _.groupBy(_.filter(this.goods, {className: 'UpgradeVG'}), 'good_itemId');

      var goodsCategories = this.goodsCategories = {};
      _.each(this.categories, function (category) {
        _.each(category.goods_itemIds, function (itemId) {
          goodsCategories[itemId] = category;
        });
      });
    },

    getItemByItemId: function(itemId) {
      logDebug('Trying to fetch an item with itemId: ' + itemId);

      var item = this.virtualItems[itemId];
      if (!item) {
        logError('Virtual item was not found when searching with itemId=' + itemId);
      }
      return item;
    },
    getPurchasableItemWithProductId: function(productId) {
      logDebug('Trying to fetch a purchasable item with productId: ' + productId);

      var item = this.purchasableItems[productId];
      if (!item) {
        logError('Virtual item was not found when searching with productId=' + itemId);
      }
      return item;
    },
    getCategoryForVirtualGood: function(goodItemId) {
      logDebug('Trying to fetch a category for a good with itemId: ' + goodItemId);

      var category = this.goodsCategories[goodItemId];
      if (!category) {
        logError('Virtual item was not found when searching with goodItemId of category=' + goodItemId);
      }
      return category;
    },
    getFirstUpgradeForVirtualGood: function(goodItemId) {
      logDebug('Trying to fetch first upgrade of a good with itemId: ' + goodItemId);

      var upgrades = this.goodsUpgrades[goodItemId];
      if (!upgrades) {
        return null;
      }

      return _.find(upgrades, function (upgradeVG) {
        return _.isUndefined(upgradeVG.prev_itemId) ||
          _.isNull(upgradeVG.prev_itemId) ||
          _.isEmpty(upgradeVG.prev_itemId);
      });
    },
    getLastUpgradeForVirtualGood: function(goodItemId) {
      logDebug('Trying to fetch last upgrade of a good with itemId: ' + goodItemId);

      var upgrades = this.goodsUpgrades[goodItemId];
      if (!upgrades) {
        return null;
      }

      return _.find(upgrades, function (upgradeVG) {
        return _.isUndefined(upgradeVG.next_itemId) ||
          _.isNull(upgradeVG.next_itemId) ||
          _.isEmpty(upgradeVG.next_itemId);
      });
    },
    getUpgradesForVirtualGood: function(goodItemId) {
      logDebug('Trying to fetch upgrades of a good with itemId: ' + goodItemId);

      return this.goodsUpgrades[goodItemId];
    },

    getVirtualItems: function () {
      return this.virtualItems;
    },

    getPurchasableItems: function () {
      return this.purchasableItems;
    },

    getGoodsCategories: function () {
      return this.goodsCategories;
    },

    getGoodsUpgrades: function () {
      return this.goodsUpgrades;
    },

    getCurrencies: function () {
      return this.currencies;
    },

    getCurrencyPacks: function () {
      return this.currencyPacks;
    },

    getGoods: function () {
      return this.goods;
    },

    getCategories: function () {
      return this.categories;
    },

    saveItem: function (virtualItem, saveToDB) {
      this.replaceVirtualItem(virtualItem);
      if (saveToDB) {
        this.save();
      }
    },
    saveItems: function(virtualItems, saveToDB) {
      if (!virtualItems || virtualItems.length == 0) {
        return;
      }

      _.each(virtualItems, function (vi) {
        this.replaceVirtualItem(vi);
      });

      if (saveToDB) {
        this.save();
      }
    },
    save: function () {
      var assets = Soomla.IStoreAssets.create();
      assets.currencies = this.currencies;
      assets.currencyPacks = this.currencyPacks;

      _.each(this.goods, function (vi) {
        if (vi.className === 'SingleUseVG') {
          assets.goods.singleUse.push(vi);
        } else if (vi.className === 'EquippableVG') {
          assets.goods.equippable.push(vi);
        } else if (vi.className === 'UpgradeVG') {
          assets.goods.goodUpgrades.push(vi);
        } else if (vi.className === 'LifetimeVG') {
          assets.goods.lifetime.push(vi);
        } else if (vi.className === 'SingleUsePackVG') {
          assets.goods.goodPacks.push(vi);
        }
      });
      assets.categories = this.categories;

      var jsonString = JSON.stringify(assets);
      logDebug("saving StoreInfo to DB. json is: " + jsonString);
      Soomla.keyValueStorage.setValue(this.KEY_META_STORE_INFO, jsonString);
    },

    replaceVirtualItem: function(virtualItem) {
      var foundIdx;
      this.virtualItems[virtualItem.itemId] = virtualItem;

      if (virtualItem.className === 'VirtualCurrency') {
        foundIdx = _.findIndex(this.currencies, {itemId: virtualItem.itemId});
        if (foundIdx >= 0) {
          _.slice(this.currencies, foundIdx);
        }
        this.currencies.push(virtualItem);
      }

      if (virtualItem.className === 'VirtualCurrencyPack') {
        if (virtualItem.purchasableItem && virtualItem.purchasableItem.marketItem) {
          this.purchasableItems[virtualItem.purchasableItem.marketItem.productId] = virtualItem;
        }

        foundIdx = _.findIndex(this.currencyPacks, {itemId: virtualItem.itemId});
        if (foundIdx >= 0) {
          _.slice(this.currencyPacks, foundIdx);
        }
        this.currencyPacks.push(virtualItem);
      }

      if (virtualItem.className === 'SingleUseVG' ||
        virtualItem.className === 'EquippableVG' ||
        virtualItem.className === 'UpgradeVG' ||
        virtualItem.className === 'LifetimeVG' ||
        virtualItem.className === 'SingleUsePackVG') {

        if (virtualItem.className === 'UpgradeVG') {
          foundIdx = _.findIndex(this.goodsUpgrades, {itemId: virtualItem.itemId});
          if (foundIdx >= 0) {
            _.slice(this.goodsUpgrades, foundIdx);
          }
          this.goodsUpgrades.push(virtualItem);
        }

        if (virtualItem.purchasableItem && virtualItem.purchasableItem.marketItem) {
          this.purchasableItems[virtualItem.purchasableItem.marketItem.productId] = virtualItem;
        }

        foundIdx = _.findIndex(this.goods, {itemId: virtualItem.itemId});
        if (foundIdx >= 0) {
          _.slice(this.goods, foundIdx);
        }
        this.goods.push(virtualItem);
      }
    }
  });

  var NativeStoreInfo = Soomla.NativeStoreInfo = declareClass("NativeStoreInfo", {
    setStoreAssets: function setStoreAssets(storeAssets) {
      logDebug('pushing CCStoreAssets to StoreInfo on native side');

      callNative({
        method: "CCStoreAssets::init",
        version: storeAssets.version,
        storeAssets: storeAssets
      });

      logDebug('done! (pushing data to StoreAssets on native side)');
    },
    save: function save() {
      StoreInfo.save.apply(this, arguments);

      callNative({
        method: "CCStoreInfo::loadFromDB"
      });
    }
  }, StoreInfo);

  StoreInfo.createShared = function(storeAssets) {
    var ret = platform.isNativeSupported() ? NativeStoreInfo.create() : StoreInfo.create();
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

  /**
   * Dispatch event. Goes through event handlers and calls
   * @param eventName function to call in event handlers
   * @param {...Mixed} params params to pass to the function of event handlers
   */
  Soomla.dispatchEvent = function (eventName) {
    // TODO: Switch all dispatching to this function
    if (arguments.length === 0) {
      logError('dispatchEvent: Wrong arguments number');
      return;
    }
    var functionName = arguments[0];
    var params = [];
    for (var i = 1; i < arguments.length; i++) {
      params.push(arguments[i]);
    }
    logDebug('dispatching: ' + functionName + ' with arguments: ' + dump(params));
    _.forEach(Soomla.eventHandlers, function (eventHandler) {
      if (_.isFunction(eventHandler[functionName])) {
        eventHandler[functionName].apply(eventHandler, params);
      }
    });
  };

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

        Soomla.storeInventory.refreshOnCurrencyBalanceChanged(virtualCurrency, parameters.balance, parameters.amountAdded);

        Soomla.fireSoomlaEvent(methodName, [virtualCurrency, parameters.balance, parameters.amountAdded]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_BALANCE_CHANGED) {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);

        Soomla.storeInventory.refreshOnGoodBalanceChanged(virtualGood, parameters.balance, parameters.amountAdded);

        Soomla.fireSoomlaEvent(methodName, [virtualGood, parameters.balance, parameters.amountAdded]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_EQUIPPED) {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);

        Soomla.storeInventory.refreshOnGoodEquipped(equippableVG);

        Soomla.fireSoomlaEvent(methodName, [equippableVG]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_UNEQUIPPED) {
        var equippableVG = Soomla.storeInfo.getItemByItemId(parameters.itemId);

        Soomla.storeInventory.refreshOnGoodUnEquipped(equippableVG);

        Soomla.fireSoomlaEvent(methodName, [equippableVG]);
      }
      else if (methodName == Soomla.Models.StoreConsts.EVENT_GOOD_UPGRADE) {
        var virtualGood = Soomla.storeInfo.getItemByItemId(parameters.itemId);
        var upgradeVG = Soomla.storeInfo.getItemByItemId(parameters.vguItemId);

        Soomla.storeInventory.refreshOnGoodUpgrade(virtualGood, upgradeVG);

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
        _.forEach(changedComponents, function (component) {
          if (component === 'store') {
            Soomla.storeInfo.initializeFromDB();
          }
        });

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
        _.forEach(changedComponents, function (component) {
          if (component === 'store') {
            Soomla.storeInventory.refreshLocalInventory();
          }
        });
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

  var StoreBridge = Soomla.StoreBridge = declareClass("StoreBridge", {
    init: function () {
      return true;
    },
    applyParams: function applyParams(storeParams) {
    }
  });

  var NativeStoreBridge = Soomla.NativeStoreBridge = declareClass("NativeStoreBridge", {
    init: function () {
      this.bindNative();
      return true;
    },
    applyParams: function applyParams(storeParams) {
      if (platform.isIos()) {
        callNative({
          method: "CCSoomlaStore::setSSV",
          ssv: storeParams.SSV
        });
      }

      if (platform.isAndroid()) {
        callNative({
          method: "CCSoomlaStore::setAndroidPublicKey",
          androidPublicKey: storeParams.androidPublicKey
        });
        callNative({
          method: "CCSoomlaStore::setTestPurchases",
          testPurchases: storeParams.testPurchases
        });
      }
    },

    bindNative: function bindNative() {
      logDebug('Binding to native platform Store bridge...');

      if (!_.isUndefined(window.jsb)) {
        if (platform.isAndroid()) {
          jsb.reflection.callStaticMethod('com/soomla/cocos2dx/store/StoreBridgeBinder', "bind", "()V");
        } else if (platform.isIos()) {
          jsb.reflection.callStaticMethod('StoreBridge', 'initShared');
        } else {
          logError('Unsupported platform: ' + platform.name);
        }
      } else {
        logDebug('Your version of JSB does not support reflection. Do not forget to initialize the bridges on the native sides.');
      }
    }
  }, StoreBridge);

  StoreBridge.initShared = function () {
    var ret = platform.isNativeSupported() ? NativeStoreBridge.create() : StoreBridge.create();
    if (ret.init()) {
      Soomla.storeBridge = ret;
    } else {
      Soomla.storeBridge = null;
    }
  };

  /**
   * SoomlaStore
   */
  var SoomlaStore = Soomla.SoomlaStore = declareClass("SoomlaStore", {
    SOOMLA_AND_PUB_KEY_DEFAULT: "YOUR GOOGLE PLAY PUBLIC KEY",
    initialized: false,
    initialize: function(storeAssets, storeParams) {

      if (this.initialized) {
        var err = "SoomlaStore is already initialized. You can't initialize it twice!";
        Soomla.fireSoomlaEvent(StoreConsts.EVENT_UNEXPECTED_ERROR_IN_STORE, [err, true]);
        logError(err);
        return;
      }

      StoreBridge.initShared();

      logDebug("CCSoomlaStore Initializing...");

      this.loadBillingService();

      StoreInfo.createShared(storeAssets);

      Soomla.storeBridge.applyParams(storeParams);

      if (platform.isIos()) {
        this.refreshMarketItemsDetails();
      } else if (platform.isAndroid()) {
        this.refreshInventory();
      }

      this.initialized = true;
      Soomla.fireSoomlaEvent(StoreConsts.EVENT_SOOMLA_STORE_INITIALIZED, [true]);

      return true;
    },
    buyMarketItem: function(productId, payload) {
      ////===========
      var item = Soomla.storeInfo.getPurchasableItemWithProductId(productId);
      if (!item) {
        return;
      }

      // simulate onMarketPurchaseStarted event
      Soomla.fireSoomlaEvent(StoreConsts.EVENT_MARKET_PURCHASE_STARTED, [item]);

      // in the editor we just give the item... no real market.
      item.give(1);

      // simulate onMarketPurchase event
      Soomla.fireSoomlaEvent(StoreConsts.EVENT_MARKET_PURCHASE, [item, 'fake_token_zyxw9876', payload]);
    },
    restoreTransactions: function() {
    },
    refreshInventory: function() {
    },
    refreshMarketItemsDetails: function() {
    },
    // For iOS only
    transactionsAlreadyRestored: function() {
    },
    // For Android only
    startIabServiceInBg: function() {
    },
    // For Android only
    stopIabServiceInBg: function() {
    },

    loadBillingService: function loadBillingService() {

    }
  });

  /**
   * NativeSoomlaStore
   */
  var NativeSoomlaStore = Soomla.NativeSoomlaStore = declareClass("NativeSoomlaStore", {
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
    refreshMarketItemsDetails: function() {
      callNative({
        method: "CCSoomlaStore::refreshMarketItemsDetails"
      });
    },
    // For iOS only
    transactionsAlreadyRestored: function() {
      var retParams = callNative({
        method: "CCSoomlaStore::transactionsAlreadyRestored"
      });
      return retParams.return;
    },
    // For Android only
    startIabServiceInBg: function() {
      callNative({
        method: "CCSoomlaStore::startIabServiceInBg"
      });
    },
    // For Android only
    stopIabServiceInBg: function() {
      callNative({
        method: "CCSoomlaStore::stopIabServiceInBg"
      });
    },

    loadBillingService: function() {
      callNative({
        method: "CCSoomlaStore::loadBillingService"
      });
    }
  }, SoomlaStore);

  Soomla.soomlaStore = platform.isNativeSupported() ? NativeSoomlaStore.create() : SoomlaStore.create();

  var StoreInventory = Soomla.StoreInventory = declareClass("StoreInventory", {
    mLocalItemBalances: {},
    mLocalUpgrades: {},
    mLocalEquippedGoods: [],
    init: function () {
      return true;
    },
    canAfford: function(itemId) {
      logDebug('Checking can afford: ' + itemId);

      var pvi = Soomla.storeInfo.getItemByItemId(itemId);
      if (pvi) {
        pvi.canAfford(payload);
      } else {
        return false;
      }
    },
    buyItem: function(itemId, payload) {
      logDebug('Buying: ' + itemId);

      var pvi = Soomla.storeInfo.getItemByItemId(itemId);
      if (pvi) {
        pvi.buy(payload);
      }
    },
    getItemBalance: function(itemId) {
      var amount = this.mLocalItemBalances[itemId];
      if (!_.isUndefined(amount) && !_.isNull(amount)) {
        return amount;
      }

      var item = Soomla.storeInfo.getItemByItemId(itemId);
      if (!item) {
        return 0;
      }
      return item.getBalance();
    },
    giveItem: function(itemId, amount) {
      logDebug('Giving: ' + amount + ' pieces of: ' + itemId);

      var item = Soomla.storeInfo.getItemByItemId(itemId);
      if (item) {
        item.give(amount);
      }
    },
    takeItem: function(itemId, amount) {
      logDebug('Taking: ' + amount + ' pieces of: ' + itemId);

      var item = Soomla.storeInfo.getItemByItemId(itemId);
      if (item) {
        item.take(amount);
      }
    },
    equipVirtualGood: function(itemId) {
      logDebug('Equipping: ' + itemId);

      var item = Soomla.storeInfo.getItemByItemId(itemId);
      if (item) {
        item.equip();
      }
    },
    unEquipVirtualGood: function(itemId) {
      logDebug('UnEquipping: ' + itemId);

      var item = Soomla.storeInfo.getItemByItemId(itemId);
      if (item) {
        item.unequip();
      }
    },
    isVirtualGoodEquipped: function(itemId) {
      logDebug('Checking if '  + itemId + ' is equipped');

      var item = Soomla.storeInfo.getItemByItemId(itemId);
      if (item) {
        return Soomla.virtualGoodsStorage.isEquipped(item);
      } else {
        return false;
      }
    },
    getGoodUpgradeLevel: function(goodItemId) {
      logDebug('Checking ' + goodItemId + ' upgrade level');

      var good = Soomla.storeInfo.getItemByItemId(goodItemId);
      if (!good) {
        logError('You tried to get the level of a non-existant virtual good.');
        return 0;
      }
      var upgradeVG = Soomla.virtualGoodsStorage.getCurrentUpgrade(good);
      if (!upgradeVG) {
        return 0; //no upgrade
      }

      var first = Soomla.storeInfo.getFirstUpgradeForVirtualGood(goodItemId);
      var level = 1;
      while (first.itemId !== upgradeVG.itemId) {
        first = Soomla.storeInfo.getItemByItemId(first.next_itemId);
        level++;
      }

      return level;
    },
    getGoodCurrentUpgrade: function(goodItemId) {
      logDebug('Checking ' + goodItemId + ' current upgrade');

      var good = Soomla.storeInfo.getItemByItemId(goodItemId);
      if (!good) {
        return "";
      }

      var upgradeVG = Soomla.virtualGoodsStorage.getCurrentUpgrade(good);
      if (!upgradeVG) {
        return "";
      }
      return upgradeVG.itemId;
    },
    upgradeGood: function(goodItemId) {
      logDebug('Upgrading Good with: ' + goodItemId);
      var good = Soomla.storeInfo.getItemByItemId(goodItemId);
      if (!good) {
        return;
      }

      var upgradeVG = Soomla.virtualGoodsStorage.getCurrentUpgrade(good);

      if (upgradeVG) {
        var nextItemId = upgradeVG.next_itemId;
        if (_.isUndefined(nextItemId) || _.isNull(nextItemId)) {
          return;
        }
        var vgu = Soomla.storeInfo.getItemByItemId(nextItemId);
        if (vgu) {
          vgu.buy("");
        }
      }
      else {
        var first = Soomla.storeInfo.getFirstUpgradeForVirtualGood(goodItemId);
        if (first) {
          first.buy("");
        }
      }
    },
    removeGoodUpgrades: function(goodItemId) {
      logDebug('Removing Good Upgrades for: ' + goodItemId);

      var upgrades = Soomla.storeInfo.getUpgradesForVirtualGood(goodItemId);
      _.forEach(upgrades, function (upgrade) {
        Soomla.virtualGoodsStorage.remove(upgrade, 1, true);
      });

      var good = Soomla.storeInfo.getItemByItemId(goodItemId);
      Soomla.virtualGoodsStorage.removeUpgrades(good);
    },

    refreshLocalInventory: function refreshLocalInventory() {
      this.mLocalItemBalances = {};
      this.mLocalUpgrades = {};
      this.mLocalEquippedGoods = [];

      _.forEach(Soomla.storeInfo.getCurrencies(), function (item) {
        this.mLocalItemBalances[item.itemId] = Soomla.virtualCurrencyStorage.getBalance(item);
      }, this);

      _.forEach(Soomla.storeInfo.getGoods(), function (item) {
        var balance = Soomla.virtualGoodsStorage.getBalance(item);
        this.mLocalItemBalances[item.itemId] = balance;

        var upgrade = Soomla.virtualGoodsStorage.getCurrentUpgrade(item);
        if (upgrade) {
          var upgradeLevel = this.getGoodUpgradeLevel(item.itemId);

          var localUpgrade = {
            itemId: upgrade.itemId,
            level: upgradeLevel
          };
          this.mLocalUpgrades[item.itemId] = localUpgrade;
        }

        if (item.className === 'EquippableVG') {
          if (Soomla.virtualGoodsStorage.isEquipped(item)) {
            this.mLocalEquippedGoods.push(item);
          }
        }

      }, this);
    },

    refreshOnGoodUpgrade: function refreshOnGoodUpgrade(vg, uvg) {
      if (!uvg) {
        delete this.mLocalUpgrades[vg.itemId];
      } else {
        var upgradeLevel = this.getGoodUpgradeLevel(vg.itemId);
        var upgrade = this.mLocalUpgrades[vg.itemId];
        if (upgrade) {
          upgrade.item = uvg.itemId;
          upgrade.level = upgradeLevel;
        } else {
          var localUpgrade = {itemId: uvg.itemId, level: upgradeLevel};
          this.mLocalUpgrades[vg.itemId] = localUpgrade;
        }
      }
    },
    refreshOnGoodEquipped: function refreshOnGoodEquipped(equippable) {
      this.mLocalEquippedGoods.push(equippable.itemId);
    },
    refreshOnGoodUnEquipped: function (equippable) {
      _.pull(this.mLocalEquippedGoods, equippable.itemId);
    },
    refreshOnCurrencyBalanceChanged: function refreshOnCurrencyBalanceChanged(virtualCurrency, balance, amountAdded) {
      this.updateLocalBalance(virtualCurrency.itemId, balance);
    },
    refreshOnGoodBalanceChanged: function refreshOnGoodBalanceChanged(good, balance, amountAdded) {
      this.updateLocalBalance(good.itemId, balance);
    },
    updateLocalBalance: function updateLocalBalance(itemId, balance) {
      this.mLocalItemBalances[itemId] = balance;
    }
  });

  StoreInventory.createShared = function() {
    var ret = StoreInventory.create();
    if (ret.init()) {
      return ret;
    } else {
      return null;
    }
  };

  Soomla.storeInventory = StoreInventory.createShared();

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

    var result;

    if (platform.isNativeSupported()) {
      if (typeof(clean) === 'undefined') {
        jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params));
      }
      else {
        jsonString = Soomla.CCSoomlaNdkBridge.callNative(JSON.stringify(params, removeNulls));
      }
      result = JSON.parse(jsonString);
    } else {
      result = {success: true, 'return': {}};
    }

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
  };

  var logDebug = Soomla.logDebug = function (output) {
    if (Soomla.DEBUG) {
      console.log("DEBUG: " + output);
    }
  };

  var logError = Soomla.logError = function (output) {
    console.log("ERROR: " + output);
  };

  var dumpError = Soomla.dumpError = function (e) {
    return e + " : " + JSON.stringify(e);
  };

  var dump = Soomla.dump = function (obj) {
    return JSON.stringify(obj);
  };

  return Soomla
};
