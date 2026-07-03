# SimpleMenuLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/SimpleMenuLayer/index.html

Wrapper around [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/), that uses static data to display a list menu.

![](/assets/images/docs/c/aplite/simple_menu_layer.png) ![](/assets/images/docs/c/aplite/simple_menu_layer.png) ![](/assets/images/docs/c/aplite/simple_menu_layer.png) ![](/assets/images/docs/c/aplite/simple_menu_layer.png) ![](/assets/images/docs/c/aplite/simple_menu_layer.png)

## Function Documentation

SimpleMenuLayer \* simple\_menu\_layer\_create([GRect](/docs/c/Graphics/Graphics_Types/#GRect) frame, Window \* window, const [SimpleMenuSection](/docs/c/User_Interface/Layers/SimpleMenuLayer/#SimpleMenuSection) \* sections, int32\_t num\_sections, void \* callback\_context)

Creates a new SimpleMenuLayer on the heap and initializes it. It also sets the internal click configuration provider onto given window.

##### Notes

The `sections` array is not deep-copied and can therefore not be stack allocated, but needs to be backed by long-lived storage.

This function does not add the menu's layer to the window.

#### Parameters
 frame

The frame at which to initialize the menu

 window

The window onto which to set the click configuration provider

 sections

Array with sections that need to be displayed in the menu

 num\_sections

The number of sections in the `sections` array.

 callback\_context

Pointer to application specific data, that is passed into the callbacks.

#### Returns

A pointer to the SimpleMenuLayer. `NULL` if the SimpleMenuLayer could not be created

void simple\_menu\_layer\_destroy(SimpleMenuLayer \* menu\_layer)

Destroys a SimpleMenuLayer previously created by simple\_menu\_layer\_create.

Layer \* simple\_menu\_layer\_get\_layer(const SimpleMenuLayer \* simple\_menu)

Gets the "root" Layer of the simple menu layer, which is the parent for the sub-layers used for its implementation.

#### Parameters
 simple\_menu

Pointer to the SimpleMenuLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the menu layer.

int simple\_menu\_layer\_get\_selected\_index(const SimpleMenuLayer \* simple\_menu)

Gets the row index of the currently selection menu item.

#### Parameters
 simple\_menu

The SimpleMenuLayer for which to get the current selected row index.

void simple\_menu\_layer\_set\_selected\_index(SimpleMenuLayer \* simple\_menu, int32\_t index, bool animated)

Selects the item in the first section at given row index.

#### Parameters
 simple\_menu

The SimpleMenuLayer for which to change the selection

 index

The row index of the item to select

 animated

Supply `true` to animate changing the selection, or `false` to change the selection instantly.

MenuLayer \* simple\_menu\_layer\_get\_menu\_layer(SimpleMenuLayer \* simple\_menu)

#### Parameters
 simple\_menu

The [SimpleMenuLayer](/docs/c/User_Interface/Layers/SimpleMenuLayer/) to get the [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/) from.

#### Returns

The [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/).

## Data Structure Documentation

struct SimpleMenuItem

Data structure containing the information of a menu item.

#### Data Fields
const char \* title

The title of the menu item. Required.

const char \* subtitle

The subtitle of the menu item. Optional, leave `NULL` if unused.

GBitmap \* icon

The icon of the menu item. Optional, leave `NULL` if unused.

[SimpleMenuLayerSelectCallback](/docs/c/User_Interface/Layers/SimpleMenuLayer/#SimpleMenuLayerSelectCallback) callback

The callback that needs to be called upon a click on the SELECT button. Optional, leave `NULL` if unused.

struct SimpleMenuSection

Data structure containing the information of a menu section.

#### Data Fields
const char \* title

Title of the section. Optional, leave `NULL` if unused.

const [SimpleMenuItem](/docs/c/User_Interface/Layers/SimpleMenuLayer/#SimpleMenuItem) \* items

Array of items in the section.

[uint32\_t](/docs/c/Standard_C/#uint32_t) num\_items

Number of items in the `.items` array.

## Typedef Documentation

 typedef struct SimpleMenuLayer SimpleMenuLayer

 typedef void(\* SimpleMenuLayerSelectCallback)(int index, void \*context) 

Function signature for the callback to handle the event that a user hits the SELECT button.

#### Parameters
 index

The row index of the item

 context

The callback context
