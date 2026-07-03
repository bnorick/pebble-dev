# Clicks

Source: https://developer.repebble.com/docs/c/User_Interface/Clicks/index.html

Handling button click interactions

Each Pebble window handles Pebble's buttons while it is displayed. Raw button down and button up events are transformed into click events that can be transferred to your app:

- Single-click. Detects a single click, that is, a button down event followed by a button up event. It also offers hold-to-repeat functionality (repeated click).

- Multi-click. Detects double-clicking, triple-clicking and other arbitrary click counts. It can fire its event handler on all of the matched clicks, or just the last.

- Long-click. Detects long clicks, that is, press-and-hold.

- Raw. Simply forwards the raw button events. It is provided as a way to use both the higher level "clicks" processing and the raw button events at the same time.

To receive click events when a window is displayed, you must register a [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) for this window with [window\_set\_click\_config\_provider()](/docs/c/User_Interface/Window/#window_set_click_config_provider). Your [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) will be called every time the window becomes visible with one context argument. By default this context is a pointer to the window but you can change this with [window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context).

In your [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) you call the [window\_single\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_click_subscribe), [window\_single\_repeating\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_repeating_click_subscribe), [window\_multi\_click\_subscribe()](/docs/c/User_Interface/Window/#window_multi_click_subscribe), [window\_long\_click\_subscribe()](/docs/c/User_Interface/Window/#window_long_click_subscribe) and [window\_raw\_click\_subscribe()](/docs/c/User_Interface/Window/#window_raw_click_subscribe) functions to register a handler for each event you wish to receive.

For convenience, click handlers are provided with a [ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) and a user-specified context.

The [ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) can be used in combination with [click\_number\_of\_clicks\_counted()](/docs/c/User_Interface/Clicks/#click_number_of_clicks_counted), [click\_recognizer\_get\_button\_id()](/docs/c/User_Interface/Clicks/#click_recognizer_get_button_id) and [click\_recognizer\_is\_repeating()](/docs/c/User_Interface/Clicks/#click_recognizer_is_repeating) to get more information about the click. This is useful if you want different buttons or event types to share the same handler.

The user-specified context is the context of your [ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider) (see above). By default it points to the window. You can override it for all handlers with [window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) or for a specific button with [window\_set\_click\_context()](/docs/c/User_Interface/Window/#window_set_click_context).

### User interaction in watchfaces

Watchfaces cannot use the buttons to interact with the user. Instead, you can use the [AccelerometerService](/docs/c/Foundation/Event_Service/AccelerometerService/).

### About the Back button

By default, the Back button will always pop to the previous window on the [Window Stack](/docs/c/User_Interface/Window_Stack/) (and leave the app if the current window is the only window). You can override the default back button behavior with [window\_single\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_click_subscribe) and [window\_multi\_click\_subscribe()](/docs/c/User_Interface/Window/#window_multi_click_subscribe) but you cannot set a repeating, long or raw click handler on the back button because a long press will always terminate the app and return to the main menu.

### Usage example

First associate a click config provider callback with your window:

```
void app\_init(void) {...window\_set\_click\_config\_provider(&window, (ClickConfigProvider) config\_provider);...}
```

 Then in the callback, you set your desired configuration for each button: 

```
void config\_provider(Window \*window) { // single click / repeat-on-hold config:window\_single\_click\_subscribe(BUTTON\_ID\_DOWN, down\_single\_click\_handler);window\_single\_repeating\_click\_subscribe(BUTTON\_ID\_SELECT, 1000, select\_single\_click\_handler);// multi click config:window\_multi\_click\_subscribe(BUTTON\_ID\_SELECT, 2, 10, 0, true, select\_multi\_click\_handler);// long click config:window\_long\_click\_subscribe(BUTTON\_ID\_SELECT, 700, select\_long\_click\_handler, select\_long\_click\_release\_handler);}
```

 Now you implement the handlers for each click you've subscribed to and set up: 

```
void down\_single\_click\_handler(ClickRecognizerRef recognizer, void \*context) {... called on single click ...Window \*window = (Window \*)context;}void select\_single\_click\_handler(ClickRecognizerRef recognizer, void \*context) {... called on single click, and every 1000ms of being held ...Window \*window = (Window \*)context;}void select\_multi\_click\_handler(ClickRecognizerRef recognizer, void \*context) {... called for multi-clicks ...Window \*window = (Window \*)context;const uint16\_t count = click\_number\_of\_clicks\_counted(recognizer);}void select\_long\_click\_handler(ClickRecognizerRef recognizer, void \*context) {... called on long click start ...Window \*window = (Window \*)context;}void select\_long\_click\_release\_handler(ClickRecognizerRef recognizer, void \*context) {... called when long click is released ...Window \*window = (Window \*)context;}
```

### See also

Refer to the

[User Interface Layers chapter in the Pebble Developer Guides](https://developer.getpebble.com/guides/pebble-apps/display-and-animations/layers/)
 (chapter "Clicks") for a conceptual overview of clicks and relevant code examples. 
## Function Documentation

uint8\_t click\_number\_of\_clicks\_counted([ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) recognizer)

Gets the click count. You can use this inside a click handler implementation to get the click count for multi\_click and (repeated) click events.

#### Parameters
 recognizer

The click recognizer for which to get the click count

#### Returns

The number of consecutive clicks, and for auto-repeating the number of repetitions.

[ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) click\_recognizer\_get\_button\_id([ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) recognizer)

Gets the button identifier. You can use this inside a click handler implementation to get the button id for the click event.

#### Parameters
 recognizer

The click recognizer for which to get the button id that caused the click event

#### Returns

the [ButtonId](/docs/c/User_Interface/Clicks/#ButtonId) of the click recognizer

bool click\_recognizer\_is\_repeating([ClickRecognizerRef](/docs/c/User_Interface/Clicks/#ClickRecognizerRef) recognizer)

Is this a repeating click. You can use this inside a click handler implementation to find out whether this is a repeating click or not.

#### Parameters
 recognizer

The click recognizer for which to find out whether this is a repeating click.

#### Returns

true if this is a repeating click.

## Enum Documentation

enum ButtonId

Button ID values.

click\_recognizer\_get\_button\_id()

#### Enumerators
BUTTON\_ID\_BACK

Back button.

BUTTON\_ID\_UP

Up button.

BUTTON\_ID\_SELECT

Select (middle) button.

BUTTON\_ID\_DOWN

Down button.

NUM\_BUTTONS

Total number of buttons.

## Typedef Documentation

 typedef void \* ClickRecognizerRef

Reference to opaque click recognizer When a [ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler) callback is called, the recognizer that fired the handler is passed in.

#### See Also
[ClickHandler](/docs/c/User_Interface/Clicks/#ClickHandler)  
[click\_number\_of\_clicks\_counted()](/docs/c/User_Interface/Clicks/#click_number_of_clicks_counted)  
[click\_recognizer\_get\_button\_id()](/docs/c/User_Interface/Clicks/#click_recognizer_get_button_id)  
[click\_recognizer\_is\_repeating()](/docs/c/User_Interface/Clicks/#click_recognizer_is_repeating)

 typedef void(\* ClickHandler)(ClickRecognizerRef recognizer, void \*context) 

Function signature of the callback that handles a recognized click pattern.

#### Parameters
 recognizer

The click recognizer that detected a "click" pattern

 context

Pointer to application specified data (see [window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context) and [window\_set\_click\_context()](/docs/c/User_Interface/Window/#window_set_click_context)). This defaults to the window.

#### See Also
[ClickConfigProvider](/docs/c/User_Interface/Clicks/#ClickConfigProvider)

 typedef void(\* ClickConfigProvider)(void \*context) 

This callback is called every time the window becomes visible (and when you call [window\_set\_click\_config\_provider()](/docs/c/User_Interface/Window/#window_set_click_config_provider) if the window is already visible).

Subscribe to click events using [window\_single\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_click_subscribe) [window\_single\_repeating\_click\_subscribe()](/docs/c/User_Interface/Window/#window_single_repeating_click_subscribe) [window\_multi\_click\_subscribe()](/docs/c/User_Interface/Window/#window_multi_click_subscribe) [window\_long\_click\_subscribe()](/docs/c/User_Interface/Window/#window_long_click_subscribe) [window\_raw\_click\_subscribe()](/docs/c/User_Interface/Window/#window_raw_click_subscribe) These subscriptions will get used by the click recognizers of each of the 4 buttons.

#### Parameters
 context

Pointer to application specific data (see [window\_set\_click\_config\_provider\_with\_context()](/docs/c/User_Interface/Window/#window_set_click_config_provider_with_context)).
