# Buttons

Source: https://developer.repebble.com/guides/events-and-services/buttons/

Button [`Clicks`](/docs/c/User_Interface/Clicks/ "Clicks") are the primary input method on Pebble. All Pebble watches come with the same buttons available, shown in the diagram below for Pebble Time:

![button-layout](/assets/images/guides/sensors-and-input/button-layout.png)

These buttons are used in a logical fashion throughout the system:

- Back - Navigates back one [`Window`](/docs/c/User_Interface/Window/ "Window") until the watchface is reached.

- Up - Navigates to the previous item in a list, or opens the past timeline when pressed from the watchface.

- Select - Opens the app launcher from the watchface, accepts a selected option or list item, or launches the next [`Window`](/docs/c/User_Interface/Window/ "Window").

- Down - Navigates to the next item in a list, or opens the future timeline when pressed from the watchface.

Developers are highly encouraged to follow these patterns when using button clicks in their watchapps, since users will already have an idea of what each button will do to a reasonable degree, thus avoiding the need for lengthy usage instructions for each app. Watchapps that wish to use each button for a specific action should use the [`ActionBarLayer`](/docs/c/User_Interface/Layers/ActionBarLayer/ "ActionBarLayer") or [`ActionMenu`](/docs/c/User_Interface/Window/ActionMenu/ "ActionMenu") to give hints about what each button will do.

## Listening for Button Clicks

Button clicks are received via a subscription to one of the types of button click events listed below. Each [`Window`](/docs/c/User_Interface/Window/ "Window") that wishes to receive button click events must provide a [`ClickConfigProvider`](/docs/c/User_Interface/Clicks/#ClickConfigProvider "ClickConfigProvider") that performs these subscriptions.

The first step is to create the [`ClickConfigProvider`](/docs/c/User_Interface/Clicks/#ClickConfigProvider "ClickConfigProvider") function:

```
static void click\_config\_provider(void \*context) {// Subcribe to button click events here}
```

The second step is to register the [`ClickConfigProvider`](/docs/c/User_Interface/Clicks/#ClickConfigProvider "ClickConfigProvider") with the current[`Window`](/docs/c/User_Interface/Window/ "Window"), typically after [`window_create()`](/docs/c/User_Interface/Window/#window_create "window\_create"):

```
// Use this provider to add button click subscriptionswindow\_set\_click\_config\_provider(window, click\_config\_provider);
```

The final step is to write a [`ClickHandler`](/docs/c/User_Interface/Clicks/#ClickHandler "ClickHandler") function for each different type of event subscription required by the watchapp. An example for a single click event is shown below:

```
static void select\_click\_handler(ClickRecognizerRef recognizer, void \*context) {// A single click has just occured}
```

## Types of Click Events

There are five types of button click events that apps subscribe to, enabling virtually any combination of up/down/click events to be utilized in a watchapp. The usage of each of these is explained below:

### Single Clicks

Most apps will use this type of click event, which occurs whenever the button specified is pressed and then immediately released. Use[`window_single_click_subscribe()`](/docs/c/User_Interface/Window/#window_single_click_subscribe "window\_single\_click\_subscribe") from a [`ClickConfigProvider`](/docs/c/User_Interface/Clicks/#ClickConfigProvider "ClickConfigProvider") function, supplying the [`ButtonId`](/docs/c/User_Interface/Clicks/#ButtonId "ButtonId") value for the chosen button and the name of the[`ClickHandler`](/docs/c/User_Interface/Clicks/#ClickHandler "ClickHandler") that will receive the events:

```
static void click\_config\_provider(void \*context) {ButtonId id = BUTTON\_ID\_SELECT;// The Select buttonwindow\_single\_click\_subscribe(id, select\_click\_handler);}
```

### Single Repeating Clicks

Similar to the single click event, the single repeating click event allows repeating events to be received at a specific interval if the chosen button is held down for a longer period of time. This makes the task of scrolling through many list items or incrementing a value significantly easier for the user, and uses fewer button clicks.

```
static void click\_config\_provider(void \*context) {ButtonId id = BUTTON\_ID\_DOWN;// The Down buttonuint16\_t repeat\_interval\_ms = 200;// Fire every 200 ms while held downwindow\_single\_repeating\_click\_subscribe(id, repeat\_interval\_ms,down\_repeating\_click\_handler);}
```

After an initial press (but not release) of the button `id` subscribed to, the callback will be called repeatedly with an interval of `repeat_interval_ms`until it is then released.

Developers can determine if the button is still held down after the first callback by using [`click_recognizer_is_repeating()`](/docs/c/User_Interface/Clicks/#click_recognizer_is_repeating "click\_recognizer\_is\_repeating"), as well as get the number of callbacks counted so far with [`click_number_of_clicks_counted()`](/docs/c/User_Interface/Clicks/#click_number_of_clicks_counted "click\_number\_of\_clicks\_counted"):

```
static void down\_repeating\_click\_handler(ClickRecognizerRef recognizer,void \*context) {// Is the button still held down?bool is\_repeating = click\_recognizer\_is\_repeating(recognizer);// How many callbacks have been recorded so far?uint8\_t click\_count = click\_number\_of\_clicks\_counted(recognizer);}
```

> Single click and single repeating click subscriptions conflict, and cannot be registered for the same button.

### Multiple Clicks

A multi click event will call the [`ClickHandler`](/docs/c/User_Interface/Clicks/#ClickHandler "ClickHandler") after a specified number of single clicks has been recorded. A good example of usage is to detect a double or triple click gesture:

```
static void click\_config\_provider(void \*context) {ButtonId id = BUTTON\_ID\_SELECT;// The Select buttonuint8\_t min\_clicks = 2;// Fire after at least two clicksuint8\_t max\_clicks = 3;// Don't fire after three clicksuint16\_t timeout = 300;// Wait 300ms before firingbool last\_click\_only = true;// Fire only after the last clickwindow\_multi\_click\_subscribe(id, min\_clicks, max\_clicks, timeout,last\_click\_only, multi\_select\_click\_handler);}
```

Similar to the single repeating click event, the [`ClickRecognizerRef`](/docs/c/User_Interface/Clicks/#ClickRecognizerRef "ClickRecognizerRef") can be used to determine how many clicks triggered this multi click event using[`click_number_of_clicks_counted()`](/docs/c/User_Interface/Clicks/#click_number_of_clicks_counted "click\_number\_of\_clicks\_counted").

### Long Clicks

A long click event is fired after a button is held down for the specified amount of time. The event also allows two [`ClickHandler`](/docs/c/User_Interface/Clicks/#ClickHandler "ClickHandler")s to be registered - one for when the button is pressed, and another for when the button is released. Only one of these is required.

```
static void click\_config\_provider(void \*context) {ButtonId id = BUTTON\_ID\_SELECT;// The select buttonuint16\_t delay\_ms = 500;// Minimum time pressed to firewindow\_long\_click\_subscribe(id, delay\_ms, long\_down\_click\_handler,long\_up\_click\_handler);}
```

### Raw Clicks

The last type of button click subcsription is used to track raw button click events. Like the long click event, two [`ClickHandler`](/docs/c/User_Interface/Clicks/#ClickHandler "ClickHandler")s may be supplied to receive each of the pressed and depressed events.

```
static void click\_config\_provider(void \*context) {ButtonId id = BUTTON\_ID\_SELECT;// The select buttonwindow\_raw\_click\_subscribe(id, raw\_down\_click\_handler, raw\_up\_click\_handler,NULL);}
```

> The last parameter is an optional pointer to a context object to be passed to the callback, and is set to `NULL` if not used.
