# AppFocusService

Source: https://developer.repebble.com/docs/c/Foundation/Event_Service/AppFocusService/index.html

Handling app focus The AppFocusService allows developers to be notified when their apps become visible on the screen. Common reasons your app may be running but not be on screen are: it's still in the middle of launching and being revealed by a system animation, or it is being covered by a system window such as a notification. This service is useful for apps that require a high degree of user interactivity, like a game where you'll want to pause when a notification covers your app window. It can be also used for apps that want to sync up an intro animation to the end of the system animation that occurs before your app is visible.

## Function Documentation

void app\_focus\_service\_subscribe\_handlers([AppFocusHandlers](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandlers) handlers)

Subscribe to the focus event service. Once subscribed, the handlers get called every time the app gains or loses focus.

#### Parameters
 handler

Handlers which will be called on will-focus and did-focus events.

#### See Also
[AppFocusHandlers](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandlers)

void app\_focus\_service\_subscribe([AppFocusHandler](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandler) handler)

Subscribe to the focus event service. Once subscribed, the handler gets called every time the app focus changes.

##### Notes

Calling this function is equivalent to

```
app\_focus\_service\_subscribe\_handlers((AppFocusHandlers){.will\_focus = handler,});
```

 

Out focus events are triggered when a modal window is about to open and cover the app.

In focus events are triggered when a modal window which is covering the app is about to close.

#### Parameters
 handler

A callback to be called on will-focus events.

void app\_focus\_service\_unsubscribe(void)

Unsubscribe from the focus event service. Once unsubscribed, the previously registered handlers will no longer be called.

## Data Structure Documentation

struct AppFocusHandlers

There are two different focus events which take place when transitioning to and from an app being in focus. Below is an example of when these events will occur: 1) The app is launched. Once the system animation to the app has completed and the app is completely in focus, the did\_focus handler is called with in\_focus set to true. 2) A notification comes in and the animation to show the notification starts. The will\_focus handler is called with in\_focus set to false. 3) The animation completes and the notification is in focus, with the app being completely covered. The did\_focus hander is called with in\_focus set to false. 4) The notification is dismissed and the animation to return to the app starts. The will\_focus handler is called with in\_focus set to true. 5) The animation completes and the app is in focus. The did\_focus handler is called with in\_focus set to true.

#### Data Fields
[AppFocusHandler](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandler) will\_focus

Handler which will be called right before an app will lose or gain focus.

##### Notes

This will be called with in\_focus set to true when a window which is covering the app is about to close and return focus to the app.

This will be called with in\_focus set to false when a window which will cover the app is about to open, causing the app to lose focus.

[AppFocusHandler](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandler) did\_focus

Handler which will be called when an animation finished which has put the app into focus or taken the app out of focus.

##### Notes

This will be called with in\_focus set to true when a window which was covering the app has closed and the app has gained focus.

This will be called with in\_focus set to false when a window has opened which is now covering the app, causing the app to lose focus.

## Typedef Documentation

 typedef void(\* AppFocusHandler)(bool in\_focus) 

Callback type for focus events.

#### Parameters
 in\_focus

True if the app is gaining focus, false otherwise.
