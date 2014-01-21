/**
 * Created by vedi on 1/21/14.
 */

Soomla = new function () {
  var declareClass = function (ClassName, fields) {
    var Clazz = function () {
      return _.defaults({
        modelName: ClassName
      }, fields);
    };
    Clazz.create = function (values) {
      return _.defaults(_.pick(values, _.keys(fields)),  Clazz());
    };

    return Clazz;
  };

  var Soomla = {};

  /**
   * VirtualItem
   */
  var VirtualItem = Soomla.VirtualItem = declareClass("VirtualItem", {
    name: "",
    description: "",
    itemId: null
  });

  /**
   * VirtualCategory
   */
  var VirtualCategory = Soomla.VirtualCategory = declareClass("VirtualCategory", {
    name: "",
    goodItemIds: null
  });

  /**
   * MarketItem
   */
  var MarketItem = Soomla.MarketItem = declareClass("MarketItem", {
    productId: null,
    mConsumable: null,
    mPrice: null
  });
  MarketItem.Consumable = {
    NONCONSUMABLE: "NONCONSUMABLE",
    CONSUMABLE: "CONSUMABLE",
    SUBSCRIPTION: "SUBSCRIPTION"
  };

  /**
   * PurchasableVirtualItem
   */
  var PurchasableVirtualItem = Soomla.PurchasableVirtualItem = declareClass("PurchasableVirtualItem", {
    purchaseType: null
  });

  /**
   * NonConsumableItem
   */
  var NonConsumableItem = Soomla.NonConsumableItem = declareClass("NonConsumableItem", {

  });

  /**
   * VirtualCurrency
   */
  var VirtualCurrency = Soomla.VirtualCurrency = declareClass("VirtualCurrency", {
  });

  /**
   * VirtualCurrencyPack
   */
  var VirtualCurrencyPack = Soomla.VirtualCurrencyPack = declareClass("v", {
    currencyAmount: 0,
    currencyItemId: null
  });

  /**
   * VirtualGood
   */
  var VirtualGood = Soomla.VirtualGood = declareClass("VirtualGood", {
  });

  /**
   * LifetimeVG
   */
  var LifetimeVG = Soomla.LifetimeVG = declareClass("LifetimeVG", {
  });

  /**
   * EquippableVG
   */
  var EquippableVG = Soomla.EquippableVG = declareClass("EquippableVG", {
    equippingModel: null
  });
  EquippableVG.EquippingModel = {
    LOCAL: 0,
    CATEGORY: 1,
    GLOBAL: 2
  };

  /**
   * SingleUseVG
   */
  var SingleUseVG = Soomla.SingleUseVG = declareClass("SingleUseVG", {
  });
  var SingleUseVG = function () {
    return _.extend({
      modelName: "SingleUseVG"
    }, VirtualGood());
  };

  /**
   * SingleUsePackVG
   */
  var SingleUsePackVG = Soomla.SingleUsePackVG = declareClass("SingleUsePackVG", {
    goodItemId: null,
    goodAmount: null
  });

  /**
   * UpgradeVG
   */
  var UpgradeVG = Soomla.UpgradeVG = declareClass("UpgradeVG", {
    goodItemId: null,
    prevItemId: null,
    nextItemId: null
  });

  return Soomla
};

