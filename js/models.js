/**
 * Created by vedi on 1/21/14.
 */

Soomla = new function () {
  var declareClass = function (ClassName, fields, parentClass) {
    var Clazz = function () {
      return _.extend(parentClass ? parentClass() : {}, fields ? fields : {}, {
        modelName: ClassName
      });
    };
    Clazz.create = function (values) {
      return _.defaults(values ? _.omit(values, "modelName") : {}, Clazz());
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
  }, VirtualItem);

  /**
   * NonConsumableItem
   */
  var NonConsumableItem = Soomla.NonConsumableItem = declareClass("NonConsumableItem", {

  }, PurchasableVirtualItem);

  /**
   * VirtualCurrency
   */
  var VirtualCurrency = Soomla.VirtualCurrency = declareClass("VirtualCurrency", {
  }, VirtualItem);

  /**
   * VirtualCurrencyPack
   */
  var VirtualCurrencyPack = Soomla.VirtualCurrencyPack = declareClass("v", {
    currencyAmount: 0,
    currencyItemId: null
  }, PurchasableVirtualItem);

  /**
   * VirtualGood
   */
  var VirtualGood = Soomla.VirtualGood = declareClass("VirtualGood", {
  }, PurchasableVirtualItem);

  /**
   * LifetimeVG
   */
  var LifetimeVG = Soomla.LifetimeVG = declareClass("LifetimeVG", {
  }, VirtualGood);

  /**
   * EquippableVG
   */
  var EquippableVG = Soomla.EquippableVG = declareClass("EquippableVG", {
    equippingModel: null
  }, LifetimeVG);
  EquippableVG.EquippingModel = {
    LOCAL: 0,
    CATEGORY: 1,
    GLOBAL: 2
  };

  /**
   * SingleUseVG
   */
  var SingleUseVG = Soomla.SingleUseVG = declareClass("SingleUseVG", {
  }, VirtualGood);
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
  }, VirtualGood);

  /**
   * UpgradeVG
   */
  var UpgradeVG = Soomla.UpgradeVG = declareClass("UpgradeVG", {
    goodItemId: null,
    prevItemId: null,
    nextItemId: null
  }, VirtualGood);

  return Soomla
};

