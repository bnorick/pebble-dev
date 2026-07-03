# Window

Source: https://developer.repebble.com/docs/c/User_Interface/Window/index.html

The basic building block of the user interface

Windows are the top-level elements in the UI hierarchy and the basic building blocks for a Pebble UI. A single window is always displayed at a time on Pebble, with the exception of when animating from one window to the other, which, in that case, is managed by the window stack. You can stack windows on top of each other, but only the topmost window will be visible.

Users wearing a Pebble typically interact with the content and media displayed in a window, clicking and pressing buttons on the watch, depending on what they see and wish to respond to in a window.

Windows serve to display a hierarchy of layers on the screen and handle user input. When a window is visible, its root Layer (and all its child layers) are drawn onto the screen automatically.

You need a window, which always fills the entire screen, to display images, text, and graphics in your Pebble app. A layer by itself doesn’t display on Pebble; it must be in the current window’s layer hierarchy to be visible.

The Window Stack serves as the global manager of what window is presented and makes sure that input events are forwarded to the topmost window.

Refer to the

[User Interface Layers chapter in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/display-and-animations/layers/)
 (chapter "Window") for a conceptual overview of Window, the Window Stack and relevant code examples. 
## Modules

#### [ActionMenu](/docs/c/User_Interface/Window/ActionMenu/)

&nbsp;

#### [NumberWindow](/docs/c/User_Interface/Window/NumberWindow/)

A ready-made Window prompting the user to pick a number

## Function Documentation

Window \* window\_create(void)

Creates a new Window on the heap and initalizes it with the default values.

- Background color : `GColorWhite`

- Root layer's `update_proc` : function that fills the window's background using `background_color`.

- `click_config_provider` : `NULL`

- `window_handlers` : all `NULL`

#### Returns

A pointer to the window. `NULL` if the window could not be created

void window\_destroy(Window \* window)

Destroys a Window previously created by window\_create.

void window\_set\_click\_config\_provider(Window \* window, [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) click\_config\_provider)

Sets the click configuration provider callback function on the window. This will automatically setup the input handlers of the window as well to use the click recognizer subsystem.

#### Parameters
 window

The window for which to set the click config provider

 click\_config\_provider

The callback that will be called to configure the click recognizers with the window

#### See Also
[Clicks](/docs/c/User_Interface/Clicks/)  
[ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider)

void window\_set\_click\_config\_provider\_with\_context(Window \* window, [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) click\_config\_provider, void \* context)

Same as [window\_set\_click\_config\_provider()](/docs/c/User_Interface/Window/#window_set_click_config_provider), but will assign a custom context pointer (instead of the window pointer) that will be passed into the [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) click event handlers.

#### Parameters
 window

The window for which to set the click config provider

 click\_config\_provider

The callback that will be called to configure the click recognizers with the window

 context

Pointer to application specific data that will be passed to the click configuration provider callback (defaults to the window).

#### See Also
[Clicks](/docs/c/User_Interface/Clicks/)  
[window\_set\_click\_config\_provider](/docs/c/User_Interface/Window/#window_set_click_config_provider)

[ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) window\_get\_click\_config\_provider(const Window \* window)

Gets the current click configuration provider of the window.

#### Parameters
 window

The window for which to get the click config provider

void \* window\_get\_click\_config\_context(Window \* window)

Gets the current click configuration provider context of the window.

#### Parameters
 window

The window for which to get the click config provider context

void window\_set\_window\_handlers(Window \* window, [WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers) handlers)

Sets the window handlers of the window. These handlers get called e.g. when the user enters or leaves the window.

#### Parameters
 window

The window for which to set the window handlers

 handlers

The handlers for the specified window

#### See Also
[WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers)

struct Layer \* window\_get\_root\_layer(const Window \* window)

Gets the root Layer of the window. The root layer is the layer at the bottom of the layer hierarchy for this window. It is the window's "canvas" if you will. By default, the root layer only draws a solid fill with the window's background color.

#### Parameters
 window

The window for which to get the root layer

#### Returns

The window's root layer

void window\_set\_background\_color(Window \* window, GColor background\_color)

Sets the background color of the window, which is drawn automatically by the root layer of the window.

#### Parameters
 window

The window for which to set the background color

 background\_color

The new background color

#### See Also
[window\_get\_root\_layer()](/docs/c/User_Interface/Window/#window_get_root_layer)

bool window\_is\_loaded(Window \* window)

Gets whether the window has been loaded. If a window is loaded, its `.load` handler has been called (and the `.unload` handler has not been called since).

#### Parameters
 window

The window to query its loaded status

#### Returns

true if the window is currently loaded or false if not.

#### See Also
[WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers)

void window\_set\_user\_data(Window \* window, void \* data)

Sets a pointer to developer-supplied data that the window uses, to provide a means to access the data at later times in one of the window event handlers.

#### Parameters
 window

The window for which to set the user data

 data

A pointer to user data.

#### See Also
[window\_get\_user\_data](/docs/c/User_Interface/Window/#window_get_user_data)

void \* window\_get\_user\_data(const Window \* window)

Gets the pointer to developer-supplied data that was previously set using [window\_set\_user\_data()](/docs/c/User_Interface/Window/#window_set_user_data).

#### Parameters
 window

The window for which to get the user data

#### See Also
[window\_set\_user\_data](/docs/c/User_Interface/Window/#window_set_user_data)

void window\_single\_click\_subscribe([ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) handler)

Subscribe to single click events.

##### Notes

Must be called from the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider).

[window\_single\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_click_subscribe) and [window\_single\_repeating\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_repeating_click_subscribe) conflict, and cannot both be used on the same button.

When there is a multi\_click and/or long\_click setup, there will be a delay before the single click

#### Parameters
 button\_id

The button events to subscribe to.

 handler

The [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) to fire on this event. handler will get fired. On the other hand, when there is no multi\_click nor long\_click setup, the single click handler will fire directly on button down.

#### See Also
[ButtonId](/docs/c/User_Interface/Clicks/#ButtonId)  
[Clicks](/docs/c/User_Interface/Clicks/)  
[window\_single\_repeating\_click\_subscribe](/docs/c/User_Interface/Window/#window_single_repeating_click_subscribe)

void window\_single\_repeating\_click\_subscribe([ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, [uint16\_t](/docs/c/Standard_C/#uint16_t) repeat\_interval\_ms, [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) handler)

Subscribe to single click event, with a repeat interval. A single click is detected every time "repeat\_interval\_ms" has been reached.

##### Notes

Must be called from the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider).

[window\_single\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_click_subscribe) and [window\_single\_repeating\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_repeating_click_subscribe) conflict, and cannot both be used on the same button.

The back button cannot be overridden with a repeating click.

#### Parameters
 button\_id

The button events to subscribe to.

 repeat\_interval\_ms

When holding down, how many milliseconds before the handler is fired again. A value of 0ms means "no repeat timer". The minimum is 30ms, and values below will be disregarded. If there is a long-click handler subscribed on this button, `repeat_interval_ms` will not be used.

 handler

The [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) to fire on this event.

#### See Also
[window\_single\_click\_subscribe](/docs/c/User_Interface/Window/#window_single_click_subscribe)

void window\_multi\_click\_subscribe([ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, uint8\_t min\_clicks, uint8\_t max\_clicks, [uint16\_t](/docs/c/Standard_C/#uint16_t) timeout, bool last\_click\_only, [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) handler)

Subscribe to multi click events.

##### Note

Must be called from the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider).

#### Parameters
 button\_id

The button events to subscribe to.

 min\_clicks

Minimum number of clicks before handler is fired. Defaults to 2.

 max\_clicks

Maximum number of clicks after which the click counter is reset. A value of 0 means use "min" also as "max".

 timeout

The delay after which a sequence of clicks is considered finished, and the click counter is reset. A value of 0 means to use the system default 300ms.

 last\_click\_only

Defaults to false. When true, only the handler for the last multi-click is called.

 handler

The [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) to fire on this event. Fired for multi-clicks, as "filtered" by the `last_click_only`, `min`, and `max` parameters.

void window\_long\_click\_subscribe([ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, [uint16\_t](/docs/c/Standard_C/#uint16_t) delay\_ms, [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) down\_handler, [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) up\_handler)

Subscribe to long click events.

##### Notes

Must be called from the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider).

The back button cannot be overridden with a long click.

#### Parameters
 button\_id

The button events to subscribe to.

 delay\_ms

Milliseconds after which "handler" is fired. A value of 0 means to use the system default 500ms.

 down\_handler

The [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) to fire as soon as the button has been held for `delay_ms`. This may be NULL to have no down handler.

 up\_handler

The [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) to fire on the release of a long click. This may be NULL to have no up handler.

void window\_raw\_click\_subscribe([ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) down\_handler, [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) up\_handler, void \* context)

Subscribe to raw click events.

##### Notes

Must be called from within the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider).

The back button cannot be overridden with a raw click.

#### Parameters
 button\_id

The button events to subscribe to.

 down\_handler

The [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) to fire as soon as the button has been pressed. This may be NULL to have no down handler.

 up\_handler

The [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) to fire on the release of the button. This may be NULL to have no up handler.

 context

If this context is not NULL, it will override the general context.

void window\_set\_click\_context([ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) button\_id, void \* context)

Set the context that will be passed to handlers for the given button's events. By default the context passed to handlers is equal to the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) context (defaults to the window).

##### Note

Must be called from within the [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider).

#### Parameters
 button\_id

The button to set the context for.

 context

Set the context that will be passed to handlers for the given button's events.

## Data Structure Documentation

struct WindowHandlers

[WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers) These handlers are called by the [Window Stack](/docs/c/User_Interface/Window_Stack/) as windows get pushed on / popped. All these handlers use [WindowHandler](/docs/c/User_Interface/Window/#WindowHandler) as their function signature.

#### Data Fields
[WindowHandler](/docs/c/User_Interface/Window/#WindowHandler) load

Called when the window is pushed to the screen when it's not loaded. This is a good moment to do the layout of the window.

[WindowHandler](/docs/c/User_Interface/Window/#WindowHandler) appear

Called when the window comes on the screen (again). E.g. when second-top-most window gets revealed (again) after popping the top-most window, but also when the window is pushed for the first time. This is a good moment to start timers related to the window, or reset the UI, etc.

[WindowHandler](/docs/c/User_Interface/Window/#WindowHandler) disappear

Called when the window leaves the screen, e.g. when another window is pushed, or this window is popped. Good moment to stop timers related to the window.

[WindowHandler](/docs/c/User_Interface/Window/#WindowHandler) unload

Called when the window is deinited, but could be used in the future to free resources bound to windows that are not on screen.

#### See Also
[window\_set\_window\_handlers()](/docs/c/User_Interface/Window/#window_set_window_handlers)  
[Window Stack](/docs/c/User_Interface/Window_Stack/)

## Typedef Documentation

 typedef struct Window Window

 typedef void(\* WindowHandler)(struct Window \*window) 

Function signature for a handler that deals with transition events of a window.

#### See Also
[WindowHandlers](/docs/c/User_Interface/Window/#WindowHandlers)  
[window\_set\_window\_handlers()](/docs/c/User_Interface/Window/#window_set_window_handlers)
