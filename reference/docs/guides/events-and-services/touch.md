# Touch

Source: https://developer.repebble.com/guides/events-and-services/touch/

On hardware platforms with a touchscreen, the `TouchService` lets an app receive touchdown, lift-off, and position updates as the user moves their finger across the display. This is the same low-level event stream the system itself uses, so apps can build their own gesture recognizers, draggable UI, or free-form input on top of it.

## Detecting Touch Support

A touchscreen is not present on every platform, and even when it is the user can disable touch input from _Settings → Display → Touch_. Apps should call[`touch_service_is_enabled()`](/docs/c/Foundation/Event_Service/TouchService/#touch_service_is_enabled "touch\_service\_is\_enabled") before relying on touch input - typically from the window's `appear` handler - and gracefully degrade if it returns `false`:

```
static void main\_window\_appear(Window \*window) {if (!touch\_service\_is\_enabled()) {text\_layer\_set\_text(s\_status\_layer,"Touch is disabled. Enable it in Settings → Display.");return;}// Touch is available - subscribe and start the touch UItouch\_service\_subscribe(touch\_handler, NULL);}
```

`touch_service_is_enabled()` returns `false` on platforms without a touchscreen, so a single check covers both the "no hardware" and the "user-disabled" cases.

For code that should only be compiled on platforms with a touchscreen at all - for example, an entire gesture recognizer that has no equivalent on button-only hardware - use the `PBL_TOUCH` compile-time define:

```
#if defined(PBL\_TOUCH)touch\_service\_subscribe(touch\_handler, NULL);#else// Fall back to a button-based UIwindow\_set\_click\_config\_provider(window, click\_config\_provider);#endif
```

## Subscribing to Touch Events

Touch events are delivered through a [`TouchServiceHandler`](/docs/c/Foundation/Event_Service/TouchService/#TouchServiceHandler "TouchServiceHandler") callback. The handler receives a pointer to a [`TouchEvent`](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent "TouchEvent") describing what happened, and the context pointer that was registered with the subscription:

```
static void touch\_handler(const TouchEvent \*event, void \*context) {switch (event-\>type) {case TouchEvent\_Touchdown:APP\_LOG(APP\_LOG\_LEVEL\_DEBUG, "Touchdown at %d, %d", event-\>x, event-\>y);break;case TouchEvent\_PositionUpdate:APP\_LOG(APP\_LOG\_LEVEL\_DEBUG, "Move to %d, %d", event-\>x, event-\>y);break;case TouchEvent\_Liftoff:APP\_LOG(APP\_LOG\_LEVEL\_DEBUG, "Liftoff at %d, %d", event-\>x, event-\>y);break;}}
```

Subscribing to the service powers on the touch sensor; it stays on as long as at least one app is subscribed and is automatically disabled again once the last subscriber drops:

```
// Receive touch eventstouch\_service\_subscribe(touch\_handler, NULL);
```

When the app no longer needs touch input - for example, when its main window disappears - unsubscribe:

```
touch\_service\_unsubscribe();
```

## Event Types

The [`TouchEventType`](/docs/c/Foundation/Event_Service/TouchService/#TouchEventType "TouchEventType") field on each event identifies what the user just did:

| Event Type | Description |
| --- | --- |
| [`TouchEvent_Touchdown`](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent_Touchdown "TouchEvent\_Touchdown") | The user has just placed a finger on the screen. `x` and `y` are the initial contact position. |
| [`TouchEvent_PositionUpdate`](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent_PositionUpdate "TouchEvent\_PositionUpdate") | An existing touch has moved. `x` and `y` are the new position. |
| [`TouchEvent_Liftoff`](/docs/c/Foundation/Event_Service/TouchService/#TouchEvent_Liftoff "TouchEvent\_Liftoff") | The user has just lifted their finger. `x` and `y` are the final position before lift-off. |

Coordinates are in the same screen-relative pixel space used everywhere else in the UI, so they can be passed directly to drawing routines or compared against [`Layer`](/docs/c/User_Interface/Layers/#Layer "Layer") bounds.

A typical touch interaction starts with a single `TouchEvent_Touchdown`, followed by zero or more `TouchEvent_PositionUpdate` events as the finger moves, and ends with a single `TouchEvent_Liftoff`. Apps that want to track gestures (taps, drags, swipes) generally store the touchdown position, watch the position updates, and decide what happened on lift-off.

## Backlight Behavior

Each touch event triggers the backlight the same way a wrist flick or button press would - the light flashes on for the system auto-off interval and then fades out. This keeps the screen lit naturally while the user is actively interacting, without keeping the backlight pinned on between taps. There is no need to call the [Light API](/guides/events-and-services/light.md) manually to achieve this; subsequent touches will re-trigger the backlight on their own.

## Battery Considerations

The touch sensor is an active component and draws power continuously while enabled. Subscribe to the touch service only while the app's UI actually needs touch input, and unsubscribe as soon as it doesn't - for example, in the window `disappear` handler, or when navigating to a screen that uses buttons instead.
