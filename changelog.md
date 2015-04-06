### v4.5.0 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/cocos2dx-v2-v4.4.1...cocos2dx-v2-v4.5.0)

**BREAKING API VERSION**

* Features
  * Replacing event handlers with custom events dispatched through Cocos2d-x facilities
  * (JSB) Replacing current event handlers with more user-friendly event handlers
  * Adding more information from Android in Market Purchase event (see inline documentation)

### v4.4.1 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/cocos2dx-v2-v4.4.0...cocos2dx-v2-v4.4.1)

* Changes
  * Changing iOS bridge compilation and resulting header location
  * (JSB) adding Soomla Query to JS
  * Making project v2.2.x compatible

### v4.4.0 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/cocos2dx-v2-v4.3.4...cocos2dx-v2-v4.4.0)

**BREAKING API VERSION**

* Features
  * Better integration process for Store module (see README for instructions)

### v4.3.4 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/cocos2dx-v2-v4.3.3...cocos2dx-v2-v4.3.4)

* Changes
  * (JSB) Updated initialization in highway

### v4.3.3 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/cocos2dx-v2-v4.3.2...cocos2dx-v2-v4.3.3)


* Changes
  * Updating Amazon plugin (v2.0.1)

### v4.3.2 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/cocos2dx-v2-v4.3.1...cocos2dx-v2-v4.3.2)

* Features
  * Adding market refresh failed event  
  * (JSB) BREAKING!!! only developers must now initialize CoreService with custom secret before initializing other modules
  * (JSB) adding market items refresh failed event

* Changes
  * Removing save to DB from market refresh
  * Fixes from updates submodules
  * (JSB) removing saving items in market items refreshed (done in native now)

### v4.3.1 [view commit logs](https://github.com/soomla/cocos2dx-store/compare/cocos2dx-v2-v4.3.0...cocos2dx-v2-v4.3.1)

* Features
  * Added canAfford functionality
  * Fixing [issue #153](https://github.com/soomla/cocos2dx-store/issues/153) on GitHub

### v4.3.0

***Important***: there are some breaking changes. Read the changes carefully.

* New Features
* Work Without a Device! the code can work on other platforms (without in-app purchases testing)
* New local inventory that keeps all balances in memory so you don't need to go to the native DB. Saves JNI calls.
