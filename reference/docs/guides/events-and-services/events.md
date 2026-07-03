# Event Services

Source: https://developer.repebble.com/guides/events-and-services/events/

All Pebble apps are executed in three phases, which are summarized below:

- Initialization - all code from the beginning of `main()` is run to set up all the components of the app.

- Event Loop - the app waits for and responds to any event services it has subscribed to.

- Deinitialization - when the app is exiting (i.e.: the user has pressed Back from the last [`Window`](/docs/c/User_Interface/Window/ "Window") in the stack) [`app_event_loop()`](/docs/c/Foundation/App/#app_event_loop "app\_event\_loop") returns, and all deinitialization code is run before the app exits.

Once [`app_event_loop()`](/docs/c/Foundation/App/#app_event_loop "app\_event\_loop") is called, execution of `main()` pauses and all further activities are performed when events from various [`Event Service`](/docs/c/Foundation/Event_Service/ "Event Service")types occur. This continues until the app is exiting, and is typically handled in the following pattern:

```
static void init() {// Initialization code here}static void deinit() {// Deinitialization code here}int main(void) {init();app\_event\_loop();deinit();}
```

## Types of Events

There are multiple types of events an app can receive from various event services. These are described in the table below, along with their handler signature and a brief description of what they do:

| Event Service | Handler(s) | Description |
| --- | --- | --- |
| [`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService") | [`TickHandler`](/docs/c/Foundation/Event_Service/TickTimerService/#TickHandler "TickHandler") | Most useful for watchfaces. Allows apps to be notified when a second, minute, hour, day, month or year ticks by. |
| [`ConnectionService`](/docs/c/Foundation/Event_Service/ConnectionService/ "ConnectionService") | [`ConnectionHandler`](/docs/c/Foundation/Event_Service/ConnectionService/#ConnectionHandler "ConnectionHandler") | Allows apps to know when the Bluetooth connection with the phone connects and disconnects. |
| [`AccelerometerService`](/docs/c/Foundation/Event_Service/AccelerometerService/ "AccelerometerService") | [`AccelDataHandler`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelDataHandler "AccelDataHandler")  
[`AccelTapHandler`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelTapHandler "AccelTapHandler") | Allows apps to receive raw data or tap events from the onboard accelerometer. |
| [`BatteryStateService`](/docs/c/Foundation/Event_Service/BatteryStateService/ "BatteryStateService") | [`BatteryStateHandler`](/docs/c/Foundation/Event_Service/BatteryStateService/#BatteryStateHandler "BatteryStateHandler") | Allows apps to read the state of the battery, as well as whether the watch is plugged in and charging. |
| [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") | [`HealthEventHandler`](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHandler "HealthEventHandler") | Allows apps to be notified to changes in various [`HealthMetric`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric "HealthMetric") values as the user performs physical activities. |
| [`AppFocusService`](/docs/c/Foundation/Event_Service/AppFocusService/ "AppFocusService") | [`AppFocusHandler`](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandler "AppFocusHandler") | Allows apps to know when they are obscured by another window, such as when a notification modal appears. |
| [`CompassService`](/docs/c/Foundation/Event_Service/CompassService/ "CompassService") | [`CompassHeadingHandler`](/docs/c/Foundation/Event_Service/CompassService/#CompassHeadingHandler "CompassHeadingHandler") | Allows apps to read a compass heading, including calibration status of the sensor. |

In addition, many other APIs also operate through the use of various callbacks including [`MenuLayer`](/docs/c/User_Interface/Layers/MenuLayer/ "MenuLayer"), [`AppMessage`](/docs/c/Foundation/AppMessage/ "AppMessage"), [`Timer`](/docs/c/Foundation/Timer/ "Timer"), and [`Wakeup`](/docs/c/Foundation/Wakeup/ "Wakeup"), but these are not considered to be 'event services' in the same sense.

## Using Event Services

The event services described in this guide are all used in the same manner - the app subscribes an implementation of one or more handlers, and is notified by the system when an event of that type occurs. In addition, most also include a 'peek' style API to read a single data item or status value on demand. This can be useful to determine the initial service state when a watchapp starts. Apps can subscribe to as many of these services as they require, and can also unsubscribe at any time to stop receiving events.

Each event service is briefly discussed below with multiple snippets - handler implementation example, subscribing to the service, and any 'peek' API.

### Tick Timer Service

The [`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService") allows an app to be notified when different units of time change. This is decided based upon the [`TimeUnits`](/docs/c/Foundation/Event_Service/TickTimerService/#TimeUnits "TimeUnits") value specified when a subscription is added.

The [`struct tm`](http://www.cplusplus.com/reference/ctime/tm/) pointer provided in the handler is a standard C object that contains many data fields describing the current time. This can be used with[`strftime()`](http://www.cplusplus.com/reference/ctime/strftime/) to obtain a human-readable string.

```
static void tick\_handler(struct tm \*tick\_time, TimeUnits changed) {static char s\_buffer[8];// Read time into a string bufferstrftime(s\_buffer, sizeof(s\_buffer), "%H:%M", tick\_time);APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Time is now %s", s\_buffer);}
```

```
// Get updates when the current minute changestick\_timer\_service\_subscribe(MINUTE\_UNIT, tick\_handler);
```

> The [`TickTimerService`](/docs/c/Foundation/Event_Service/TickTimerService/ "TickTimerService") has no 'peek' API, but a similar effect can be achieved using the [`time()`](/docs/c/Standard_C/Time/ "Time") and [`localtime()`](/docs/c/Standard_C/Time/#localtime "localtime") APIs.

### Connection Service

The [`ConnectionService`](/docs/c/Foundation/Event_Service/ConnectionService/ "ConnectionService") uses a handler for each of two connection types:

- `pebble_app_connection_handler` - the connection to the Pebble app on the phone, analogous with the bluetooth connection state.

- `pebblekit_connection_handler` - the connection to an iOS companion app, if applicable. Will never occur on Android.

Either one is optional, but at least one must be specified for a valid subscription.

```
static void app\_connection\_handler(bool connected) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Pebble app %sconnected", connected ? "" : "dis");}static void kit\_connection\_handler(bool connected) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "PebbleKit %sconnected", connected ? "" : "dis"); }
```

```
connection\_service\_subscribe((ConnectionHandlers) {.pebble\_app\_connection\_handler = app\_connection\_handler,.pebblekit\_connection\_handler = kit\_connection\_handler});
```

```
// Peek at either the Pebble app or PebbleKit connectionsbool app\_connection = connection\_service\_peek\_pebble\_app\_connection();bool kit\_connection = connection\_service\_peek\_pebblekit\_connection();
```

### Accelerometer Service

The [`AccelerometerService`](/docs/c/Foundation/Event_Service/AccelerometerService/ "AccelerometerService") can be used in two modes - tap events and raw data events. [`AccelTapHandler`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelTapHandler "AccelTapHandler") and [`AccelDataHandler`](/docs/c/Foundation/Event_Service/AccelerometerService/#AccelDataHandler "AccelDataHandler") are used for each of these respective use cases. See the [_Accelerometer_](/guides/events-and-services/accelerometer.md) guide for more information.

**Data Events**

```
static void accel\_data\_handler(AccelData \*data, uint32\_t num\_samples) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Got %d new samples", (int)num\_samples);}
```

```
const int num\_samples = 10;// Subscribe to data eventsaccel\_data\_service\_subscribe(num\_samples, accel\_data\_handler);
```

```
// Peek at the last readingAccelData data;accel\_service\_peek(&data);
```

**Tap Events**

```
static void accel\_tap\_handler(AccelAxisType axis, int32\_t direction) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Tap event received");}
```

```
// Subscribe to tap eventsaccel\_tap\_service\_subscribe(accel\_tap\_handler);
```

### Battery State Service

The [`BatteryStateService`](/docs/c/Foundation/Event_Service/BatteryStateService/ "BatteryStateService") allows apps to examine the state of the battery, and whether or not is is plugged in and charging.

```
static void battery\_state\_handler(BatteryChargeState charge) {// Report the current charge percentageAPP\_LOG(APP\_LOG\_LEVEL\_INFO, "Battery charge is %d%%", (int)charge.charge\_percent);}
```

```
// Get battery state updatesbattery\_state\_service\_subscribe(battery\_state\_handler);
```

```
// Peek at the current battery stateBatteryChargeState state = battery\_state\_service\_peek();
```

### Health Service

The [`HealthService`](/docs/c/Foundation/Event_Service/HealthService/ "HealthService") uses the [`HealthEventHandler`](/docs/c/Foundation/Event_Service/HealthService/#HealthEventHandler "HealthEventHandler") to notify a subscribed app when new data pertaining to a [`HealthMetric`](/docs/c/Foundation/Event_Service/HealthService/#HealthMetric "HealthMetric") is available. See the [_Pebble Health_](/guides/events-and-services/health.md) guide for more information.

```
static void health\_handler(HealthEventType event, void \*context) {if(event == HealthEventMovementUpdate) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "New health movement event");}}
```

```
// Subscribe to health-related eventshealth\_service\_events\_subscribe(health\_handler, NULL);
```

### App Focus Service

The [`AppFocusService`](/docs/c/Foundation/Event_Service/AppFocusService/ "AppFocusService") operates in two modes - basic and complete.

**Basic Subscription**

A basic subscription involves only one handler which will be fired when the app is moved in or out of focus, and any animated transition has completed.

```
static void focus\_handler(bool in\_focus) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "App is %s in focus", in\_focus ? "now" : "not");}
```

```
// Add a basic subscriptionapp\_focus\_service\_subscribe(focus\_handler);
```

**Complete Subscription**

A complete subscription will notify the app with more detail about changes in focus using two handlers in an [`AppFocusHandlers`](/docs/c/Foundation/Event_Service/AppFocusService/#AppFocusHandlers "AppFocusHandlers") object:

- `.will_focus` - represents a change in focus that is _about_ to occur, such as the start of a transition animation to or from a modal window. `will_focus`will be `true` if the app will be in focus at the end of the transition.

- `.did_focus` - represents the end of a transition. `did_focus` will be `true`if the app is now completely in focus and the animation has finished.

```
void will\_focus\_handler(bool will\_focus) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Will %s focus", will\_focus ? "gain" : "lose");}void did\_focus\_handler(bool did\_focus) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "%s focus", did\_focus ? "Gained" : "Lost");}
```

```
// Subscribe to both types of eventsapp\_focus\_service\_subscribe\_handlers((AppFocusHandlers) {.will\_focus = will\_focus\_handler,.did\_focus = did\_focus\_handler});
```

### Compass Service

The [`CompassService`](/docs/c/Foundation/Event_Service/CompassService/ "CompassService") provides access to regular updates about the watch's magnetic compass heading, if it is calibrated. See the[_Compass_](/guides/events-and-services/compass.md) guide for more information.

```
static void compass\_heading\_handler(CompassHeadingData heading\_data) {// Is the compass calibrated?if(heading\_data.compass\_status == CompassStatusCalibrated) {APP\_LOG(APP\_LOG\_LEVEL\_INFO, "Calibrated! Heading is %ld",TRIGANGLE\_TO\_DEG(heading\_data.magnetic\_heading));}}
```

```
// Subscribe to compass heading updatescompass\_service\_subscribe(compass\_heading\_handler);
```

```
// Peek the compass heading dataCompassHeadingData data;compass\_service\_peek(&data);
```
