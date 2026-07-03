# App

Source: https://developer.repebble.com/docs/c/Foundation/App/index.html

App entry point and event loop.

App is a module that provides you with an event loop for your Pebble app. All interaction between Pebble apps and the underlying Pebble OS takes place through an event loop. Before calling the [app\_event\_loop()](/docs/c/Foundation/App/#app_event_loop) function, you subscribe to event services and implement event handlers. Each handler receives specific types of Events dispatched throughout the life of the Pebble watchapp.

The [app\_event\_loop()](/docs/c/Foundation/App/#app_event_loop) function takes care of both waiting for new events to become available on the watchapp event bus and routing new events to the appropriate handler. [Event Service](/docs/c/Foundation/Event_Service/) allows an app to directly register for different types of events. This function will block until the watchapp is ready to exit, and should be placed in the app's main() function.

A watchapp typically configures and uses the [app\_event\_loop()](/docs/c/Foundation/App/#app_event_loop) as follows:

```
int main(void) {// do set up here// Enter the main event loop. This will block until the app is ready to exit.app\_event\_loop();// do clean up here}
```

## Function Documentation

void app\_event\_loop(void)

The event loop for C apps, to be used in app's main(). Will block until the app is ready to exit.
