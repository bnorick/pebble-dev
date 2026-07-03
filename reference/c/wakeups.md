# Wakeups // Pebble Developers
The [`Wakeup`](https://developer.repebble.com/docs/c/Foundation/Wakeup/ "Wakeup") API allows developers to schedule an app launch in the future, even if the app itself is closed in the meantime. A wakeup event is scheduled in a similar manner to a [`Timer`](https://developer.repebble.com/docs/c/Foundation/Timer/ "Timer") with a future timestamp calculated beforehand.

Calculating Timestamps
----------------------

To schedule a wakeup event, first determine the timestamp of the desired wakeup time as a `time_t` variable. Most uses of the [`Wakeup`](https://developer.repebble.com/docs/c/Foundation/Wakeup/ "Wakeup") API will fall into three distinct scenarios discussed below.

### A Future Time

Call [`time()`](https://developer.repebble.com/docs/c/Standard_C/Time/ "Time") and add the offset, measured in seconds. For example, for 30 minutes in the future:

```
// 30 minutes from now
time_t timestamp = time(NULL) + (30 * SECONDS_PER_MINUTE);

```


### A Specific Time

Use [`clock_to_timestamp()`](about:/docs/c/Foundation/Wall_Time/#clock_to_timestamp "clock_to_timestamp") to obtain a `time_t` timestamp by specifying a day of the week and hours and minutes (in 24 hour format). For example, for the next occuring Monday at 5 PM:

```
// Next occuring monday at 17:00 
time_t timestamp = clock_to_timestamp(MONDAY, 17, 0);

```


### Using a Timestamp Provided by a Web Service

The timestamp will need to be translated using the [`getTimezoneOffset()`](http://www.w3schools.com/jsref/jsref_gettimezoneoffset.asp) method available in PebbleKit JS or with any timezone information given by the web service.

Scheduling a Wakeup
-------------------

Once a `time_t` timestamp has been calculated, the wakeup event can be scheduled:

```
// Let the timestamp be 30 minutes from now
const time_t future_timestamp = time() + (30 * SECONDS_PER_MINUTE);

// Choose a 'cookie' value representing the reason for the wakeup
const int cookie = 0;

// If true, the user will be notified if they missed the wakeup 
// (i.e. their watch was off)
const bool notify_if_missed = true;

// Schedule wakeup event
WakeupId id = wakeup_schedule(future_timestamp, cookie, notify_if_missed);

// Check the scheduling was successful
if(id >= 0) {
  // Persist the ID so that a future launch can query it
  const wakeup_id_key = 43;
  persist_write_int(wakeup_id_key, id);
}

```


After scheduling a wakeup event it is possible to perform some interaction with it. For example, reading the timestamp for when the event will occur using the [`WakeupId`](about:/docs/c/Foundation/Wakeup/#WakeupId "WakeupId") with [`wakeup_query()`](about:/docs/c/Foundation/Wakeup/#wakeup_query "wakeup_query"), and then perform simple arithmetic to get the time remaining:

```
// This will be set by wakeup_query()
time_t wakeup_timestamp = 0;

// Is the wakeup still scheduled?
if(wakeup_query(id, &wakeup_timestamp)) {
  // Get the time remaining
  int seconds_remaining = wakeup_timestamp - time(NULL);
  APP_LOG(APP_LOG_LEVEL_INFO, "%d seconds until wakeup", seconds_remaining);
}

```


To cancel a scheduled event, use the [`WakeupId`](about:/docs/c/Foundation/Wakeup/#WakeupId "WakeupId") obtained when it was scheduled:

```
// Cancel a wakeup
wakeup_cancel(id);

```


To cancel all scheduled wakeup events:

```
// Cancel all wakeups
wakeup_cancel_all();

```


Limitations
-----------

There are three limitations that should be taken into account when using the Wakeup API:

*   There can be no more than 8 scheduled wakeup events per app at any one time.
    
*   Wakeup events cannot be scheduled within 30 seconds of the current time.
    
*   Wakeup events are given a one minute window either side of the wakeup time. In this time no app may schedule an event. The return [`StatusCode`](about:/docs/c/Foundation/Storage/#StatusCode "StatusCode") of [`wakeup_schedule()`](about:/docs/c/Foundation/Wakeup/#wakeup_schedule "wakeup_schedule") should be checked to determine whether the scheduling of the new event should be reattempted. A negative value indicates that the wakeup could not be scheduled successfully.
    

The possible [`StatusCode`](about:/docs/c/Foundation/Storage/#StatusCode "StatusCode") values are detailed below:



* StatusCode: E_RANGE
  * Value: -8
  * Description: The wakeup event cannot be scheduled due to another event in that period.
* StatusCode: E_INVALID_ARGUMENT
  * Value: -4
  * Description: The time requested is in the past.
* StatusCode: E_OUT_OF_RESOURCES
  * Value: -7
  * Description: The application has already scheduled all 8 wakeup events.
* StatusCode: E_INTERNAL
  * Value: -3
  * Description: A system error occurred during scheduling.


Handling Wakeup Events
----------------------

A wakeup event can occur at two different times - when the app is closed, and when it is already launched and in the foreground.

If the app is launched due to a previously scheduled wakeup event, check the [`AppLaunchReason`](about:/docs/c/Foundation/Launch_Reason/#AppLaunchReason "AppLaunchReason") and load the app accordingly:

```
static void init() {
  if(launch_reason() == APP_LAUNCH_WAKEUP) {
    // The app was started by a wakeup event.
    WakeupId id = 0;
    int32_t reason = 0;

    // Get details and handle the event appropriately
    wakeup_get_launch_event(&id, &reason);
  }

  /* other init code */

}

```


If the app is expecting a wakeup to occur while it is open, use a subscription to the wakeup service to be notified of such events:

```
static void wakeup_handler(WakeupId id, int32_t reason) {
  // A wakeup event has occurred while the app was already open
}

```


```
// Subscribe to wakeup service
wakeup_service_subscribe(wakeup_handler);

```


The two approaches can also be combined for a unified response to being woken up, not depenent on the state of the app:

```
// Get details of the wakeup
wakeup_get_launch_event(&id, &reason);

// Manually handle using the handler
wakeup_handler(id, reason);

```