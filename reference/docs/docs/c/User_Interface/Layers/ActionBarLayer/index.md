# ActionBarLayer

Source: https://developer.repebble.com/docs/c/User_Interface/Layers/ActionBarLayer/index.html

Vertical, bar-shaped control widget on the right edge of the window

![](/assets/images/docs/c/aplite/action_bar_layer.png) ![](/assets/images/docs/c/aplite/action_bar_layer.png) ![](/assets/images/docs/c/aplite/action_bar_layer.png) ![](/assets/images/docs/c/aplite/action_bar_layer.png) ![](/assets/images/docs/c/aplite/action_bar_layer.png)

ActionBarLayer is a Layer that displays a bar on the right edge of the window. The bar can contain up to 3 icons, each corresponding with one of the buttons on the right side of the watch. The purpose of each icon is to provide a hint (feed-forward) to what action a click on the respective button will cause.

The action bar is useful when there are a few (up to 3) main actions that are desirable to be able to take quickly, literally with one press of a button.

### More actions

If there are more than 3 actions the user might want to take:

- Try assigning the top and bottom icons of the action bar to the two most immediate actions and use the middle icon to push a Window with a MenuLayer with less immediate actions.

- Secondary actions that are not vital, can be "hidden" under a long click. Try to group similar actions to one button. For example, in a Music app, a single click on the top button is tied to the action to jump to the previous track. Holding that same button means seek backwards.

### Directionality mapping

When the top and bottom buttons are used to control navigating through a (potentially virtual, non-visible) list of items, follow this guideline:

- Tie the top button to the action that goes to the _previous_ item in the list, for example "jump to previous track" in a Music app.

- Tie the bottom button to the action that goes to the _next_ item in the list, for example "jump to next track" in a Music app.

### Geometry

- The action bar's width varies per platform. 30px on most displays, 34px on Emery and Gabbro, and 40px on Chalk. Use the [ACTION\_BAR\_WIDTH](/docs/c/User_Interface/Layers/ActionBarLayer/#ACTION_BAR_WIDTH) define.

- Icons should not be wider than 28 pixels, or taller than 18 pixels. It is recommended to use a size of around 15 x 15 pixels for the "visual core" of the icon, and extending or contracting where needed. 

The code example below shows how to do the initial setup of the action bar in a window's `.load` handler. Configuring the button actions is similar to the process when using [window\_set\_click\_config\_provider()](/docs/c/User_Interface/Window/#window_set_click_config_provider). See [Clicks](/docs/c/User_Interface/Clicks/) for more information.

```
ActionBarLayer \*action\_bar;// The implementation of my\_next\_click\_handler and my\_previous\_click\_handler// is omitted for the sake of brevity. See the Clicks reference docs.void click\_config\_provider(void \*context) {window\_single\_click\_subscribe(BUTTON\_ID\_DOWN, (ClickHandler) my\_next\_click\_handler);window\_single\_click\_subscribe(BUTTON\_ID\_UP, (ClickHandler) my\_previous\_click\_handler);}void window\_load(Window \*window) {...// Initialize the action bar:action\_bar = action\_bar\_layer\_create();// Associate the action bar with the window:action\_bar\_layer\_add\_to\_window(action\_bar, window);// Set the click config provider:action\_bar\_layer\_set\_click\_config\_provider(action\_bar,click\_config\_provider);// Set the icons:// The loading of the icons is omitted for brevity... See gbitmap\_create\_with\_resource()action\_bar\_layer\_set\_icon\_animated(action\_bar, BUTTON\_ID\_UP, my\_icon\_previous, true);action\_bar\_layer\_set\_icon\_animated(action\_bar, BUTTON\_ID\_DOWN, my\_icon\_next, true);}
```

## Function Documentation

ActionBarLayer \* action\_bar\_layer\_create(void)

Creates a new ActionBarLayer on the heap and initalizes it with the default values.

- Background color: [GColorBlack](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlack)

- No click configuration provider (`NULL`)

- No icons

- Not added to / associated with any window, thus not catching any button input yet. 

#### Returns

A pointer to the ActionBarLayer. `NULL` if the ActionBarLayer could not be created

void action\_bar\_layer\_destroy(ActionBarLayer \* action\_bar\_layer)

Destroys a ActionBarLayer previously created by action\_bar\_layer\_create.

Layer \* action\_bar\_layer\_get\_layer(ActionBarLayer \* action\_bar\_layer)

Gets the "root" Layer of the action bar layer, which is the parent for the sub- layers used for its implementation.

#### Parameters
 action\_bar\_layer

Pointer to the ActionBarLayer for which to get the "root" Layer

#### Returns

The "root" Layer of the action bar layer.

void action\_bar\_layer\_set\_context(ActionBarLayer \* action\_bar, void \* context)

Sets the context parameter, which will be passed in to [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) callbacks and the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) callback of the action bar.

##### Note

By default, a pointer to the action bar itself is passed in, if the context has not been set or if it has been set to `NULL`.

#### Parameters
 action\_bar

The action bar for which to assign the new context

 context

The new context

#### See Also
[action\_bar\_layer\_set\_click\_config\_provider()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_click_config_provider)  
[Clicks](/docs/c/User_Interface/Clicks/)

void action\_bar\_layer\_set\_click\_config\_provider(ActionBarLayer \* action\_bar, [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) click\_config\_provider)

Sets the click configuration provider callback of the action bar. In this callback your application can associate handlers to the different types of click events for each of the buttons, see [Clicks](/docs/c/User_Interface/Clicks/).

##### Notes

If the action bar had already been added to a window and the window is currently on-screen, the click configuration provider will be called before this function returns. Otherwise, it will be called by the system when the window becomes on-screen.

The `.raw` handlers cannot be used without breaking the automatic highlighting of the segment of the action bar that for which a button is

#### Parameters
 action\_bar

The action bar for which to assign a new click configuration provider

 click\_config\_provider

The new click configuration provider

#### See Also
[action\_bar\_layer\_set\_icon()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon)

void action\_bar\_layer\_set\_icon(ActionBarLayer \* action\_bar, [ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, const GBitmap \* icon)

Sets an action bar icon onto one of the 3 slots as identified by `button_id`. Only BUTTON\_ID\_UP, BUTTON\_ID\_SELECT and BUTTON\_ID\_DOWN can be used. The transition will not be animated. Whenever an icon is set, the click configuration provider will be called, to give the application the opportunity to reconfigure the button interaction.

#### Parameters
 action\_bar

The action bar for which to set the new icon

 button\_id

The identifier of the button for which to set the icon

 icon

Pointer to the GBitmap icon

#### See Also
[action\_bar\_layer\_set\_icon\_animated()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon_animated)  
[action\_bar\_layer\_set\_icon\_press\_animation()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon_press_animation)  
[action\_bar\_layer\_set\_click\_config\_provider()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_click_config_provider)

void action\_bar\_layer\_clear\_icon(ActionBarLayer \* action\_bar, [ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id)

Convenience function to clear out an existing icon. All it does is call `action_bar_layer_set_icon(action_bar, button_id, NULL)`

#### Parameters
 action\_bar

The action bar for which to clear an icon

 button\_id

The identifier of the button for which to clear the icon

#### See Also
[action\_bar\_layer\_set\_icon()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon)

void action\_bar\_layer\_add\_to\_window(ActionBarLayer \* action\_bar, struct Window \* window)

Adds the action bar's layer on top of the window's root layer. It also adjusts the layout of the action bar to match the geometry of the window it gets added to. Lastly, it calls [window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) on the window to set it up to work with the internal callback and raw click handlers of the action bar, to enable the highlighting of the section of the action bar when the user presses a button.

##### Notes

After this call, do not use [window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) with the window that the action bar has been added to (this would de-associate the action bar's click config provider and context). Instead use [action\_bar\_layer\_set\_click\_config\_provider()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_click_config_provider) and [action\_bar\_layer\_set\_context()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_context) to register the click configuration provider to configure the buttons actions.

It is advised to call this is in the window's `.load` or `.appear` handler. Make sure to call [action\_bar\_layer\_remove\_from\_window()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_remove_from_window) in the window's `.unload` or `.disappear` handler.

Adding additional layers to the window's root layer after this calll can occlude the action bar.

#### Parameters
 action\_bar

The action bar to associate with the window

 window

The window with which the action bar is to be associated

void action\_bar\_layer\_remove\_from\_window(ActionBarLayer \* action\_bar)

Removes the action bar from the window and unconfigures the window's click configuration provider. `NULL` is set as the window's new click config provider and also as its callback context. If it has not been added to a window before, this function is a no-op.

#### Parameters
 action\_bar

The action bar to de-associate from its current window

void action\_bar\_layer\_set\_background\_color(ActionBarLayer \* action\_bar, GColor background\_color)

Sets the background color of the action bar. Defaults to [GColorBlack](/docs/c/Graphics/Graphics_Types/Color_Definitions/#GColorBlack). The action bar's layer is automatically marked dirty.

#### Parameters
 action\_bar

The action bar of which to set the background color

 background\_color

The new background color

void action\_bar\_layer\_set\_icon\_animated(ActionBarLayer \* action\_bar, [ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, const GBitmap \* icon, bool animated)

Sets an action bar icon onto one of the 3 slots as identified by `button_id`. Only BUTTON\_ID\_UP, BUTTON\_ID\_SELECT and BUTTON\_ID\_DOWN can be used. Optionally, if `animated` is `true`, the transition will be animated. Whenever an icon is set, the click configuration provider will be called, to give the application the opportunity to reconfigure the button interaction.

#### Parameters
 action\_bar

The action bar for which to set the new icon

 button\_id

The identifier of the button for which to set the icon

 icon

Pointer to the GBitmap icon

 animated

True = animate the transition, False = do not animate the transition

#### See Also
[action\_bar\_layer\_set\_icon()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon)  
[action\_bar\_layer\_set\_icon\_press\_animation()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon_press_animation)  
[action\_bar\_layer\_set\_click\_config\_provider()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_click_config_provider)

void action\_bar\_layer\_set\_icon\_press\_animation(ActionBarLayer \* action\_bar, [ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, ActionBarLayerIconPressAnimation animation)

Sets the animation to use while a button is pressed on an ActionBarLayer. By default we use ActionBarLayerIconPressAnimationMoveLeft.

#### Parameters
 action\_bar

The action bar for which to set the press animation

 button\_id

The button for which to set the press animation

 animation

The animation to use.

#### See Also
[action\_bar\_layer\_set\_icon\_animated()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_icon_animated)  
[action\_bar\_layer\_set\_click\_config\_provider()](/docs/c/User_Interface/Layers/ActionBarLayer/#action_bar_layer_set_click_config_provider)

## Enum Documentation

enum ActionBarLayerIconPressAnimation

#### Enumerators
ActionBarLayerIconPressAnimationNoneActionBarLayerIconPressAnimationMoveLeftActionBarLayerIconPressAnimationMoveUpActionBarLayerIconPressAnimationMoveRightActionBarLayerIconPressAnimationMoveDown

## Typedef Documentation

 typedef struct ActionBarLayer ActionBarLayer

## Macro Definition Documentation

#define ACTION\_BAR\_WIDTH [\_ACTION\_BAR\_WIDTH](/docs/c/User_Interface/Layers/ActionBarLayer/#_ACTION_BAR_WIDTH)(PBL\_PLATFORM\_TYPE\_CURRENT)

The width of the action bar in pixels.

- [SDK 3](javascript:void(0);)
- [SDK 4](javascript:void(0);)
- [SDK 4.9+](javascript:void(0);)

#define \_ACTION\_BAR\_WIDTH ( plat)

The width of the action bar in pixels, for all platforms.

#define \_ACTION\_BAR\_WIDTH ( plat)

The width of the action bar in pixels, for all platforms.

#define \_ACTION\_BAR\_WIDTH ( plat)

The width of the action bar in pixels, for all platforms.

#define NUM\_ACTION\_BAR\_ITEMS 3

The maximum number of action bar items.
