# ActionMenu

Source: https://developer.repebble.com/docs/c/User_Interface/Window/ActionMenu/index.html

## Function Documentation

char \* action\_menu\_item\_get\_label(const ActionMenuItem \* item)

Getter for the label of a given ActionMenuItem.

#### Parameters
 item

the ActionMenuItem of interest

#### Returns

a pointer to the string label. NULL if invalid.

void \* action\_menu\_item\_get\_action\_data(const ActionMenuItem \* item)

Getter for the action\_data pointer of a given ActionMenuitem.

#### Parameters
 item

the ActionMenuItem of interest

#### Returns

a pointer to the data. NULL if invalid.

#### See Also
[action\_menu\_level\_add\_action](/docs/c/User_Interface/Window/ActionMenu/#action_menu_level_add_action)

ActionMenuLevel \* action\_menu\_level\_create([uint16\_t](/docs/c/Standard_C/#uint16_t) max\_items)

Create a new action menu level with storage allocated for a given number of items.

##### Notes

levels are freed alongside the whole hierarchy so no destroy API is provided.

by default, levels are using ActionMenuLevelDisplayModeWide. Use [action\_menu\_level\_set\_display\_mode](/docs/c/User_Interface/Window/ActionMenu/#action_menu_level_set_display_mode) to change it.

#### Parameters
 max\_items

the max number of items that will be displayed at that level

#### See Also
[action\_menu\_hierarchy\_destroy](/docs/c/User_Interface/Window/ActionMenu/#action_menu_hierarchy_destroy)

void action\_menu\_level\_set\_display\_mode(ActionMenuLevel \* level, [ActionMenuLevelDisplayMode](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuLevelDisplayMode) display\_mode)

Set the action menu display mode.

#### Parameters
 level

The ActionMenuLevel whose display mode you want to change

 display\_mode

The display mode for the action menu (3 vs. 1 item per row)

ActionMenuItem \* action\_menu\_level\_add\_action(ActionMenuLevel \* level, const char \* label, [ActionMenuPerformActionCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuPerformActionCb) cb, void \* action\_data)

Add an action to an ActionLevel.

#### Parameters
 level

the level to add the action to

 label

the text to display for the action in the menu

 cb

the callback that will be triggered when this action is actuated

 action\_data

data to pass to the callback for this action

#### Returns

a reference to the new ActionMenuItem on success, NULL if the level is full

ActionMenuItem \* action\_menu\_level\_add\_child(ActionMenuLevel \* level, ActionMenuLevel \* child, const char \* label)

Add a child to this ActionMenuLevel.

#### Parameters
 level

the parent level

 child

the child level

 label

the text to display in the action menu for this level

#### Returns

a reference to the new ActionMenuItem on success, NULL if the level is full

void action\_menu\_hierarchy\_destroy(const ActionMenuLevel \* root, [ActionMenuEachItemCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuEachItemCb) each\_cb, void \* context)

Destroy a hierarchy of ActionMenuLevels.

##### Notes

Typical implementations will cleanup memory allocated for the item label/data associated with each item in the callback

Hierarchy is traversed in post-order. In other words, all children items are freed before their parent is freed.

#### Parameters
 root

the root level in the hierarchy

 each\_cb

a callback to call on every ActionMenuItem in every level

 context

a context pointer to pass to each\_cb on invocation

void \* action\_menu\_get\_context(ActionMenu \* action\_menu)

Get the context pointer this ActionMenu was created with.

#### Parameters
 action\_menu

A pointer to an ActionMenu

#### Returns

the context pointer initially provided in the [ActionMenuConfig](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuConfig). NULL if none exists.

ActionMenuLevel \* action\_menu\_get\_root\_level(ActionMenu \* action\_menu)

Get the root level of an ActionMenu.

#### Parameters
 action\_menu

the ActionMenu you want to know about

#### Returns

a pointer to the root ActionMenuLevel for the given ActionMenu, NULL if invalid

ActionMenu \* action\_menu\_open([ActionMenuConfig](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuConfig) \* config)

Open a new ActionMenu. The ActionMenu acts much like a window. It fills the whole screen and handles clicks.

#### Parameters
 config

the configuration info for this new ActionMenu

#### Returns

the new ActionMenu

void action\_menu\_freeze(ActionMenu \* action\_menu)

Freeze the ActionMenu. The ActionMenu will no longer respond to user input.

##### Note

this API should be used when waiting for asynchronous operation.

#### Parameters
 action\_menu

the ActionMenu

void action\_menu\_unfreeze(ActionMenu \* action\_menu)

Unfreeze the ActionMenu previously frozen with [action\_menu\_freeze](/docs/c/User_Interface/Window/ActionMenu/#action_menu_freeze).

#### Parameters
 action\_menu

the ActionMenu to unfreeze

void action\_menu\_set\_result\_window(ActionMenu \* action\_menu, Window \* result\_window)

Set the result window for an ActionMenu. The result window will be shown when the ActionMenu closes.

##### Note

repeated call will result in only the last call to be applied, i.e. only one result window is ever set

#### Parameters
 action\_menu

the ActionMenu

 result\_window

the window to insert, pass NULL to remove the current result window

void action\_menu\_close(ActionMenu \* action\_menu, bool animated)

Close the ActionMenu, whether it is frozen or not.

##### Note

this API can be used on a frozen ActionMenu once the data required to build the result window has been received and the result window has been set

#### Parameters
 action\_menu

the ActionMenu to close

 animated

whether or not show a close animation

## Data Structure Documentation

struct ActionMenuConfig

Configuration struct for the ActionMenu.

#### Data Fields
const ActionMenuLevel \* root\_level

the root level of the ActionMenu

void \* context

a context pointer which will be accessbile when actions are performed

struct [ActionMenuConfig](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuConfig) colors[ActionMenuDidCloseCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuDidCloseCb) will\_close

Called immediately before the ActionMenu closes.

[ActionMenuDidCloseCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuDidCloseCb) did\_close

a callback used to cleanup memory after the menu has closed

ActionMenuAlign align

## Enum Documentation

enum ActionMenuAlign

#### Enumerators
ActionMenuAlignTopActionMenuAlignCenter

enum ActionMenuLevelDisplayMode

enum value that controls whether menu items are displayed in a grid (similarly to the emoji replies) or in a single column (reminiscent of [MenuLayer](/docs/c/User_Interface/Layers/MenuLayer/))

#### Enumerators
ActionMenuLevelDisplayModeWide

Each item gets its own row.

ActionMenuLevelDisplayModeThin

Grid view: multiple items per row.

## Typedef Documentation

 typedef struct ActionMenuItem ActionMenuItem

 typedef struct ActionMenuLevel ActionMenuLevel

 typedef struct ActionMenu ActionMenu

 typedef void(\* ActionMenuDidCloseCb)(ActionMenu \*menu, const ActionMenuItem \*performed\_action, void \*context) 

Callback executed after the ActionMenu has closed, so memory may be freed.

#### Parameters
 root\_level

the root level passed to the ActionMenu

 performed\_action

the ActionMenuItem for the action that was performed, NULL if the ActionMenu is closing without an action being selected by the user

 context

the context passed to the ActionMenu

 typedef void(\* ActionMenuPerformActionCb)(ActionMenu \*action\_menu, const ActionMenuItem \*action, void \*context) 

Callback executed when a given action is selected.

##### Note

the action menu is closed immediately after an action is performed, unless it is frozen in the [ActionMenuPerformActionCb](/docs/c/User_Interface/Window/ActionMenu/#ActionMenuPerformActionCb)

#### Parameters
 action\_menu

the action menu currently on screen

 action

the action that was triggered

 context

the context passed to the action menu

 typedef void(\* ActionMenuEachItemCb)(const ActionMenuItem \*item, void \*context) 

Callback invoked for each item in an action menu hierarchy.

#### Parameters
 item

the current action menu item

 a

caller-provided context callback
